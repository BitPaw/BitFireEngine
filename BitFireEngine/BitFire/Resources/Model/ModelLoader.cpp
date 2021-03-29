#include "ModelLoader.h"
#include "../File/File.h"

BF::ModelType BF::ModelLoader::ParseModelType(AsciiString& extension)
{
    bool is3DS = extension.CompareIgnoreCase("3ds");
    bool isOBJ = extension.CompareIgnoreCase("obj");
    bool isPLY = extension.CompareIgnoreCase("ply");
    bool isSTL = extension.CompareIgnoreCase("stl");
    bool isWRL = extension.CompareIgnoreCase("wrl");

    if (is3DS) return ModelType::A3DS;
    if (isOBJ) return ModelType::OBJ;
    if (isPLY) return ModelType::PLY;
    if (isSTL) return ModelType::STL;
    if (isWRL) return ModelType::WRL;

    return ModelType::UnKown;
}

bool BF::ModelLoader::IsModelFile(AsciiString& extension)
{
    return ParseModelType(extension) != ModelType::UnKown;
}

BF::ErrorCode BF::ModelLoader::LoadFromFile(AsciiString& filePath, Model& model)
{
    File file(filePath);
    ModelType modelType = ParseModelType(file.Extension);

    model.FilePath.Copy(filePath);

    switch (modelType)
    {
    case BF::ModelType::A3DS:
        break;

    case BF::ModelType::FBX:
        break;

    case BF::ModelType::OBJ:
    {
        OBJ obj;
        obj.Load(filePath);
        obj.Convert(model);
        break;
    }

    case BF::ModelType::PLY:
        break;

    case BF::ModelType::STL:
        break;

    case BF::ModelType::WRL:
        break;

    case BF::ModelType::UnKown:
    default:
        return ErrorCode::NotSupported;
    }

    return ErrorCode::NoError;
}

void BF::ModelLoader::ToModel(Shape& form, Model& model)
{
    const unsigned int meshSize = 1;
    List<Point<float>>* vertexData = form.DrawPointList();
    unsigned int vertexListSize = vertexData->Size();
    Mesh* mesh;

    if((vertexListSize % 3) == 0)
    {     
        model.RenderInformation.RenderType = RenderMode::Triangle;
    }

    if ((vertexListSize % 4) == 0)
    {
        model.RenderInformation.RenderType = RenderMode::Square;
    }

    model.MeshList.ReSize(meshSize);

    mesh = &model.MeshList[0]; // Get current target Mesh
    mesh->Name.Copy("Shape");


    mesh->VertexList.ReSize(vertexListSize);
    mesh->IndexList.ReSize(vertexListSize);

    for (unsigned int i = 0; i < vertexListSize; i++)
    {
        Vertex* vertex = &mesh->VertexList[i];
        vertex->ColorID = -1;
        vertex->CurrentPosition = (*vertexData)[i];
        
        mesh->IndexList[i].Set(i, -1, -1);
    }

    vertexData->DeleteAll();

    model.CalculateNormalVectors();

    model.UpdateGlobalMesh();
}