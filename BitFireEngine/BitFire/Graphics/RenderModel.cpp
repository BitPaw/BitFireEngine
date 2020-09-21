#include "RenderModel.h"

#include "../OpenGL/OpenGLAPI.h"

void BF::RenderModel::UpdateRenderSystemLink()
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

BF::RenderModel::RenderModel() : RenderModel("[N/A]")
{

}

BF::RenderModel::RenderModel(std::string name)
{   
    ModelName = name; 
    _currentPosition = Vector3(0,0,0);
    ModelID = -1;
}

void BF::RenderModel::LoadFromWaveFront(WaveFront& waveFront)
{
    MeshList.ReSize(waveFront.ElementList.Size.Value);

    unsigned int offset = 0;
    unsigned int size = MeshList.Size.Value;

    for (unsigned int elementIndex = 0; elementIndex < size; elementIndex++)
    {
        WaveFrontElement* element = &waveFront.ElementList[elementIndex]; // Get current source Mesh
        const unsigned int faceElementListSize = element->FaceElementList.Size.Value; 

        Mesh* mesh = &MeshList[elementIndex]; // Get current target Mesh
        mesh->Name = element->Name; 
             
        // Vertex Data
        mesh->VertexList.ReSize(element->VertexPositionList.Size.Value);
        for (unsigned int i = 0; i < element->VertexPositionList.Size.Value; i++)
        {            
            Vertex* vertex = &mesh->VertexList[i];

            vertex->CurrentPosition = element->VertexPositionList[i];
        }

        mesh->TexturePointList.ReSize(element->TextureCoordinateList.Size.Value);
        for (unsigned int i = 0; i < element->TextureCoordinateList.Size.Value; i++)
        {
            mesh->TexturePointList[i] = element->TextureCoordinateList[i];
        }

        mesh->NormalPointList.ReSize(element->VertexNormalPositionList.Size.Value);
        for (unsigned int i = 0; i < element->VertexNormalPositionList.Size.Value; i++)
        {
            mesh->NormalPointList[i] = element->VertexNormalPositionList[i];
        }

        // Index Data
        mesh->IndexList.ReSize(faceElementListSize);
        for (unsigned int i = 0; i < faceElementListSize; i++)
        {
            IndexPosition* indexPosition = &element->FaceElementList[i];
            unsigned int vertexIndex = indexPosition->X - 1;
            unsigned int pointIndex = indexPosition->Y - 1;
            unsigned int vertexNormalIndex = indexPosition->Z - 1;

            mesh->IndexList[i].VertexPositionID = vertexIndex;
            mesh->IndexList[i].TexturePointID = pointIndex;
            mesh->IndexList[i].NormalVectorID = vertexNormalIndex;          
        }
    }  
    
    UpdateGlobalMesh();
    UpdateRenderSystemLink();
}

void BF::RenderModel::Move(BF::Vector3 vector)
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

void BF::RenderModel::MoveTo(Vector3 vector)
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

BF::Vector3 BF::RenderModel::CurrentPosition()
{
    return _currentPosition;
}

void BF::RenderModel::Orbit(Vector3 vector)
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

void BF::RenderModel::Rotate(Vector3 vector)
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

void BF::RenderModel::ReSize(Vector3 vector)
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

void BF::RenderModel::CalculateNormalVectors()
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

void BF::RenderModel::UseTexturePointAsColor()
{
    const unsigned int indexListLength = GlobalMesh.IndexList.Size.Value;

    GlobalMesh.ColorList.ReSize(indexListLength);
    MeshList[0].ColorList.ReSize(indexListLength);

    // Link
    for (unsigned int i = 0; i < indexListLength; i++)
    {
        GlobalMesh.ColorList[i] = &MeshList[0].ColorList[i];
    }

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

void BF::RenderModel::PrintModelData()
{
    printf("Meshes %u\n", MeshList.Size.Value);

    for (unsigned int i = 0; i < MeshList.Size.Value; i++)
    {
        Mesh* mesh = &MeshList[i];

        printf("N: %u\n", mesh->NormalPointList.Size.Value);

        
    }
}

void BF::RenderModel::UpdateGlobalMesh()
{
    const unsigned int length = MeshList.Size.Value;
    unsigned int vertexListLength = 0;
    unsigned int texturePointListLength = 0;
    unsigned int normalPointListLength = 0;
    unsigned int colorListLength = 0;
    unsigned int indexListLength = 0;

    for (unsigned int i = 0; i < length; i++)
    {
        Mesh* mesh = &MeshList[i];

        vertexListLength += mesh->VertexList.Size.Value;
        texturePointListLength += mesh->TexturePointList.Size.Value;
        normalPointListLength += mesh->NormalPointList.Size.Value;
        colorListLength += mesh->ColorList.Size.Value;
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
        colorListLength = mesh->ColorList.Size.Value;
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

        for (unsigned int i = 0; i < colorListLength; i++)
        {
            GlobalMesh.ColorList[GlobalMesh.ColorList.CurrentIndex++] = &mesh->ColorList[i];
        }

        for (unsigned int i = 0; i < indexListLength; i++)
        {
            GlobalMesh.IndexList[GlobalMesh.IndexList.CurrentIndex++] = &mesh->IndexList[i];
        }
    }
}