#include "ModelLoader.h"
#include "../../OpenGL/OpenGLAPI.h"

BF::IModel* BF::ModelLoader::LoadFromFile(std::string filePath)
{
    IModel* model = nullptr;
    ModelType modelType = ModelType::UnKown;
    TextFile textFile(filePath);
    std::string fileExtension = textFile.GetFileExtension();

    bool is3DS = fileExtension == "3ds";
    bool isOBJ = fileExtension == "obj";
    bool isPLY = fileExtension == "ply";
    bool isSTL = fileExtension == "stl";
    bool isWRL = fileExtension == "wrl";

    if (is3DS) modelType = ModelType::A3DS;
    if (isOBJ) modelType = ModelType::OBJ;
    if (isPLY) modelType = ModelType::PLY;
    if (isSTL) modelType = ModelType::STL;
    if (isWRL) modelType = ModelType::WRL;

    switch (modelType)
    {
        case BF::ModelType::A3DS:
            MessageSystem::PushMessage(MessageType::Info, "[.3DS] Autodesk File detected.");
            break;

        case BF::ModelType::FBX:
            MessageSystem::PushMessage(MessageType::Info, "[.FBX] FilmBox File detected.");
            break;

        case BF::ModelType::OBJ:
        {
            MessageSystem::PushMessage(MessageType::Info, "[.OBJ] WaveFont File detected.");

            OBJ* obj = (OBJ*)OBJLoader::LoadFromFile(filePath);
            Model* m = OBJToModel(obj);

            OpenGLAPI* openGLAPI = OpenGLAPI::Instance();

            if (openGLAPI == nullptr)
            {
                // Error  
            }
            else
            {
                openGLAPI->Render->RegisterRenderModel(m);
            }

            model = m;

            break;
        }           

        case BF::ModelType::PLY:
            MessageSystem::PushMessage(MessageType::Info, "[.PLY] Polygon File detected.");
            break;

        case BF::ModelType::STL:
            MessageSystem::PushMessage(MessageType::Info, "[.STL] Standard Triangle Language File detected.");
            break;

        case BF::ModelType::WRL:
            MessageSystem::PushMessage(MessageType::Info, "[.WRL] World File detected.");
            break;

        case BF::ModelType::UnKown:
        default:
            throw "Unsuported Type/File";
    }

    return model;
}

void BF::ModelLoader::SaveToFile(std::string filePath)
{

}

BF::Model* BF::ModelLoader::OBJToModel(OBJ* waveFront)
{
    Model* model = new Model();

    model->MeshList.ReSize(waveFront->ElementList.Size.Value);

    unsigned int offset = 0;
    unsigned int size = model->MeshList.Size.Value;
    unsigned int materialSize = waveFront->Materials.Size.Value;

    if (materialSize > 0)
    {
        unsigned int materialSize = waveFront->Materials[0].MaterialList.Size.Value;
        unsigned int colorIndex = 0;

        model->ColorList.ReSize(materialSize);

        for (unsigned int i = 0; i < waveFront->Materials.Size.Value; i++)
        {
            MTL* mtl = &waveFront->Materials[i];

            for (unsigned int j = 0; j < materialSize; j++)
            {
                Material* material = &mtl->MaterialList[j];

                float r = material->Diffuse.X;
                float g = material->Diffuse.Y;
                float b = material->Diffuse.Z;

                model->ColorList[colorIndex++] = RGBA(r, g, b);
            }
        }
    }   

    for (unsigned int elementIndex = 0; elementIndex < size; elementIndex++)
    {
        OBJElement* element = &waveFront->ElementList[elementIndex]; // Get current source Mesh
        const unsigned int faceElementListSize = element->FaceElementList.Size.Value;

        Mesh* mesh = &model->MeshList[elementIndex]; // Get current target Mesh
        mesh->Name = element->Name;

        // Color

        // Vertex Data
        mesh->VertexList.ReSize(element->VertexPositionList.Size.Value);
        for (unsigned int i = 0; i < element->VertexPositionList.Size.Value; i++)
        {
            Vertex* vertex = &mesh->VertexList[i];
            vertex->ColorID = element->MaterialID;
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

    model->UpdateGlobalMesh();

    return model;
}