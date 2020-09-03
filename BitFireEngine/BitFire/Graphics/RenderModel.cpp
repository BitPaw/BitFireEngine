#include "RenderModel.h"
#include "../OpenGL/OpenGLAPI.h"

void BF::RenderModel::UpdateRenderSystemLink()
{
    OpenGLAPI* openGLAPI = OpenGLAPI::Instance();

    if (openGLAPI == nullptr)
    {
        ShouldBeRendered = false;
        RenderID = -1;    
    }
    else
    {
        ShouldBeRendered = true;
        RenderID = openGLAPI->Render->RegisterRenderModel(this);
    }
}

BF::RenderModel::RenderModel() : RenderModel("[N/A]")
{
  
}

BF::RenderModel::RenderModel(std::string name)
{   
    RenderID = -1;
    ShouldBeRendered = false;
    ModelName = name; 
}

void BF::RenderModel::LoadFromWaveFront(WaveFront& waveFront)
{
    MeshList.ReSize(waveFront.ElementList.Size.Value);

    unsigned int offset = 0;
    unsigned int size = MeshList.Size.Value;

    //size = 1;

    for (unsigned int elementIndex = 0; elementIndex < size; elementIndex++)
    {
        WaveFrontElement* element = &waveFront.ElementList[elementIndex]; // Get current source Mesh
        const unsigned int faceElementListSize = element->FaceElementList.Size.Value; 

        Mesh* mesh = &MeshList[elementIndex]; // Get current target Mesh
        mesh->Name = element->Name; 
      
    
        //  mesh->VertexList.ReSize(faceElementListSize);
        
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

           // mesh->IndexList[i] = vertexIndex; // OK

            // CANT RENDER MORE THEN ONE MESH AT ONCE WHY?????!!?!?!
           /*
            Vertex* vertex = &mesh->VertexList[vertexIndex];
            vertex->CurrentPosition = *waveFront.GetVertexPositionFromGlobalID(vertexIndex);
            vertex->NormalizedPosition = *waveFront.GetVertexNormalFromGlobalID(vertexNormalIndex);

            if (pointIndex < element->TextureCoordinateListSize)
            {
                vertex->TexturePoint = *waveFront.GetVertexTextureCoordinatesFromGlobalID(pointIndex);
                vertex->Color = RGBA(vertex->TexturePoint.X, vertex->TexturePoint.Y, 1);
            }*/

          
        }
    }  
    
    UpdateGlobalMesh();

    // Generate Array Data?
    UpdateRenderSystemLink();
}

void BF::RenderModel::MoveWholeObject(Position position)
{
    for (unsigned int i = 0; i < MeshList.Size.Value; i++)
    {
        Mesh* mesh = &MeshList[i];

        for (unsigned int  i = 0; i < mesh->VertexList.Size.Value; i++)
        {
            Vertex* vertex = &mesh->VertexList[i];
            Position* currentPosition = &vertex->CurrentPosition;
            currentPosition->X += position.X;
            currentPosition->Y += position.Y;
            currentPosition->Z += position.Z;
        }
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

void BF::RenderModel::PrintModelData()
{
    printf("Meshes %u\n", MeshList.Size.Value);

    for (size_t i = 0; i < MeshList.Size.Value; i++)
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
/*

Vertex* BF::RenderModel::GetVertexInGlobalMesh(const unsigned int vertexID)
{
    unsigned int length = MeshList.Size.Value;
    unsigned int dynamicIndex = 0;

    for (unsigned int i = 0; i < length; i++)
    {
        Mesh* mesh = &MeshList[i];
        unsigned int size = mesh->VertexList.Size.Value;

        if (dynamicIndex + size < vertexID)
        {
            dynamicIndex += size;          
        }     
        else
        {
            for (unsigned int i = 0; i < size; i++)
            {
                if (vertexID == dynamicIndex++)
                {
                    return &mesh->VertexList[i];
                }
            }
        }
    }

   throw std::runtime_error("Not Found");

   return nullptr;
}

Point* BF::RenderModel::GetTexturePointInGlobalMesh(const unsigned int vertexID)
{
    unsigned int length = MeshList.Size.Value;
    unsigned int dynamicIndex = 0;

    for (unsigned int i = 0; i < length; i++)
    {
        Mesh* mesh = &MeshList[i];
        unsigned int size = mesh->TexturePointList.Size.Value;

        if (dynamicIndex + size < vertexID)
        {
            dynamicIndex += size;
        }
        else
        {

            for (unsigned int i = 0; i < size; i++)
            {
                if (vertexID == dynamicIndex++)
                {
                    return &mesh->TexturePointList[i];
                }
            }
        }
    }

    throw std::runtime_error("Not Found");

    return nullptr;
}

Position* BF::RenderModel::GetNormalInGlobalMesh(const unsigned int vertexID)
{
    unsigned int length = MeshList.Size.Value;
    unsigned int dynamicIndex = 0;

    for (unsigned int i = 0; i < length; i++)
    {
        Mesh* mesh = &MeshList[i];
        unsigned int size = mesh->NormalPointList.Size.Value;

        if (dynamicIndex + size < vertexID)
        {
            dynamicIndex += size;
        }
        else
        {
            for (unsigned int i = 0; i < size; i++)
            {
                if (vertexID == dynamicIndex++)
                {
                    return &mesh->NormalPointList[i];
                }
            }
        }
    }
    throw std::runtime_error("Not Found");

    return nullptr;
}



void BF::Mesh::GenerateArrayData()
{
    // Vertex
    {
        unsigned int dynamicIndex = 0;
        unsigned int blockSize = (4 + 4 + 4 + 2);

        _vertexData.Lengh = VertexListSize * blockSize;
        _vertexData.Data = new float[_vertexData.Lengh];
        _vertexData.SizeInBytesSingleBlock = sizeof(float) * blockSize;
        _vertexData.SizeInBytesDataBlock = sizeof(float) * _vertexData.Lengh;

        float* vList = _vertexData.Data;

        //printf("Creating Data Array. Length=%u\n", _vertexData.Lengh);

        for (unsigned int i = 0; i < VertexListSize; i++)
        {
            Vertex* vertex = &VertexList[i];
            Position* position = &vertex->CurrentPosition;
            Position* normal = &vertex->NormalizedPosition;
            Point* point = &vertex->TexturePoint;
            RGBA* color = &vertex->Color;

            //printf("[ID=%u]\n", i);
            //printf("Position: <%.2f | %.2f | %.2f>\n", position->X, position->Y, position->Z);
            //printf("Normal  : <%.2f | %.2f | %.2f>\n", normal->X, normal->Y, normal->Z);
            //printf("Point   : <%.2f | %.2f>\n", point->X, point->Y);
            //printf("Color   : <%.2f | %.2f | %.2f | %.2f>\n\n", color->Red, color->Green, color->Blue, color->Alpha);

            // positions
            vList[dynamicIndex++] = position->X;
            vList[dynamicIndex++] = position->Y;
            vList[dynamicIndex++] = position->Z;
            vList[dynamicIndex++] = 1; // W

            // Normals
            vList[dynamicIndex++] = normal->X;
            vList[dynamicIndex++] = normal->Y;
            vList[dynamicIndex++] = normal->Z;
            vList[dynamicIndex++] = 1; // W

            // Color
            vList[dynamicIndex++] = color->Red;
            vList[dynamicIndex++] = color->Green;
            vList[dynamicIndex++] = color->Blue;
            vList[dynamicIndex++] = color->Alpha;

            // Texture
            vList[dynamicIndex++] = point->X;
            vList[dynamicIndex++] = point->Y;
        }
    }
    /*
    for (size_t i = 0; i < _vertexData.Lengh; i++)
    {
        //printf("[ID=%u/%u] %f\n", i, _vertexData.Lengh ,_vertexData.Data[i]);
    }
    
}

*/