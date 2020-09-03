#include "RenderModel.h"
#include "../OpenGL/OpenGLAPI.h"

void RenderModel::UpdateRenderSystemLink()
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

RenderModel::RenderModel() : RenderModel("[N/A]", Mesh())
{
  
}

RenderModel::RenderModel(std::string name, Mesh mesh) 
{
    bool validMesh = mesh.Dimension > 0;
    RenderID = -1;

    ModelName = name; 
    
    MeshListLengh = 0;

    ShouldBeRendered = validMesh;

    if (validMesh)
    {
        MeshListLengh++;
        MeshList = new Mesh[1]{ mesh };
        //VertexMeshList.push_back(mesh);

        UpdateRenderSystemLink();
    }
}

RenderModel::~RenderModel()
{
    /*
    for (unsigned int i = 0; i < VertexMeshList.size(); i++)
    {
        //delete &VertexMeshList.at(i);
    }
    */
}

void RenderModel::LoadFromWaveFront(WaveFront& waveFront)
{
    MeshListLengh = waveFront.ElementListSize;
    MeshList = new Mesh[MeshListLengh];

    for (unsigned int elementIndex = 0; elementIndex < 1; elementIndex++)
    {
        const WaveFrontElement* element = &waveFront.ElementList[elementIndex];
        const unsigned int faceElementListSize = element->FaceElementListSize;

        Mesh* mesh = &MeshList[elementIndex];
        mesh->VertexListSize = faceElementListSize;
        mesh->IndexListSize = faceElementListSize;               
      
        mesh->VertexList = new Vertex[faceElementListSize];
        mesh->IndexList = new unsigned int[faceElementListSize];

        for (unsigned int faceIndex = 0; faceIndex < faceElementListSize; faceIndex++)
        {
            IndexPosition* indexPosition = &element->FaceElementList[faceIndex];      

            unsigned int vertexIndex = (indexPosition->X - 1);
            unsigned int pointIndex = indexPosition->Y - 1;
            unsigned int vertexNormalIndex = indexPosition->Z - 1;

            Vertex* vertex = &mesh->VertexList[faceIndex];
            vertex->CurrentPosition = *waveFront.GetVertexPositionFromGlobalID(vertexIndex);
            vertex->NormalizedPosition = *waveFront.GetVertexNormalFromGlobalID(vertexNormalIndex);

            if (pointIndex < element->TextureCoordinateListSize)
            {
                vertex->TexturePoint = *waveFront.GetVertexTextureCoordinatesFromGlobalID(pointIndex);
            }
            
            mesh->IndexList[faceIndex] = faceIndex;
          
                /*
                Position* position = &element->VertexPositionList[vertexIndex];
                Position* normal = &element->VertexNormalPositionList[vertexNormalIndex];
                Point point = Point(0, 0);

                if (pointIndex < element->TextureCoordinateListSize)
                {
                    point = element->TextureCoordinateList[pointIndex];
                }

                Vertex vertex = Vertex(*position, *normal, color, point);

                mesh->VertexList[faceIndex] = vertex;
                mesh->IndexList[faceIndex] = idiceIndex++;
                */
            
        }

        mesh->GenerateArrayData();
    }  

    UpdateRenderSystemLink();
}

void RenderModel::MoveWholeObject(Position position)
{
    for (unsigned int i = 0; i < MeshListLengh; i++)
    {
        Mesh* mesh = &MeshList[i];

        for (unsigned int  i = 0; i < mesh->VertexListSize; i++)
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
