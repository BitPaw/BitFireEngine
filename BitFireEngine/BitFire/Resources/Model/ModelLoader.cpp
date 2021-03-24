#include "ModelLoader.h"

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

BF::Model* BF::ModelLoader::LoadFromFile(AsciiString& filePath)
{
    Model* model = new Model();

    LoadFromFile(*model, filePath);

    return model;
}

void BF::ModelLoader::LoadFromFile(Model& model, AsciiString& filePath)
{
    TextFile textFile(filePath);
    AsciiString fileExtension = textFile.FileExtension;
    ModelType modelType = ParseModelType(fileExtension);

    model.FilePath.Copy(filePath);

    switch (modelType)
    {
    case BF::ModelType::A3DS:
        Log::Write(LogMessageType::Event, "[.3DS] Autodesk File detected.");
        break;

    case BF::ModelType::FBX:
        Log::Write(LogMessageType::Event, "[.FBX] FilmBox File detected.");
        break;

    case BF::ModelType::OBJ:
    {
        Log::Write(LogMessageType::Event, "[.OBJ] WaveFont File detected.");

        OBJ* obj = OBJLoader::LoadFromFile(filePath);

        ToModel(*obj, model);

        delete obj;

        break;
    }

    case BF::ModelType::PLY:
        Log::Write(LogMessageType::Event, "[.PLY] Polygon File detected.");
        break;

    case BF::ModelType::STL:
        Log::Write(LogMessageType::Event, "[.STL] Standard Triangle Language File detected.");
        break;

    case BF::ModelType::WRL:
        Log::Write(LogMessageType::Event, "[.WRL] World File detected.");
        break;

    case BF::ModelType::UnKown:
    default:
        throw "Unsuported Type/File";
    }
}

void BF::ModelLoader::SaveToFile(Model& model, AsciiString& filePath)
{

}

void BF::ModelLoader::ToModel(OBJ& waveFront, Model& model)
{
    bool usedNormals = false;
    unsigned int vertexListSize = waveFront.VertexStructureSize;

    if ((vertexListSize % 3) == 0)
    {
        model.RenderInformation.RenderType = RenderMode::Triangle;
    }

    if ((vertexListSize % 4) == 0)
    {
        model.RenderInformation.RenderType = RenderMode::Square;
    }

    model.MeshList.ReSize(waveFront.ElementList.Size()); 

    //unsigned int offset = 0;
    unsigned int size = model.MeshList.Size();
    unsigned int materialSize = waveFront.Materials.Size();

    if (materialSize > 0)
    {
        unsigned int materialSize = waveFront.Materials[0].MaterialList.Size();
        unsigned int colorIndex = 0;

        model.ColorList.ReSize(materialSize);

        for (unsigned int i = 0; i < waveFront.Materials.Size(); i++)
        {
            MTL* mtl = &waveFront.Materials[i];

            for (unsigned int j = 0; j < materialSize; j++)
            {
                Material* material = &mtl->MaterialList[j];

                float r = material->Diffuse.X;
                float g = material->Diffuse.Y;
                float b = material->Diffuse.Z;

                model.ColorList[colorIndex++].SetColor(r, g, b);
            }
        }
    }   

    for (unsigned int elementIndex = 0; elementIndex < size; elementIndex++)
    {
        OBJElement* element = &waveFront.ElementList[elementIndex]; // Get current source Mesh
        Mesh* mesh = &model.MeshList[elementIndex]; // Get current target Mesh
        unsigned int vertexListSize = element->VertexPositionList.Size();
        unsigned int faceElementListSize = element->FaceElementList.Size();      
        unsigned int normalListSize = element->VertexNormalPositionList.Size();
        unsigned int textureCoordinateListSize = element->TextureCoordinateList.Size();

        mesh->Name = element->Name;

        // Color

        // Vertex Data
        mesh->VertexList.ReSize(vertexListSize);
        for (unsigned int i = 0; i < vertexListSize; i++)
        {
            Vertex* vertex = &mesh->VertexList[i];
            vertex->ColorID = element->MaterialID;
            vertex->CurrentPosition = element->VertexPositionList[i];

            //printf("V: <%f|%f|%f> C:%u\n", vertex->CurrentPosition.X, vertex->CurrentPosition.Y, vertex->CurrentPosition.Z, vertex->ColorID);
        }

        mesh->TexturePointList.ReSize(textureCoordinateListSize);
        for (unsigned int i = 0; i < textureCoordinateListSize; i++)
        {
            mesh->TexturePointList[i] = element->TextureCoordinateList[i];
           // printf("T: <%f|%f>\n", mesh->TexturePointList[i].X, mesh->TexturePointList[i].Y);
        }        

        if (normalListSize > 0)
        {
            usedNormals = true;
            mesh->NormalPointList.ReSize(normalListSize);
            for (unsigned int i = 0; i < normalListSize; i++)
            {
                mesh->NormalPointList[i] = element->VertexNormalPositionList[i];
                //printf("N: <%f|%f|%f>\n", mesh->NormalPointList[i].X, mesh->NormalPointList[i].Y, mesh->NormalPointList[i].Z);
            }
        }     

        // Index Data
        mesh->IndexList.ReSize(faceElementListSize);
        for (unsigned int i = 0; i < faceElementListSize; i++)
        {
            Position<unsigned int>* indexPosition = &element->FaceElementList[i];
            MeshIndexData* meshData = &mesh->IndexList[i];
            meshData->VertexPositionID = indexPosition->X - 1;
            meshData->TexturePointID = indexPosition->Y - 1;
            meshData->NormalVectorID = indexPosition->Z - 1;

            //printf("F: <%5u|%5u|%5u>\n", meshData->VertexPositionID, meshData->TexturePointID, meshData->NormalVectorID);
        }
    }
   
    if (!usedNormals)
    {
        model.CalculateNormalVectors();
    }

    model.UpdateGlobalMesh();
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