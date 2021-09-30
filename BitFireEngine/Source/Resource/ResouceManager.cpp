#include "ResouceManager.h"
#include "../../../SystemResource/Source/Font/FNT/FNTPage.h"
#include "../../../SystemResource/Source/File/File.h"
#include "../../../SystemResource/Source/Time/StopWatch.h"
#include "../../../SystemResource/Source/Game/SkyBox.h"
#include "../../../SystemResource/Source/Math/Physic/GravityField.h"
#include "../../../SystemRender/Source/OpenGLAPI.h"
#include <thread>


int _matrixModelID;
int _matrixViewID;
int _matrixProjectionID;
int _materialTextureID;
BF::RefreshRateMode RefreshRate;

void CameraDataGet(unsigned int shaderID)
{
    _matrixModelID = BF::OpenGLAPI::ShaderGetUniformLocationID(shaderID, "MatrixModel");
    _matrixViewID = BF::OpenGLAPI::ShaderGetUniformLocationID(shaderID, "MatrixView");
    _matrixProjectionID = BF::OpenGLAPI::ShaderGetUniformLocationID(shaderID, "MatrixProjection");
    _materialTextureID = BF::OpenGLAPI::ShaderGetUniformLocationID(shaderID, "MaterialTexture");
}

void CameraDataUpdate(BF::Camera& camera)
{
    //BF::OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixModelID, camera.MatrixModel.Data);
   BF::Matrix4x4<float> viewModel = BF::Matrix4x4<float>(camera.MatrixModel);

   //auto pos = camera.MatrixModel.CurrentPosition();

   //viewModel.Multiply(camera.MatrixModel);

   //viewModel.Move(camera.MatrixModel.Data[11], camera.MatrixModel.Data[12], camera.MatrixModel.Data[13]);

   //viewModel.Print();

   BF::OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixViewID, camera.MatrixView.Data);
    BF::OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixProjectionID, camera.MatrixProjection.Data);
}




void BF::ResourceManager::UpdateVBOData(Model& model)
{
    LinkedMesh& mesh = model.GlobalMesh;
    float* vertexData = model.RenderInformation.VertexData;
    unsigned int* indexData = model.RenderInformation.IndexData;
    unsigned int indexDataSize = mesh.IndexList.Size();
    bool validCall = model.RenderInformation.IndexDataSize > 0 && model.RenderInformation.VertexDataSize > 0;

    assert(validCall);
    assert(indexDataSize > 0);

    for (unsigned int i = 0; i < indexDataSize; i++)
    {
        MeshIndexData* indexList = mesh.IndexList[i];
        unsigned int vertexIndex = indexList->VertexPositionID;
        unsigned int textureIndex = indexList->TexturePointID;
        unsigned int normalIndex = indexList->NormalVectorID;

        assert(vertexIndex < mesh.VertexList.Size());
        assert(textureIndex < mesh.TexturePointList.Size());

        Vertex* vertex = mesh.VertexList[vertexIndex];

        Vector4<float> defaultColor(1, 1, 1, 1);
        Vector2<float> defaultTexturepoint;
        Vector3<float> normalPosition;

        Vector4<float>* color = &defaultColor;
        Vector3<float>* position = nullptr;
        Vector3<float>* normal = nullptr;
        Vector2<float>* texture = nullptr;          

        bool hasColor = !model.ColorList.IsEmpty() && vertex->ColorID != -1;
        bool hasNormal = !mesh.NormalPointList.IsEmpty();
        bool hasTexture = !mesh.TexturePointList.IsEmpty();
        
        position = &vertex->CurrentPosition;

        if (hasColor)
        {
            assert(vertex->ColorID <= model.ColorList.Size());

            color = &model.ColorList[vertex->ColorID];
        }

        if (hasNormal)
        {
            assert(normalIndex <= model.GlobalMesh.NormalPointList.Size());

            normal = model.GlobalMesh.NormalPointList[normalIndex];
        }

        texture = model.GlobalMesh.TexturePointList[textureIndex];
        indexData[i] = i;

        const unsigned int sizeOfAll = (3+3+4+2);
        const unsigned int sizeOfAllFloat = sizeOfAll * sizeof(float);

        assert(position != nullptr);
        assert(normal != nullptr);
        assert(color != nullptr);
        assert(texture != nullptr);

        float data[sizeOfAll]
        {
            position->X,
            position->Y,
            position->Z,

            normal->X,
            normal->Y,
            normal->Z,

            color->X,
            color->Y,
            color->Z,
            color->W,

            texture->X,
            texture->Y,
        };

        memcpy(vertexData, data, sizeOfAllFloat);
        vertexData += sizeOfAll;
    }

    //renderInformation->VertexDataLength = dataIndex - renderInformation->VertexDataPosition -1;
    //renderInformation->IndiceIndexLength = indiceIndex - renderInformation->IndiceIndex-1;
}

BF::ResourceManager::ResourceManager()
{
    _lastUsedShaderProgram = -1;
    _defaultShaderID = -1;
    _defaultTextureID = -1;

    DefaultFont = nullptr;

    _imageAdd.Create();
    _modelAdd.Create();
}

BF::ResourceManager::~ResourceManager()
{
    _imageAdd.Delete();
    _modelAdd.Delete();
    UnloadAll();
}

BF::Model* BF::ResourceManager::GetModel(unsigned int index)
{
    unsigned int currentIndex = 0;

    for (LinkedListNode<Model*>* node = _modelList.GetFirst(); node != nullptr; node = node->Next)
    {
        Model* model = node->Element;

        if (index == currentIndex++)
        {
            return model;
        }
    }

    return nullptr;
}

void BF::ResourceManager::UnloadAll()
{

}

void BF::ResourceManager::PushToGPU(Model& model)
{
    unsigned int& modelID = model.ID;
    bool isAlreadyLinked = (int)modelID > 0;
    bool isUsable = modelID == ResourceIDLoaded || isAlreadyLinked;
    ModelRenderInformation& renderInfo = model.RenderInformation;

    modelID = ResourceIDLoading;

    if (!isUsable)
    {
        return;
    }

    if (isAlreadyLinked)
    {
        UpdateVBOData(model);

        if (renderInfo.VertexDataSize > 0)
        {
            OpenGLAPI::VertexArrayUpdate(renderInfo.VertexBufferID, renderInfo.VertexDataSize * sizeof(float), renderInfo.VertexData);
        }
    }
    else
    {
        modelID = _modelList.Size();

        unsigned int vertexDataSize = 3 + 3 + 4 + 2;

        renderInfo.Allocate(vertexDataSize, model.GlobalMesh.IndexList.Size());        

        //printf("\n\nBEFORE\n\n");

        //renderInfo.PrintGPUData();

        UpdateVBOData(model);

        //printf("\n\nAFTER\n\n");

        //renderInfo.PrintGPUData();

        // Allocate GPU Buffer
        OpenGLAPI::VertexArrayDefine(&renderInfo.VertexArrayID);
        OpenGLAPI::VertexArrayBind(renderInfo.VertexArrayID);

        OpenGLAPI::VertexDataDefine(&renderInfo.VertexBufferID, renderInfo.VertexDataSize * sizeof(float), renderInfo.VertexData);

        unsigned int sizeList[4] = { 3,3,4,2 };

        OpenGLAPI::VertexAttributeArrayDefine(sizeof(float), 4, sizeList);

        OpenGLAPI::IndexDataDefine(&renderInfo.IndexBufferID, renderInfo.IndexDataSize * sizeof(unsigned int), renderInfo.IndexData);
    }
}

void BF::ResourceManager::PushToGPU(Image& image)
{
    if (image.ID == ResourceIDLoaded)
    {
        OpenGLAPI::RegisterImage(image);

        if (_defaultTextureID == -1)
        {
            _defaultTextureID = image.ID;
        }
    }   
}

void BF::ResourceManager::CheckUncachedData()
{  
    for (LinkedListNode<Model*>* node = _modelList.GetFirst(); node != nullptr; node = node->Next)
    {
        Model* model = node->Element;

        if (model->ID == ResourceIDLoaded)
        {
            PushToGPU(*model);

            //model->PrintModelData();
        }    
    }

    for (LinkedListNode<Image*>* node = _imageList.GetFirst() ; node != nullptr ; node = node->Next)
    {
        Image* image = node->Element;

        if (image->ID == ResourceIDLoaded)
        {
            PushToGPU(*image);

            //image->PrintData();
        }
    }
}

BF::Resource* BF::ResourceManager::Load(const char* filePath)
{
    Resource* resource = nullptr;
    ResourceType resourceType = ResourceType::Unknown;

    {
        bool isModel = Model::FileFormatPeek(filePath) != ModelType::UnKown;
        bool isImage = Image::FileFormatPeek(filePath) != ImageFileExtension::Unkown;
        bool isSound = Sound::FileFormatPeek(filePath) != SoundFormat::Unkown;
        bool isFont = Font::FileFormatPeek(filePath) != FontFormat::Unkown;
        bool isShader = false;
        bool isDialog = false;
        bool isLevel = Level::IsLevelFile(filePath);

        if (isModel) resourceType = ResourceType::Model;
        if (isImage) resourceType = ResourceType::Image;
        if (isSound) resourceType = ResourceType::Sound;
        if (isFont) resourceType = ResourceType::Font;
        if (isShader) resourceType = ResourceType::Shader;
        if (isDialog) resourceType = ResourceType::Dialog;
        if (isLevel) resourceType = ResourceType::Level;
    }

    switch (resourceType)
    {
        case ResourceType::Dialog:
        {
            Dialog* dialog = new Dialog();

            Load(*dialog, filePath);

            resource = dialog;

            break;
        }

        case ResourceType::Font:
        {
            Font* font = new Font();

            Load(*font, filePath);

            resource = font;

            break;
        }

        case ResourceType::Image:
        {
            Image* image = new Image();

            Load(*image, filePath);

            resource = image;

            break;
        }

        case ResourceType::Level:
        {
            Level* level = new Level();

            Load(*level, filePath);

            resource = level;

            break;
        }

        case ResourceType::Model:
        {
            Model* model = new Model();

            Load(*model, filePath);

            resource = model;

            break;
        }
        case ResourceType::Shader:
        {
            break;
        }
        case ResourceType::Sound:
        {
            Sound* sound = new Sound();

            Load(*sound, filePath);

            resource = sound;

            break;
        }
    }

    return resource;
}

void BF::ResourceManager::Load(Model& model, const char* filePath)
{
    model.MarkAsLoading("<Unnamed-Model>", filePath);

    Add(model);

    std::thread* modelLoaderThread = new std::thread([](ResourceManager* resourceManager, Model* model)
    {
        ResourceLoadingResult errorCode = model->Load();

        if (errorCode == ResourceLoadingResult::Successful)
        {
            model->ID = ResourceIDLoaded;

            for (unsigned int i = 0; i < model->MaterialList.Size(); i++)
            {
                Material& modelMaterial = model->MaterialList[i];

                std::thread* asy = new std::thread([](ResourceManager* resourceManager, Material* material)
                {
                    Image* image = new Image();

                    image->ID = ResourceIDLoading;
  
                    resourceManager->Add(*image);

                    ResourceLoadingResult errorCode = image->Load(material->TextureFilePath);                    

                    if (errorCode == ResourceLoadingResult::Successful)
                    {
                        material->Texture = image;
                    }

                }, resourceManager, &modelMaterial);
            }
        }

    }, this, &model);
}

void BF::ResourceManager::Load(Image& image, const char* filePath)
{
    Add(image);

   image.Load(filePath);   
}

void BF::ResourceManager::Load(Sound& sound, const char* filePath)
{
    //Add(sound);
}

void BF::ResourceManager::Load(Font& font, const char* filePath)
{
    Add(font);

    ResourceLoadingResult errorCode = font.Load(filePath);

    if (errorCode == ResourceLoadingResult::Successful)
    {
        for (unsigned int i = 0; i < font.AdditionalResourceListSize; i++)
        {
            AsciiString path(filePath);
            char* resourcePath = &font.AdditionalResourceList[i];          
            char textureFilePath[50];
            memset(textureFilePath, 0, 50);

            int resourcePathSize = strlen(resourcePath);
            int startIndex = path.FindLast('/') + 1;

            memcpy(textureFilePath, filePath, startIndex);

            int length = strlen(textureFilePath);

            memcpy(&textureFilePath[length], &resourcePath[0], resourcePathSize);
            
            // Does file exist?

            font.Texture = new Image();

           // errorCode = ErrorCode::FileNotFound;
            Load(*font.Texture, textureFilePath);

            if (errorCode != ResourceLoadingResult::Successful)
            {
                delete font.Texture;
                font.Texture = nullptr;
            }
        }

        font.ID = _fontList.Size();

        strcpy(font.FilePath, filePath);
    }
}

void BF::ResourceManager::Load(ShaderProgram& resource, const char* filePath)
{

}

void BF::ResourceManager::Load(Dialog& resource, const char* filePath)
{

}

void BF::ResourceManager::Load(Level& level, const char* filePath)
{
    File file(filePath);

    const char _modelToken = 'O';
    const char _textureToken = 'T';
    const char _musicToken = 'M';
    const char _fontToken = 'F';
    const char _shaderToken = 'S';
    const char _dialogToken = 'D';
    const char _emptyToken = ' ';
    const char _commentToken = '#';
    unsigned int modelCounter = 0;
    unsigned int imageCounter = 0;
    unsigned int soundCounter = 0;
    unsigned int fontCounter = 0;
    unsigned int shaderCounter = 0;
    unsigned int dialogCounter = 0;

    ResourceLoadingResult resourceLoadingResult = file.ReadFromDisk();
    unsigned int amountOfLines = file.CountAmountOfLines();
    char currentLineBuffer[200];

    if (resourceLoadingResult != ResourceLoadingResult::Successful)
    {
        return;
    }

    // Step I - Count objects
    while (file.ReadNextLineInto(currentLineBuffer))
    {
        char character = currentLineBuffer[0];

        switch (character)
        {
            case _modelToken:
                modelCounter++;
                break;

            case _textureToken:
                imageCounter++;
                break;

            case _musicToken:
                soundCounter++;
                break;

            case _fontToken:
                fontCounter++;
                break;

            case _shaderToken:
                shaderCounter++;
                break;

            case _dialogToken:
                dialogCounter++;
                break;

            case _commentToken:
            case _emptyToken:
            default:
                // Do nothinf
                break;
        }
    }

    // Step II - Reserve space
    level.ModelList.ReSize(modelCounter);
    level.ImageList.ReSize(imageCounter);
    level.SoundList.ReSize(soundCounter);
    level.FontList.ReSize(fontCounter);
    level.ShaderList.ReSize(shaderCounter);
    level.DialogList.ReSize(dialogCounter);

    modelCounter = 0;
    imageCounter = 0;
    soundCounter = 0;
    fontCounter = 0;
    shaderCounter = 0;
    dialogCounter = 0;

    file.CursorToBeginning();

    // Step II - Parse and Load
    while (file.ReadNextLineInto(currentLineBuffer))
    {
        char character = currentLineBuffer[0];
        char dummyBuffer[30];
        char path[120];

        switch (character)
        {
            case _modelToken:
            {
                char positionText[30];
                char rotationText[30];
                char scaleText[30];
                Vector3<float> position;
                Vector3<float> rotation;
                Vector3<float> scale;

                sscanf(currentLineBuffer, "%s %s %s %s %s", dummyBuffer, path, positionText, rotationText, scaleText);


                

                // Get raw Data-------------------------                         

                // Replace 0|0|0 -> 0 0 0 
                for (size_t i = 0; positionText[i] != '\0'; i++)
                {
                    if (positionText[i] == '|')
                    {
                        positionText[i] = ' ';
                    }
                }

                for (size_t i = 0; rotationText[i] != '\0'; i++)
                {
                    if (rotationText[i] == '|')
                    {
                        rotationText[i] = ' ';
                    }
                }

                for (size_t i = 0; scaleText[i] != '\0'; i++)
                {
                    if (scaleText[i] == '|')
                    {
                        scaleText[i] = ' ';
                    }
                }

                sscanf(positionText, "%f %f %f", &position.X, &position.Y, &position.Z);
                sscanf(rotationText, "%f %f %f", &rotation.X, &rotation.Y, &rotation.Z);
                sscanf(scaleText, "%f %f %f", &scale.X, &scale.Y, &scale.Z);
                //------------------------------------------------

                // Load Model----------------
                Model* loadedModel = new Model(); 

                Load(*loadedModel, path);

                if (loadedModel == nullptr)
                {
                    printf("[Warning] Loading failed!\n");
                    break;
                }

                level.ModelList[modelCounter++] = loadedModel;
                //-------------------

                rotation.X = Math::DegreeToRadians(rotation.X);
                rotation.Y = Math::DegreeToRadians(rotation.Y);
                rotation.Z = Math::DegreeToRadians(rotation.Z);

                //--[Apply Data]-------------
                //loadedModel->DirectMorth = false;
                //loadedModel->ModelMatrix.Move(position);
                //loadedModel->ModelMatrix.Rotate(rotation);
                loadedModel->MatrixModel.Scale(scale);
                //loadedModel->UpdateGlobalMesh();

                //Add(*loadedModel);
                //-----------------------
                break;
            }
            case _textureToken:
            {
                sscanf(currentLineBuffer, "%s %s", dummyBuffer, path);

                Image* image = new Image();

                Add(*image);

                Load(*image, path);      

                level.ImageList[imageCounter++] = image;
                break;
            }
            case _musicToken:
            {
                sscanf(currentLineBuffer, "%s %s", dummyBuffer, path);

                Sound* sound = new Sound();
                
                Load(*sound, path);

                level.SoundList[soundCounter++] = sound;
                break;
            }
            case _fontToken:
            {
                sscanf(currentLineBuffer, "%s %s", dummyBuffer, path);

                Font* font = new Font();
                
                Load(*font, path);          

                level.FontList[fontCounter++] = font;

                for (size_t i = 0; i < font->AdditionalResourceListSize; i++)
                {
                    font->AdditionalResourceList[i];
                }

                Add(*font);
                break;
            }
            case _shaderToken:
            {
                break;
            }
            case _dialogToken:
            {
                break;
            }
            case _commentToken:
            case _emptyToken:
            default:
                // Do nothinf
                break;
        }
    }
}

void BF::ResourceManager::Load(ShaderProgram& shaderProgram, const char* vertexShader, const char* fragmentShader)
{
    shaderProgram.AddShader(vertexShader, fragmentShader);
    shaderProgram.Load();

    bool validShader = OpenGLAPI::ShaderCompile(shaderProgram);

    if (validShader)
    {
        Add(shaderProgram);
    }
}

void BF::ResourceManager::Load
(
    SkyBox& skyBox, 
    const char* shaderVertex,
    const char* shaderFragment,
    const char* textureRight,
    const char* textureLeft, 
    const char* textureTop, 
    const char* textureBottom, 
    const char* textureBack, 
    const char* textureFront)
{
    Load(skyBox.Faces[0], textureRight);
    Load(skyBox.Faces[1], textureLeft);
    Load(skyBox.Faces[2], textureTop);
    Load(skyBox.Faces[3], textureBottom);
    Load(skyBox.Faces[4], textureBack);
    Load(skyBox.Faces[5], textureFront);

    Load(skyBox.Shader, shaderVertex, shaderFragment);

    Add(skyBox);
}

void BF::ResourceManager::Add(Model& model)
{
    _modelAdd.Lock();
    _modelList.Add(&model);
    _modelAdd.Release();
}

void BF::ResourceManager::Add(Image& image)
{  
    _imageAdd.Lock();
    _imageList.Add(&image);
    _imageAdd.Release();
}

void BF::ResourceManager::Add(Font& font)
{
    bool firstImage = _fontList.Size() == 0;
    bool isRegistered = font.ID != -1;

    if (!isRegistered)
    {
        _fontList.Add(&font);
    }

    if (firstImage)
    {
        DefaultFont = &font;
    }
}

void BF::ResourceManager::Add(ShaderProgram& shaderProgram)
{
    bool firstShaderProgram = _shaderProgramList.Size() == 0;
    bool isRegistered = shaderProgram.ID != -1;

    if (isRegistered)
    {
        _shaderProgramList.Add(&shaderProgram);
    }

    if (firstShaderProgram)
    {
        _defaultShaderID = shaderProgram.ID;

        CameraDataGet(_defaultShaderID);
    }
}

void BF::ResourceManager::Add(SkyBox& skyBox)
{
    

    OpenGLAPI::SkyBoxSet(skyBox);
  // OpenGLAPI::SkyBoxUse(skyBox);

    DefaultSkyBox = &skyBox;
}

void BF::ResourceManager::Add(Collider* collider)
{
    _physicList.Add(collider);
}

// TODO: This Funktion is very inefficient! O(n^2)
void BF::ResourceManager::ModelsPhysicsApply(float deltaTime)
{      
    for (LinkedListNode<Collider*>* colliderNode = _physicList.GetFirst(); colliderNode != nullptr; colliderNode = colliderNode->Next)
    {
        Collider* collider = colliderNode->Element;

        for (LinkedListNode<Model*>* modelNode = _modelList.GetFirst(); modelNode != nullptr; modelNode = modelNode->Next)
        {
            Model* model = modelNode->Element;
            Vector4<float> modelPositionx4 = model->MatrixModel.CurrentPosition();
            Vector3<float> modelPosition(modelPositionx4.X, modelPositionx4.Y, modelPositionx4.Z);
            bool isColliding = collider->IsColliding(modelPosition);            

            if (isColliding && model->EnablePhysics)
            {
                switch (collider->Type)
                {
                    case ColliderType::Gravity:
                    {
                        GravityField* gravityField = (GravityField*)collider;

                        model->ApplyGravity(gravityField->PullForce, deltaTime);
                        break;
                    }
                    case ColliderType::HitBox:
                    {
                        break;
                    }
                    case ColliderType::EffectBox:
                    {
                        break;
                    }
                }           
            }
        }
    }  
}

void BF::ResourceManager::ModelsRender(float deltaTime)
{
    OpenGLAPI::RenderClear();

    MainCamera.Update(deltaTime);

    // Render Skybox first, if it is used
    {
        bool hasSkyBox = DefaultSkyBox != nullptr;

        if (hasSkyBox)
        {
            unsigned int shaderID = DefaultSkyBox->Shader.ID;
            Matrix4x4<float> viewTri(MainCamera.MatrixView);

            viewTri.ResetForthAxis();

            OpenGLAPI::DepthMaskEnable(false);
            OpenGLAPI::DrawOrder(true);          

            OpenGLAPI::UseShaderProgram(shaderID);
            _lastUsedShaderProgram = shaderID;

            CameraDataGet(shaderID);        
            CameraDataUpdate(MainCamera);                               

            OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixViewID, viewTri.Data);

            OpenGLAPI::SkyBoxUse(*DefaultSkyBox);

            OpenGLAPI::Render(RenderMode::Triangle, 0, DefaultSkyBox->VertexListSize);

            OpenGLAPI::DepthMaskEnable(true);
            OpenGLAPI::DrawOrder(false);
        }
    }

    for (LinkedListNode<Model*>* currentModel = _modelList.GetFirst() ; currentModel != nullptr ; currentModel = currentModel->Next)
    {
        Model* model = currentModel->Element;
        ModelRenderInformation& renderInfo = model->RenderInformation;
        unsigned int shaderProgramID = renderInfo.ShaderProgramID;
        bool useDefaultShader = shaderProgramID == -1;
        bool changeShader = shaderProgramID != _lastUsedShaderProgram;
        bool isRegistered = ((int)model->ID) >= 0;
        bool skipRendering = !(renderInfo.ShouldItBeRendered && isRegistered);
       
        if (skipRendering)
        {
            continue;
        }

        assert(isRegistered);

        if (useDefaultShader)
        {
            shaderProgramID = _defaultShaderID;
            changeShader = shaderProgramID != _lastUsedShaderProgram;
        }

        OpenGLAPI::VertexArrayBind(renderInfo.VertexArrayID);

        //-----[Shader Lookup]--------------------------------------------------------------------
        if (changeShader)
        {
            OpenGLAPI::UseShaderProgram(shaderProgramID);

            _lastUsedShaderProgram = shaderProgramID;

            CameraDataGet(shaderProgramID);  
        }

        CameraDataUpdate(MainCamera);

        unsigned int currentIndex = 0;

        for (unsigned int i = 0; i < model->MeshList.Size(); i++)
        {
            Mesh& mesh = model->MeshList[i];
            Material* material = mesh.MeshMaterial;    
            unsigned int textureID = _defaultTextureID;
            unsigned int amountToRender = 0; 
            bool hasMaterial = material != nullptr;

            if (hasMaterial)
            {
                Image* texture = material->Texture;
                bool hasTexture = texture != nullptr;

                if (hasTexture)
                {
                    textureID = texture->ID;      

                    OpenGLAPI::TextureUse(texture->Type, textureID);
                }
            }
            else
            {
                OpenGLAPI::TextureUse(ImageType::Texture2D, textureID);
            }     

            OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixModelID, model->MatrixModel.Data);

            //---RenderStyle-------------------------
            if (renderInfo.RenderType != RenderMode::Unkown)
            {
                amountToRender = mesh.IndexList.Size();

                OpenGLAPI::Render(renderInfo.RenderType, currentIndex, amountToRender);      

                currentIndex += amountToRender;
            }
            //------------------------------------------------------------------------------
        }
    }
}

void BF::ResourceManager::PrintContent(bool detailed)
{
    unsigned int modelListSize = _modelList.Size();
    unsigned int imageListSize = _imageList.Size();
    unsigned int soundListSize = _soundList.Size();
    unsigned int shaderListSize = _shaderProgramList.Size();
    unsigned int fontListSize = _fontList.Size();
    unsigned int dialogListSize = _dialogList.Size();

    if (detailed)
    {
        const char* message =
            "+-----------------------------------------------------------------------------+\r\n"
            "|   %-73s |\n"
            "+-----+-----------------------+--------------------------------------+--------+\n"
            "|  ID | Name                  | Source - FilePath                    | Size   |\n"
            "+-----+-----------------------+--------------------------------------+--------+\n";

        const char* endLine = "+-----+-----------------------+--------------------------------------+--------+\n\n";

        const char* line = "| %3i | %-21s | %-36s | %4i B |\n";

    
        printf(message, "Models");

        LinkedListNode<Model*>* currentModel = _modelList.GetFirst();

        while (currentModel != nullptr)
        {
            Model* model = currentModel->Element;

            printf(line, model->ID, model->Name, model->FilePath, sizeof(*model));

            currentModel = currentModel->Next;
        }

        printf(endLine);
        printf(message, "Images");

        LinkedListNode<Image*>* currentImage = _imageList.GetFirst();

        while (currentImage != nullptr)
        {
            Image* image = currentImage->Element;

            printf(line, image->ID, image->Name, image->FilePath, sizeof(*image));
     
            //printf("| %2s | %s-%-11s | %s\n", buffer, ImageFormatToString(image->Format), ImageTypeToString(image->Type), image->FilePath);

            currentImage = currentImage->Next;
        }

        printf(endLine);
        printf(message, "Sounds");

        for (size_t i = 0; i < soundListSize; i++)
        {

        }

        printf(endLine);
        printf(message, "Font");


        LinkedListNode<Font*>* currentFont = _fontList.GetFirst();

        while (currentFont != nullptr)
        {
            Font* font = currentFont->Element;

            printf("| ID:%u Font Source: %s\n", font->ID, &font->FilePath[0]);

            currentFont = currentFont->Next;
        }

        printf(endLine);
        printf(message, "Shader");

        LinkedListNode<ShaderProgram*>* currentChaderProgram = _shaderProgramList.GetFirst();

        while (currentChaderProgram != nullptr)
        {
            ShaderProgram* shaderProgram = currentChaderProgram->Element;

            printf("| ID:%u ShaderProgram\n", shaderProgram->ID);

            for (size_t i = 0; i < 2; i++)
            {
                Shader& shader = shaderProgram->ShaderList[i];                

                printf("| - Sub-Shader ID:%u Type:%u Source:%s\n", shader.ID, shader.Type, &shader.FilePath[0]);
            }

            currentChaderProgram = currentChaderProgram->Next;
        }

        printf(endLine);
        printf(message, "Dialog");

        for (size_t i = 0; i < dialogListSize; i++)
        {

        }
   
        printf(endLine);
    }
    else
    {
        const char* message =
            "+--------------------------------------------------+\n"
            "| Loaded Resources\n"
            "| - Models <%u>\n"
            "| - Image  <%u>\n"
            "| - Sound  <%u>\n"
            "| - Font   <%u>\n"
            "| - Shader <%u>\n"
            "| - Dialog <%u>\n"
            "+--------------------------------------------------+\n";

        printf
        (
            message,
            modelListSize,
            imageListSize,
            soundListSize,
            shaderListSize,
            fontListSize,
            dialogListSize
        );
    }
}