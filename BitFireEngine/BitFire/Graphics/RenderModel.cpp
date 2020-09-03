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
     
    ShouldBeRendered = validMesh;

    if (validMesh)
    {
        VertexMeshList.push_back(mesh);

        UpdateRenderSystemLink();
    }
}

RenderModel::~RenderModel()
{
    for (unsigned int i = 0; i < VertexMeshList.size(); i++)
    {
        //delete &VertexMeshList.at(i);
    }
}

void RenderModel::LoadFromWaveFront(WaveFront& waveFront)
{
    unsigned int IdecieListSize = waveFront.FaceElements.size() * 3;
    ModelName = waveFront.Name;
    Mesh mesh = Mesh();
    RGBA color = RGBA();

    mesh.Vertices.reserve(IdecieListSize);
    mesh.Indices.reserve(IdecieListSize);

    unsigned int idiceIndex = 0;

    for (unsigned int i = 0; i < waveFront.FaceElements.size(); i++)
    {
        IndexPosition* indexPosition = &waveFront.FaceElements.at(i);
        unsigned int indice = idiceIndex++;
        unsigned int vertexIndex = indexPosition->X -1;
        unsigned int pointIndex = indexPosition->Y -1;
        unsigned int vertexNormalIndex = indexPosition->Z -1;
        
        Position position = waveFront.VectorPositions.at(vertexIndex);
        Position normal = waveFront.VectorNormalPositions.at(vertexNormalIndex);
        Point point;

        if (pointIndex < waveFront.TextureCoordinates.size())
        {
            point = waveFront.TextureCoordinates.at(pointIndex);
        }
        else
        {
            point = Point(0,0);
        }
      
        Vertex vertex = Vertex(position, normal, color, point);

        mesh.Vertices.push_back(vertex);
        mesh.Indices.push_back(indice);
    }

    mesh.GenerateArrayData();
    VertexMeshList.push_back(mesh);

    UpdateRenderSystemLink();
}

void RenderModel::MoveWholeObject(Position position)
{
    for (unsigned int i = 0; i < VertexMeshList.size(); i++)
    {
        Mesh* mesh = &VertexMeshList.at(i);

        for (unsigned int  i = 0; i < mesh->Vertices.size(); i++)
        {
            Vertex* vertex = &mesh->Vertices.at(i);
            Position* currentPosition = &vertex->CurrentPosition;

            currentPosition->X += position.X;
            currentPosition->Y += position.Y;
            currentPosition->Z += position.Z;
        }
    }

    UpdateRenderSystemLink();
}
