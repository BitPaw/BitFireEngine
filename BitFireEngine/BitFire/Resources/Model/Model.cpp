#include "Model.h"

#include "../../OpenGL/OpenGLAPI.h"

void BF::Model::UpdateRenderSystemLink()
{
    OpenGLAPI* openGLAPI = OpenGLAPI::Instance();

    if (openGLAPI == nullptr)
    {
        // Error  
    }
    else
    {
        openGLAPI->Render->RegisterRenderModel(this);
    }
}

BF::Model::Model() : Model("[N/A]")
{

}

BF::Model::Model(std::string name)
{   
    _currentPosition = Vector3(0, 0, 0);
       
    ModelID = -1;
    ModelName = name;
}

BF::Model::~Model()
{
    ModelName = "[DELETED] " + ModelName;

   // MeshList.DeleteAll();
}

void BF::Model::MoveBy(BF::Vector3 vector)
{  
    _currentPosition += vector;

    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size.Value; i++)
    {
        Vertex* vertex = GlobalMesh.VertexList[i];
        Position* currentPosition = &vertex->CurrentPosition;

        currentPosition->X += vector.X;
        currentPosition->Y += vector.Y;
        currentPosition->Z += vector.Z;  
    }

    UpdateRenderSystemLink();
}

void BF::Model::MoveTo(Vector3 vector)
{
    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size.Value; i++)
    {
        Vertex* vertex = GlobalMesh.VertexList[i];
        Position* currentPosition = &vertex->CurrentPosition;

        currentPosition->X += -_currentPosition.X + vector.X;
        currentPosition->Y += -_currentPosition.Y + vector.Y;
        currentPosition->Z += -_currentPosition.Z + vector.Z;
    }

    _currentPosition = vector;

    UpdateRenderSystemLink();
}

BF::Vector3 BF::Model::CurrentPosition()
{
    return _currentPosition;
}

void BF::Model::Orbit(Vector3 vector)
{
    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size.Value; i++)
    {
        Vertex* vertex = GlobalMesh.VertexList[i];
        Position* currentPosition = &vertex->CurrentPosition;
        Vector3 current = Vector3(currentPosition->X, currentPosition->Y, currentPosition->Z);

        current.Rotate(vector);

        currentPosition->X = current.X;
        currentPosition->Y = current.Y;
        currentPosition->Z = current.Z;
    }

    UpdateRenderSystemLink();
}

void BF::Model::Rotate(Vector3 vector)
{
    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size.Value; i++)
    {
        Vertex* vertex = GlobalMesh.VertexList[i];
        Position* currentPosition = &vertex->CurrentPosition;
        Vector3 current = Vector3(currentPosition->X, currentPosition->Y, currentPosition->Z);  
    
        current -= _currentPosition;
        current.Rotate(vector);
        current += _currentPosition;

        currentPosition->X = current.X;
        currentPosition->Y = current.Y;
        currentPosition->Z = current.Z;
    }

    UpdateRenderSystemLink();
}

void BF::Model::Scale(Vector3 vector)
{
    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size.Value; i++)
    {
        Vertex* vertex = GlobalMesh.VertexList[i];
        Position* currentPosition = &vertex->CurrentPosition;

        currentPosition->X *= vector.X;
        currentPosition->Y *= vector.Y;
        currentPosition->Z *= vector.Z;
    }

    UpdateRenderSystemLink();
}

void BF::Model::CalculateNormalVectors()
{
    for (unsigned int i = 0; i < MeshList.Size.Value; i++)
    {
        Mesh* mesh = &MeshList[i];
        List<MeshIndexData>* indexList = &mesh->IndexList;
        List<Vertex>* vertexList = &mesh->VertexList;
        unsigned int size = mesh->IndexList.Size.Value;

        mesh->NormalPointList.ReSize(size);

        for (unsigned int i = 0; i < size; i += 3)
        {
            unsigned int indexA = (*indexList)[i].VertexPositionID;
            unsigned int indexB = (*indexList)[i + 1].VertexPositionID;
            unsigned int indexC = (*indexList)[i + 2].VertexPositionID;

            Vertex* vertexA = &(*vertexList)[indexA];
            Vertex* vertexB = &(*vertexList)[indexB];
            Vertex* vertexC = &(*vertexList)[indexC];

            Position* aPos = &vertexA->CurrentPosition;
            Position* bPos = &vertexB->CurrentPosition;
            Position* cPos = &vertexC->CurrentPosition;

            glm::vec3 a(aPos->X, aPos->Y, aPos->Z);
            glm::vec3 b(bPos->X, bPos->Y, bPos->Z);
            glm::vec3 c(cPos->X, cPos->Y, cPos->Z);

            glm::vec3 nA = glm::cross(a, b);
            glm::vec3 nB = glm::cross(b, c);
            glm::vec3 nC = glm::cross(c, a);  

            // BAd code, this memory waste
            (*indexList)[i].NormalVectorID = mesh->NormalPointList.CurrentIndex;
            mesh->NormalPointList[mesh->NormalPointList.CurrentIndex++] = Position(nA.x, nA.y, nA.z);

            (*indexList)[i + 1].NormalVectorID = mesh->NormalPointList.CurrentIndex;
            mesh->NormalPointList[mesh->NormalPointList.CurrentIndex++] = Position(nB.x, nB.y, nB.z);

            (*indexList)[i + 2].NormalVectorID = mesh->NormalPointList.CurrentIndex;
            mesh->NormalPointList[mesh->NormalPointList.CurrentIndex++] = Position(nC.x, nC.y, nC.z);
        }
    }   
}

void BF::Model::UseTexturePointAsColor()
{
    const unsigned int indexListLength = GlobalMesh.IndexList.Size.Value;

    GlobalMesh.ColorList.ReSize(indexListLength);
    
    /*MeshList[0].ColorList.ReSize(indexListLength);

    // Link
    for (unsigned int i = 0; i < indexListLength; i++)
    {
        GlobalMesh.ColorList[i] = &MeshList[0].ColorList[i];
    }
    */

    // Color
    for (unsigned int i = 0; i < indexListLength; i++)
    {
        MeshIndexData* meshIndexData = GlobalMesh.IndexList[i];
        
        Vertex* vertex = GlobalMesh.VertexList[meshIndexData->VertexPositionID];
        Point* texturepoint = GlobalMesh.TexturePointList[meshIndexData->TexturePointID];

        vertex->ColorID = i;
        GlobalMesh.ColorList[i]->SetColor(texturepoint->X, texturepoint->Y, 0);
    }

    UpdateRenderSystemLink();
}

void BF::Model::PrintModelData()
{
    printf("Meshes %u\n", MeshList.Size.Value);

    for (unsigned int i = 0; i < MeshList.Size.Value; i++)
    {
        Mesh* mesh = &MeshList[i];

        printf("N: %u\n", mesh->NormalPointList.Size.Value);

        
    }
}

void BF::Model::UpdateGlobalMesh()
{
    const unsigned int length = MeshList.Size.Value;
    unsigned int vertexListLength = 0;
    unsigned int texturePointListLength = 0;
    unsigned int normalPointListLength = 0;
    unsigned int colorListLength = ColorList.Size.Value;
    unsigned int indexListLength = 0;

    for (unsigned int i = 0; i < length; i++)
    {
        Mesh* mesh = &MeshList[i];

        vertexListLength += mesh->VertexList.Size.Value;
        texturePointListLength += mesh->TexturePointList.Size.Value;
        normalPointListLength += mesh->NormalPointList.Size.Value;
        indexListLength += mesh->IndexList.Size.Value;
    }

    GlobalMesh.VertexList.ReSize(vertexListLength);
    GlobalMesh.TexturePointList.ReSize(texturePointListLength);
    GlobalMesh.NormalPointList.ReSize(normalPointListLength);
    GlobalMesh.ColorList.ReSize(colorListLength);
    GlobalMesh.IndexList.ReSize(indexListLength);

    for (unsigned int i = 0; i < length; i++)
    {
        Mesh* mesh = &MeshList[i];
        vertexListLength = mesh->VertexList.Size.Value;
        texturePointListLength = mesh->TexturePointList.Size.Value;
        normalPointListLength = mesh->NormalPointList.Size.Value;
        indexListLength = mesh->IndexList.Size.Value;

        for (unsigned int i = 0; i < vertexListLength; i++)
        {
            GlobalMesh.VertexList[GlobalMesh.VertexList.CurrentIndex++] = &mesh->VertexList[i];
        }

        for (unsigned int i = 0; i < texturePointListLength; i++)
        {
            GlobalMesh.TexturePointList[GlobalMesh.TexturePointList.CurrentIndex++] = &mesh->TexturePointList[i];
        }

        for (unsigned int i = 0; i < normalPointListLength; i++)
        {
            GlobalMesh.NormalPointList[GlobalMesh.NormalPointList.CurrentIndex++] = &mesh->NormalPointList[i];
        }

        GlobalMesh.ColorList.CurrentIndex = 0;
        for (unsigned int i = 0; i < colorListLength; i++)
        {
            GlobalMesh.ColorList[GlobalMesh.ColorList.CurrentIndex++] = &ColorList[i];
        }

        for (unsigned int i = 0; i < indexListLength; i++)
        {
            GlobalMesh.IndexList[GlobalMesh.IndexList.CurrentIndex++] = &mesh->IndexList[i];
        }
    }
}