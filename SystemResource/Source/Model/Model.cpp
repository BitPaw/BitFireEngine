#include "Model.h"

#include "ModelType.h"
#include "OBJ/OBJ.h"
#include "../File/File.h"
#include "../../../SystemResource/Source/Math/Geometry/Shape/Triangle.h"
#include "../../../SystemResource/Source/Math/Geometry/Shape/Rectangle.h"

BF::Model::Model()
{
    RenderInformation.RenderType = RenderMode::Unkown;
}

BF::Model::Model(const char* modelName)
{
    RenderInformation.RenderType = RenderMode::Unkown;

    strcpy(Name, modelName);
}

void BF::Model::Move(float x, float y, float z)
{
    Move(Vector3<float>(x, y, z));
}

void BF::Model::Move(Vector3<float> position)
{
    if (DirectMorth)
    {
        for (unsigned int i = 0; i < GlobalMesh.VertexList.Size(); i++)
        {
            GlobalMesh.VertexList[i]->CurrentPosition.Add(position);
        }

        //_currentPosition += position;
    }

    ModelMatrix.Move(position.X, position.Y, position.Z);
}

void BF::Model::MoveTo(float x, float y, float z)
{
    MoveTo(Vector3<float>(x, y, z));
}

void BF::Model::MoveTo(Vector3<float> position)
{
    if (DirectMorth)
    {
        for (unsigned int i = 0; i < GlobalMesh.VertexList.Size(); i++)
        {
            Vertex* vertex = GlobalMesh.VertexList[i];

            auto x = ModelMatrix.CurrentPosition();

            vertex->CurrentPosition -= Vector3<float>(x.X, x.Y, x.Z);
            vertex->CurrentPosition += position;
        }

        // _currentPosition = position;
    }

    ModelMatrix.MoveTo(position.X, position.Y, position.Z);
}

void BF::Model::Rotate(float x, float y, float z)
{
    Rotate(Vector3<float>(x, y, z));
}

void BF::Model::Rotate(Vector3<float> rotation)
{
    float xRadians = Math::DegreeToRadians(rotation.X);
    float yRadians = Math::DegreeToRadians(rotation.Y);
    float zRadians = Math::DegreeToRadians(rotation.Z);

    if (DirectMorth)
    {
        for (unsigned int i = 0; i < GlobalMesh.VertexList.Size(); i++)
        {
            Vertex* vertex = GlobalMesh.VertexList[i];
            Vector3<float>& currentPosition = vertex->CurrentPosition;

            auto x = ModelMatrix.CurrentRotation();
            Vector3<float> position(x.X, x.Y, x.Z);

            currentPosition -= position;
            currentPosition.Rotate(rotation);
            currentPosition += position;
        }

        /*
        _currentRotation += rotation;

        if (_currentRotation.X > 360)
        {
            _currentRotation.X -= 360;
        }

        if (_currentRotation.Y > 360)
        {
            _currentRotation.Y -= 360;
        }

        if (_currentRotation.Z > 360)
        {
            _currentRotation.Z -= 360;
        }*/
    }

    ModelMatrix.Rotate(xRadians, yRadians, zRadians);
}

void BF::Model::RotateTo(float x, float y, float z)
{
    ModelMatrix.RotateTo(x, y, z);
}

void BF::Model::RotateTo(Vector3<float> rotation)
{
    ModelMatrix.RotateTo(rotation.X, rotation.Y, rotation.Z);
}



void BF::Model::Orbit(float x, float y, float z)
{
    Orbit(Vector3<float>(x, y, z));
}

void BF::Model::Orbit(Vector3<float> rotation)
{
    for (unsigned int i = 0; i < GlobalMesh.VertexList.Size(); i++)
    {
        Vertex* vertex = GlobalMesh.VertexList[i];

        vertex->CurrentPosition.Rotate(rotation);
    }
}

void BF::Model::Orbit(Vector3<float> rotation, Vector3<float> ancerPosition)
{
    // ModelMatrix.Orbit();
}

void BF::Model::Scale(float x, float y, float z)
{
    Scale(Vector3<float>(x, y, z));
}

void BF::Model::Scale(Vector3<float> scaleFactor)
{
    if (DirectMorth)
    {
        for (unsigned int i = 0; i < GlobalMesh.VertexList.Size(); i++)
        {
            Vertex* vertex = GlobalMesh.VertexList[i];

            vertex->CurrentPosition *= scaleFactor;
        }
    }
    else
    {
        ModelMatrix.Scale(scaleFactor.X, scaleFactor.Y, scaleFactor.Z);
    }
}

void BF::Model::CalculateNormalVectors()
{
    /*
    for (unsigned int i = 0; i < MeshList.Size(); i++)
    {
        Mesh* mesh = &MeshList[i];
        List<MeshIndexData>* indexList = &mesh->IndexList;
        List<Vertex>* vertexList = &mesh->VertexList;
        unsigned int indexListSize = mesh->IndexList.Size();

        switch (indexListSize)
        {
            case 0:
                // Poligon has no points, there cant be a normal verctor.
                break;

            case 1:
                // Poligon has only one Point, normal will be teh point itself.

                break;

            case 2:
                // There are only 2 points, you cant render something like this. Or can it?
                break;

            case 3:
            default:
            {
                switch (RenderInformation.RenderType)
                {
                    case RenderMode::Triangle:
                    {
                        unsigned int i = 0;
                        unsigned int normalPointIndex = 0;
                        float normals = indexListSize / 3.0f;
                        unsigned int normalSaveVectorSize = Math::Floor(normals);
                        unsigned int normalExactVectorSize = Math::Ceiling(normals);
                        mesh->NormalPointList.ReSize(normalExactVectorSize);

                        while (normalPointIndex < normalSaveVectorSize)
                        {
                            MeshIndexData* mIndexA = &(*indexList)[i++];
                            MeshIndexData* mIndexB = &(*indexList)[i++];
                            MeshIndexData* mIndexC = &(*indexList)[i++];

                            Vertex* vertexA = &(*vertexList)[mIndexA->VertexPositionID];
                            Vertex* vertexB = &(*vertexList)[mIndexB->VertexPositionID];
                            Vertex* vertexC = &(*vertexList)[mIndexC->VertexPositionID];

                            Triangle triangle
                            (
                                vertexA->CurrentPosition,
                                vertexB->CurrentPosition,
                                vertexC->CurrentPosition
                            );

                            mIndexA->NormalVectorID = normalPointIndex;
                            mIndexB->NormalVectorID = normalPointIndex;
                            mIndexC->NormalVectorID = normalPointIndex;

                            mesh->NormalPointList[normalPointIndex++] = triangle.NormalDirection();
                        }

                        if (normalSaveVectorSize < normalExactVectorSize)
                        {
                            MeshIndexData* mIndexA = &(*indexList)[i - 1];
                            MeshIndexData* mIndexB = &(*indexList)[i];
                            MeshIndexData* mIndexC = &(*indexList)[0];

                            Vertex* vertexA = &(*vertexList)[mIndexA->VertexPositionID];
                            Vertex* vertexB = &(*vertexList)[mIndexB->VertexPositionID];
                            Vertex* vertexC = &(*vertexList)[mIndexC->VertexPositionID];

                            Triangle triangle
                            (
                                vertexA->CurrentPosition,
                                vertexB->CurrentPosition,
                                vertexC->CurrentPosition
                            );

                            mIndexA->NormalVectorID = normalPointIndex;
                            mIndexB->NormalVectorID = normalPointIndex;
                            mIndexC->NormalVectorID = normalPointIndex;

                            mesh->NormalPointList[normalPointIndex++] = triangle.NormalDirection();
                        }
                    }
                    break;

                    case RenderMode::Square:
                    {
                        unsigned int i = 0;
                        unsigned int normalPointIndex = 0;
                        float normals = indexListSize / 4.0f;
                        unsigned int normalSaveVectorSize = Math::Floor(normals);
                        unsigned int normalExactVectorSize = Math::Ceiling(normals);
                        mesh->NormalPointList.ReSize(normalExactVectorSize);

                        while (normalPointIndex < normalSaveVectorSize)
                        {
                            MeshIndexData* mIndexA = &(*indexList)[i];
                            MeshIndexData* mIndexB = &(*indexList)[i + 1];
                            MeshIndexData* mIndexC = &(*indexList)[i + 2];
                            MeshIndexData* mIndexD = &(*indexList)[i + 3];

                            Vertex* vertexA = &(*vertexList)[mIndexA->VertexPositionID];
                            Vertex* vertexB = &(*vertexList)[mIndexB->VertexPositionID];
                            Vertex* vertexC = &(*vertexList)[mIndexC->VertexPositionID];
                            Vertex* vertexD = &(*vertexList)[mIndexD->VertexPositionID];

                            Rectangle rectangle
                            (
                                vertexA->CurrentPosition,
                                vertexB->CurrentPosition,
                                vertexC->CurrentPosition,
                                vertexD->CurrentPosition
                            );

                            mIndexA->NormalVectorID = normalPointIndex;
                            mIndexB->NormalVectorID = normalPointIndex;
                            mIndexC->NormalVectorID = normalPointIndex;
                            mIndexD->NormalVectorID = normalPointIndex;

                            mesh->NormalPointList[normalPointIndex++] = rectangle.NormalDirection();
                        }

                        if (normalSaveVectorSize < normalExactVectorSize)
                        {
                            printf("Error");
                        }
                        break;
                    }


                    break;
                }
            }  
        }
    }
    */
}

void BF::Model::UseTexturePointAsColor()
{
    unsigned int indexListLength = GlobalMesh.IndexList.Size();

    ColorList.ReSize(indexListLength);

    for (unsigned int i = 0; i < indexListLength; i++)
    {
        MeshIndexData& meshIndexData = MeshList[0].IndexList[i];

        Vertex& vertex = MeshList[0].VertexList[meshIndexData.VertexPositionID];
        Vector2<float>& texturepoint = MeshList[0].TexturePointList[meshIndexData.TexturePointID];

        vertex.ColorID = i;

        ColorList[i].Set(texturepoint.X, texturepoint.Y, 0, 0);
    }

    UpdateGlobalMesh();
}

void BF::Model::PrintModelData()
{
    printf("Meshes %u\n", MeshList.Size());

    for (unsigned int i = 0; i < MeshList.Size(); i++)
    {
        Mesh& mesh = MeshList[i];

        printf("Material <%u>: %5u %5u %5u", i, mesh.VertexList.Size(), mesh.NormalPointList.Size(), mesh.TexturePointList.Size());

        if (mesh.MeshMaterial == nullptr)
        {
            printf(" - No Material\n");
        }
        else
        {
            Material* material = mesh.MeshMaterial;
            Image* texture = material->Texture;

            if (texture == nullptr)
            {
                printf(" - <NoImage> Path %s", &mesh.MeshMaterial->Name[0]);

            }
            else
            {
                printf(" - ImageID:%u Path %s", texture->ID, &mesh.MeshMaterial->Name[0]);
            }
        }

        printf("\n");
    }
}

void BF::Model::UpdateGlobalMesh()
{
    const unsigned int length = MeshList.Size();
    unsigned int vertexListLength = 0;
    unsigned int texturePointListLength = 0;
    unsigned int normalPointListLength = 0;
    unsigned int colorListLength = ColorList.Size();
    unsigned int indexListLength = 0;

    unsigned int vertexIndex = 0;
    unsigned int textureIndex = 0;
    unsigned int normalIndex = 0;
    unsigned int colorIndex = 0;
    unsigned int indexIndex = 0;
    
    if (length == 0)
    {
        return;
    }

    for (unsigned int i = 0; i < length; i++)
    {
        Mesh& mesh = MeshList[i];

        vertexListLength += mesh.VertexList.Size();
        texturePointListLength += mesh.TexturePointList.Size();
        normalPointListLength += mesh.NormalPointList.Size();
        indexListLength += mesh.IndexList.Size();
    }

    GlobalMesh.VertexList.ReSize(vertexListLength);
    GlobalMesh.TexturePointList.ReSize(texturePointListLength);
    GlobalMesh.NormalPointList.ReSize(normalPointListLength);
    GlobalMesh.ColorList.ReSize(colorListLength);
    GlobalMesh.IndexList.ReSize(indexListLength);

    for (unsigned int i = 0; i < length; i++)
    {
        Mesh& mesh = MeshList[i];

        vertexListLength = mesh.VertexList.Size();
        texturePointListLength = mesh.TexturePointList.Size();
        normalPointListLength = mesh.NormalPointList.Size();
        indexListLength = mesh.IndexList.Size();

        for (unsigned int i = 0; i < vertexListLength; i++)
        {
            GlobalMesh.VertexList[vertexIndex++] = &mesh.VertexList[i];
        }

        for (unsigned int i = 0; i < texturePointListLength; i++)
        {
            GlobalMesh.TexturePointList[textureIndex++] = &mesh.TexturePointList[i];
        }

        for (unsigned int i = 0; i < normalPointListLength; i++)
        {
            GlobalMesh.NormalPointList[normalIndex++] = &mesh.NormalPointList[i];
        }

        for (unsigned int i = 0; i < colorListLength; i++)
        {
            GlobalMesh.ColorList[colorIndex++] = &ColorList[i];
        }

        for (unsigned int i = 0; i < indexListLength; i++)
        {
            GlobalMesh.IndexList[indexIndex++] = &mesh.IndexList[i];
        }
    }
}

void BF::Model::ScaleTexturePoints(float x, float y)
{
    ScaleTexturePoints(Vector2<float>(x, y));
}

void BF::Model::ScaleTexturePoints(Vector2<float> scale)
{
    for (unsigned int i = 0; i < GlobalMesh.TexturePointList.Size(); i++)
    {
        GlobalMesh.TexturePointList[i]->Multiply(scale);
    }
}

BF::ModelType BF::Model::CheckFileExtension(const char* fileExtension)
{
    AsciiString extension(fileExtension);

    if (extension.CompareIgnoreCase("3ds")) return ModelType::A3DS;
    if (extension.CompareIgnoreCase("obj")) return ModelType::OBJ;
    if (extension.CompareIgnoreCase("ply")) return ModelType::PLY;
    if (extension.CompareIgnoreCase("stl")) return ModelType::STL;
    if (extension.CompareIgnoreCase("wrl")) return ModelType::WRL;

    return ModelType::UnKown;
}

BF::ResourceLoadingResult BF::Model::Load()
{
    return Load(FilePath);
}

BF::ResourceLoadingResult BF::Model::Load(const char* filePath)
{
    if (filePath == nullptr)
    {
        return ResourceLoadingResult::FileNotFound;
    }

    File file(filePath);
    ModelType modelType = CheckFileExtension(file.Extension);

    ID = ResourceIDCurrentlyLoading;
    strcpy(FilePath, filePath);

    switch (modelType)
    {
        case ModelType::A3DS:
            break;

        case ModelType::FBX:
            break;

        case ModelType::OBJ:
        {
            OBJ obj;
            obj.Load(filePath);
            obj.Convert(*this);
            break;
        }

        case ModelType::PLY:
            break;

        case ModelType::STL:
            break;

        case ModelType::WRL:
            break;

        case ModelType::UnKown:
        default:
            return ResourceLoadingResult::FormatNotSupported;
    }

    ID = ResourceIDReadyToBeCached;

    return ResourceLoadingResult::Successful;
}

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

    UpdateGlobalMesh();*/
}