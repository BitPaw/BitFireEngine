#include "Model.h"

#include "ModelType.h"

#include "3DS/A3DS.h"
#include "FBX/FBX.h"
#include "OBJ/OBJ.h"
#include "PLY/PLY.h"
#include "STL/STL.h"
#include "WRL/WRL.h"

#include "../File/File.h"
#include "../../../SystemResource/Source/Math/Geometry/Shape/Triangle.h"
#include "../../../SystemResource/Source/Math/Geometry/Shape/Rectangle.h"

BF::Model::Model()
{
    ShouldItBeRendered = false;

    MaterialListSize = 0;
    MaterialList = nullptr;

    MeshListSize = 0;
    MeshList = nullptr;

    SharedModel = nullptr;

    NameChange("<Unnamed Model>");
}

BF::Model::Model(const char* modelName) : Model()
{
    NameChange(modelName);
}

void BF::Model::PrintModelData()
{
    printf("+--------------------------------------------+\n");
    printf("| Meshes %u |\n", MeshListSize);

    for (size_t i = 0; i < MeshListSize; i++)
    {
        Mesh& mesh = MeshList[i];
        MeshRenderInfo& info = mesh.RenderInfo;
        MeshStructure& structure = mesh.Structure;

        printf("+--------------------------------------------+\n");
        printf("| Mesh <%u/%u>\n", i, MeshListSize);
        printf("| Vertex   : ID:%u, Size:%u |\n", structure.VertexBufferID, structure.VertexDataSize);
        printf("| Index    : ID:%u, Size:%u |\n", structure.IndexBufferID, structure.IndexDataSize);
        printf("| Material : ID:%u, ShaderID:%u, Render:%u |\n", info.MaterialID, info.ShaderProgramID, info.ShouldBeRendered);
    }

    printf("+--------------------------------------------+");
}

BF::ModelType BF::Model::FileFormatPeek(const char* fileExtension)
{
    File file(fileExtension);

    if (file.ExtensionEquals("3ds")) return ModelType::A3DS;
    if (file.ExtensionEquals("obj")) return ModelType::OBJ;
    if (file.ExtensionEquals("ply")) return ModelType::PLY;
    if (file.ExtensionEquals("stl")) return ModelType::STL;
    if (file.ExtensionEquals("wrl")) return ModelType::WRL;

    return ModelType::UnKown;
}

BF::FileActionResult BF::Model::Load()
{
    return Load(FilePath);
}

void BF::Model::Position(Vector3<float> position)
{
    MatrixModel.MoveTo(position);
}

BF::Vector3<float> BF::Model::Position()
{
    return MatrixModel.PositionXYZ();
}

BF::FileActionResult BF::Model::Load(const char* filePath)
{
    if (!File::DoesFileExist(filePath))
    {
        ID = ResourceIDFileNotFound;
        return FileActionResult::FileNotFound;
    }

    ModelType modelType = FileFormatPeek(filePath);

    ID = ResourceIDLoading;

    FilePathChange(filePath);

    switch (modelType)
    {
        case ModelType::A3DS:
        {
            A3DS a3ds;
            a3ds.Load(filePath);
            a3ds.ConvertTo(*this);
            break;
        }

        case ModelType::FBX:
        {
            FBX fbx;
            fbx.Load(filePath);
            fbx.ConvertTo(*this);
            break;
        }

        case ModelType::OBJ:
        {
            OBJ obj;
            obj.Load(filePath);
            obj.ConvertTo(*this);
            break;
        }

        case ModelType::PLY:
        {
            OBJ obj;
            obj.Load(filePath);
            obj.ConvertTo(*this);
            break;
        }

        case ModelType::STL:
        {
            STL stl;
            stl.Load(filePath);
            stl.ConvertTo(*this);
            break;
        }

        case ModelType::WRL:
        {
            WRL wrl;
            wrl.Load(filePath);
            wrl.ConvertTo(*this);
            break;
        }

        case ModelType::UnKown:
        default:
            return FileActionResult::FormatNotSupported;
    }

    ID = ResourceIDLoaded;

    return FileActionResult::Successful;
}

void BF::Model::ConvertFrom(float* vertexList, size_t vertexListSize, unsigned int* indexList, size_t indexListSize, RenderMode renderMode, float textureScaleX, float textureScaleY, bool rawPositions)
{
    ID = ResourceIDLoading;

    MeshListSize = 1;
    MeshList = new Mesh[MeshListSize];

    Mesh& mesh = MeshList[0]; // Get current target Mesh
    
    mesh.Structure.RenderType = renderMode;

    NameChange("<Shape>");

    if (rawPositions)
    {
        mesh.Structure.VertexDataBlockListSize = 1;
        mesh.Structure.VertexDataBlockList[0] = 3;
        mesh.Structure.VertexDataBlockList[1] = 0;
        mesh.Structure.VertexDataBlockList[2] = 0;
        mesh.Structure.VertexDataBlockList[3] = 0;

        mesh.Structure.Allocate(vertexListSize, indexListSize);

        memcpy(mesh.Structure.VertexData, vertexList, vertexListSize * sizeof(float));
        memcpy(mesh.Structure.IndexData, indexList, indexListSize * sizeof(unsigned int));
    }
    else
    {
        mesh.Structure.VertexDataBlockListSize = 4;
        mesh.Structure.VertexDataBlockList[0] = 3;
        mesh.Structure.VertexDataBlockList[1] = 3;
        mesh.Structure.VertexDataBlockList[2] = 4;
        mesh.Structure.VertexDataBlockList[3] = 2;

        mesh.Structure.Allocate((vertexListSize / 3) * (3 + 3 + 4 + 2), indexListSize);

        // strncpy(mesh.Name, "Shape", MeshNameSize);

        memcpy(mesh.Structure.IndexData, indexList, indexListSize * sizeof(unsigned int));

        float* vertexFullData = mesh.Structure.VertexData;
        unsigned int vertexFullDataIndex = 0;

        for (size_t i = 0; i < vertexListSize; )
        {
            float x = vertexList[i++];
            float y = vertexList[i++];
            float z = vertexList[i++];
            float xNorm = x != 0 ? 0 : 1;
            float yNorm = y != 0 ? 0 : 1;
            float tx = (xNorm) * textureScaleX; // [-1,1] -> [0,2] -> [0,1] // ((-x + 1) / 2.0f) * textureScale
            float ty = yNorm * textureScaleY;

            vertexFullData[vertexFullDataIndex++] = x;
            vertexFullData[vertexFullDataIndex++] = y;
            vertexFullData[vertexFullDataIndex++] = z;

            vertexFullData[vertexFullDataIndex++] = 0;
            vertexFullData[vertexFullDataIndex++] = 0;
            vertexFullData[vertexFullDataIndex++] = 0;

            vertexFullData[vertexFullDataIndex++] = 1;
            vertexFullData[vertexFullDataIndex++] = 1;
            vertexFullData[vertexFullDataIndex++] = 1;
            vertexFullData[vertexFullDataIndex++] = 1;

            vertexFullData[vertexFullDataIndex++] = tx; 
            vertexFullData[vertexFullDataIndex++] = ty; 
        }
    }   

    mesh.Structure.SizeCheck();
    strcpy(mesh.Name, "<Sprite-Mesh>");

    ID = ResourceIDLoaded;
}

/*

void BF::Model::ConvertFrom(Shape& shape)
{
    /*
    const unsigned int meshSize = 1;
    List<Point<float>>* vertexData = shape.DrawPointList();
    unsigned int vertexListSize = vertexData->Size();
    Mesh* mesh;

    if ((vertexListSize % 3) == 0)
    {
        RenderInformation.RenderType = RenderMode::Triangle;
    }

    if ((vertexListSize % 4) == 0)
    {
        RenderInformation.RenderType = RenderMode::Square;
    }

    MeshList.ReSize(meshSize);

    mesh = &MeshList[0]; // Get current target Mesh

    strcpy(mesh->Name, "Shape");

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

    CalculateNormalVectors();

    UpdateGlobalMesh();*
}
*/

size_t BF::Model::FullSizeInMemory()
{
    return sizeof(Model);
}