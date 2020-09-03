#include "RenderModel.h"

RenderModel::RenderModel()
{
    ModelName = "[N/A]";
}

RenderModel::RenderModel(std::string name, Mesh mesh)
{
    ModelName = name;
    VertexMeshList.push_back(mesh);
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
        Point point = waveFront.TextureCoordinates.at(pointIndex);
        Vertex vertex = Vertex(position, normal, color, point);

        mesh.Vertices.push_back(vertex);
        mesh.Indices.push_back(indice);
    }

    VertexMeshList.push_back(mesh);
}