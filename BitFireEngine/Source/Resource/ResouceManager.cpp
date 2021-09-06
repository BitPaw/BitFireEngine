#include "ResouceManager.h"
#include "../../../SystemResource/Source/Font/FNT/FNTPage.h"
#include "../../../SystemResource/Source/File/File.h"
#include "../../../SystemResource/Source/Time/StopWatch.h"
#include "../../../SystemResource/Source/Game/SkyBox.h"
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
    List<float>& vertexData = model.RenderInformation.VertexData;
    List<unsigned int>& indexData = model.RenderInformation.IndexData;

    unsigned int dataIndex = 0;// renderInformation->VertexDataPosition;
    //unsigned int indiceIndex = renderInformation->IndiceIndex;

   // printf("Update: <%p> <%.2u> %s\n", renderInformation, renderInformation->RenderID, &(renderInformation->RenderModel->ModelName[0]));

    if (model.RenderInformation.IndexData.Size() == 0)
    {

        printf("[Could not UpdateVBOData(), index data empty or not set.]\n");
        return;
    }

    for (unsigned int i = 0; i < mesh.IndexList.Size(); i++)
    {
        assert(i <= mesh.IndexList.Size(), "[x][ResourceManager][UpdateVBOData] illegal MeshIndexData index.");

        MeshIndexData* indexList = mesh.IndexList[i];

        Vector4<float> defaultColor(1, 1, 1, 1);
        Vector2<float> defaultTexturepoint;
        Vector3<float> normalPosition;

        Vector4<float>* color = &defaultColor;
        Vector3<float>* position = nullptr;
        Vector3<float>* normal = nullptr;
        Vector2<float>* texture = nullptr;

        unsigned int vertexIndex = indexList->VertexPositionID;
        unsigned int textureIndex = indexList->TexturePointID;
        unsigned int normalIndex = indexList->NormalVectorID;

        assert(vertexIndex < mesh.VertexList.Size(), "[x][] Invalid Index.");

        Vertex* vertex = mesh.VertexList[vertexIndex];

        bool hasColor = !model.ColorList.IsEmpty() && vertex->ColorID != -1;
        bool hasNormal = !mesh.NormalPointList.IsEmpty();
        bool hasTexture = !mesh.TexturePointList.IsEmpty();
        
        position = &vertex->CurrentPosition;

        if (hasColor)
        {
            assert(vertex->ColorID <= model.ColorList.Size(), "[x][] Invalid Index.");

            color = &model.ColorList[vertex->ColorID];
        }

        if (hasNormal)
        {
            assert(normalIndex <= model.GlobalMesh.NormalPointList.Size(), "[x][] Invalid Index.");

            normal = model.GlobalMesh.NormalPointList[normalIndex];
        }

        if (hasTexture)
        {
            assert(textureIndex <= model.GlobalMesh.TexturePointList.Size(), "[x][] Invalid Index.");

            texture = model.GlobalMesh.TexturePointList[textureIndex];
        }       

        indexData[i] = i;

        vertexData[dataIndex++] = position->X;
        vertexData[dataIndex++] = position->Y;
        vertexData[dataIndex++] = position->Z;

        vertexData[dataIndex++] = normal->X;
        vertexData[dataIndex++] = normal->Y;
        vertexData[dataIndex++] = normal->Z;

        void* destination = &vertexData[dataIndex++];
        void* source = color;

        memcpy(destination, source, 4 * sizeof(float));

        dataIndex += 3;

        vertexData[dataIndex++] = texture->X;
        vertexData[dataIndex++] = texture->Y;
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
    bool isUsable = modelID == ResourceIDReadyToUpload || isAlreadyLinked;
    ModelRenderInformation& renderInfo = model.RenderInformation;

    modelID = ResourceIDCurrentlyLoading;

    if (!isUsable)
    {
        return;
    }

    if (isAlreadyLinked)
    {
        UpdateVBOData(model);

        if (renderInfo.VertexData.Size() != 0)
        {
            OpenGLAPI::VertexArrayUpdate(renderInfo.VertexBufferID, renderInfo.VertexData.SizeInBytes(), &renderInfo.VertexData[0]);
        }
    }
    else
    {
        modelID = _modelList.Size();

        renderInfo.VertexData.ReSize(model.GlobalMesh.IndexList.Size() * (3 + 3 + 4 + 2));
        renderInfo.IndexData.ReSize(model.GlobalMesh.IndexList.Size());

        UpdateVBOData(model);

        // Allocate GPU Buffer
        OpenGLAPI::VertexArrayDefine(&renderInfo.VertexArrayID);
        OpenGLAPI::VertexArrayBind(renderInfo.VertexArrayID);

        OpenGLAPI::VertexDataDefine(&renderInfo.VertexBufferID, sizeof(float) * renderInfo.VertexData.Size(), &renderInfo.VertexData[0]);

        int sizeList[4] = { 3,3,4,2 };

        OpenGLAPI::VertexAttributeArrayDefine(sizeof(float), 4, sizeList);

        OpenGLAPI::IndexDataDefine(&renderInfo.IndexBufferID, renderInfo.IndexData.SizeInBytes(), &renderInfo.IndexData[0]);
    }
}

void BF::ResourceManager::PushToGPU(Image& image)
{
    if (image.ID == ResourceIDReadyToUpload)
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

        if (model->ID == ResourceIDReadyToUpload)
        {
            PushToGPU(*model);
        }    
    }

    for (LinkedListNode<Image*>* node = _imageList.GetFirst() ; node != nullptr ; node = node->Next)
    {
        Image* image = node->Element;

        if (image->ID == ResourceIDReadyToUpload)
        {
            PushToGPU(*image);
        }
    }
}

BF::Resource* BF::ResourceManager::Load(const char* filePathString, ResourceLoadMode resourceLoadMode)
{
    Resource* resource = nullptr;
    ResourceType resourceType = ResourceType::Unknown;
    File file(filePathString);
    AsciiString fileExtension(&file.Extension[0]);
    bool doesFileExist = file.DoesFileExist();
    ResourceLoadingResult errorCode;
    AsciiString filePath(filePathString);

    if (doesFileExist)
    {
        {
            bool isModel = Model::CheckFileExtension(file.Extension) != ModelType::UnKown;
            bool isImage = Image::CheckFileExtension(fileExtension) != ImageFileExtension::Unkown;
            bool isSound = false;
            bool isFont = Font::IsFontFile(file.Extension);
            bool isShader = false;
            bool isDialog = false;
            bool isLevel = fileExtension.CompareIgnoreCase("lev");

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
                errorCode = Load(*dialog, filePathString);
                break;
            }            

            case ResourceType::Font:
            {
                Font* font = new Font();
                errorCode = Load(*font, filePathString);

                if (errorCode == ResourceLoadingResult::Successful)
                {
                    Add(*font);
                    resource = font;
                }

                break;
            }

            case ResourceType::Image:
            {
                Image* image = new Image();
                errorCode = Load(*image, filePathString);

                if (errorCode == ResourceLoadingResult::Successful)
                {
                    Add(*image);
                    resource = image;
                }

                break;
            }

            case ResourceType::Level:
            {        
                Level* level = new Level();
                errorCode = Load(*level, filePathString);
                break;
            }

            case ResourceType::Model:
            {        
                Model* model = new Model();
                errorCode = Load(*model, filePathString);
                
                if (errorCode == ResourceLoadingResult::Successful)
                {
                    Add(*model);
                    resource = model;
                }

                break;
            }
            case ResourceType::Shader:
            {
       
                break;
            }
            case ResourceType::Sound:
            {
                Sound* sound = new Sound();
                errorCode = Load(*sound, filePathString);

                break;
            }
        }
    }
    else
    {
        errorCode = ResourceLoadingResult::FileNotFound;
    }

    switch (errorCode)
    {
        case ResourceLoadingResult::Successful:
        {
            break;
        }
        case ResourceLoadingResult::FormatNotSupported:
        {
            printf
            (
                "[Warning] Fileextension <%s> is not supported or reconised by the system!\n"
                "          Resource at path <%s> could not be loaded\n",
                &fileExtension[0],
                &filePath[0]
            );
            break;
        }
        case ResourceLoadingResult::FileNotFound:
        {
            printf("[Error] File is missing at path <%s>\n", &filePath[0]);
            break;
        }
        case ResourceLoadingResult::OutOfMemory:
        {
            printf("[Error] System is out of memory! File couldn't load at path <%s>\n", &filePath[0]);
            break;
        }
    }

    return resource;
}

static int inmageID = 0;

void BF::ResourceManager::LoadAsync(const char* filePath)
{
    Image* image = new Image();
    ResourceLoadingResult errorCode = image->Load(filePath);

    sprintf(image->Name, "Image Nr.%i", ++inmageID);

    if (errorCode == ResourceLoadingResult::Successful)
    {
        Add(*image);
    }
}

BF::ResourceLoadingResult BF::ResourceManager::Load(Model& model, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    strcpy(model.FilePath, filePath);

    std::thread* modelLoaderThread = new std::thread([](ResourceManager* resourceManager, Model* model, const char* filePath)
    {
        ResourceLoadingResult errorCode = model->Load();

        if (errorCode == ResourceLoadingResult::Successful)
        {
            for (unsigned int i = 0; i < model->MaterialList.Size(); i++)
            {
                Material& modelMaterial = model->MaterialList[i];

                std::thread* asy = new std::thread([](ResourceManager* resourceManager, Material* material)
                {
                    Image* image = new Image();
                    ResourceLoadingResult errorCode = image->Load(material->TextureFilePath);

                    sprintf(image->Name, "Image Nr.%i", ++inmageID);

                    if (errorCode == ResourceLoadingResult::Successful)
                    {
                        material->Texture = image;
                    }

                    resourceManager->Add(*image);

                }, resourceManager, &modelMaterial);
            }
        }

       resourceManager->Add(*model);

    }, this, &model, filePath);

    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::ResourceManager::Load(Image& image, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    ResourceLoadingResult errorCode = image.Load(filePath);
    
    if (errorCode == ResourceLoadingResult::Successful)
    {
        Add(image);
    }
  
    return errorCode;
}

BF::ResourceLoadingResult BF::ResourceManager::Load(Sound& resource, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::ResourceManager::Load(Font& font, const char* filePath, ResourceLoadMode resourceLoadMode)
{
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

            memcpy(textureFilePath, &filePath[0], startIndex);

            int length = strlen(textureFilePath);

            memcpy(&textureFilePath[length], &resourcePath[0], resourcePathSize);
            
            // Does file exist?

            font.Texture = new Image();

           // errorCode = ErrorCode::FileNotFound;
            errorCode = Load(*font.Texture, textureFilePath);

            if (errorCode != ResourceLoadingResult::Successful)
            {
                delete font.Texture;
                font.Texture = nullptr;
            }
        }

        font.ID = _fontList.Size();

        strcpy(font.FilePath, filePath);
    }

    return errorCode;
}

BF::ResourceLoadingResult BF::ResourceManager::Load(ShaderProgram& resource, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::ResourceManager::Load(Dialog& resource, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::ResourceManager::Load(Level& level, const char* filePath, ResourceLoadMode resourceLoadMode)
{
    File file(filePath);
    ResourceLoadingResult errorCode;

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
    unsigned int amountOfLines = 0;

    file.Read();

    char currentLineBuffer[200];

    amountOfLines = file.CountAmountOfLines();

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
                for (size_t i = 0; i < positionText[i] != '\0'; i++)
                {
                    if (positionText[i] == '|')
                    {
                        positionText[i] = ' ';
                    }
                }

                for (size_t i = 0; i < rotationText[i] != '\0'; i++)
                {
                    if (rotationText[i] == '|')
                    {
                        rotationText[i] = ' ';
                    }
                }

                for (size_t i = 0; i < scaleText[i] != '\0'; i++)
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

                errorCode = Load(*loadedModel, path);

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
                loadedModel->ModelMatrix.Scale(scale);
                //loadedModel->UpdateGlobalMesh();

                //Add(*loadedModel);
                //-----------------------
                break;
            }
            case _textureToken:
            {
                sscanf(currentLineBuffer, "%s %s", dummyBuffer, path);

                Image* image = new Image();

                errorCode = Load(*image, path);

                if (errorCode == ResourceLoadingResult::Successful)
                {
                    Add(*image);
                }
                else
                {
                    delete image;
                }         

                level.ImageList[imageCounter++] = image;
                break;
            }
            case _musicToken:
            {
                sscanf(currentLineBuffer, "%s %s", dummyBuffer, path);

                Sound* sound = new Sound();
                
                errorCode = Load(*sound, path);

                level.SoundList[soundCounter++] = sound;
                break;
            }
            case _fontToken:
            {
                sscanf(currentLineBuffer, "%s %s", dummyBuffer, path);

                Font* font = new Font();
                
                errorCode = Load(*font, path);          

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

    return errorCode;
}

BF::ResourceLoadingResult BF::ResourceManager::Load(ShaderProgram& shaderProgram, const char* vertexShader, const char* fragmentShader, ResourceLoadMode ResourceLoadMode)
{
    shaderProgram.AddShader(vertexShader, fragmentShader);
    shaderProgram.Load();

    bool validShader = OpenGLAPI::ShaderCompile(shaderProgram);

    if (validShader)
    {
        Add(shaderProgram);
    }

    return ResourceLoadingResult::Successful;
}

void BF::ResourceManager::Add(Model& model)
{
    bool readyToCache = model.ID == ResourceIDReadyToBeCached;

    if (readyToCache)
    {
        model.ID = ResourceIDReadyToUpload;
        _modelAdd.Lock();
        _modelList.Add(&model);
        _modelAdd.Release();
    }

   // PushToGPU(model);
}

void BF::ResourceManager::Add(Image& image)
{
  
    bool readyToCache = image.ID == ResourceIDReadyToBeCached;

    if (readyToCache)
    {
        image.ID = ResourceIDReadyToUpload;

        _imageAdd.Lock();
        _imageList.Add(&image);
        _imageAdd.Release();
    }
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

void BF::ResourceManager::ModelsPhysicsApply(float deltaTime)
{   
    for (LinkedListNode<Model*>* currentModel = _modelList.GetFirst() ; currentModel != nullptr ; currentModel = currentModel->Next)
    {
        Model* model = currentModel->Element;
        auto& force = model->Force;
        auto& velocity = model->Velocity;
        auto mass = model->Mass;
        Vector3<float> gravity(0.f, -0.981, 0.f);

        if (model->EnablePhysics)
        {
            model->ModelMatrix.Motion(force, velocity, mass, gravity, deltaTime);
        }
    }
}

void BF::ResourceManager::ModelsRender(float deltaTime)
{
    LinkedListNode<Model*>* currentModel = _modelList.GetFirst();

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

    while (currentModel != nullptr)
    {
        Model* model = currentModel->Element;
        ModelRenderInformation& renderInfo = model->RenderInformation;
        unsigned int shaderProgramID = renderInfo.ShaderProgramID;
        bool useDefaultShader = shaderProgramID == -1;
        bool changeShader = shaderProgramID != _lastUsedShaderProgram;

        currentModel = currentModel->Next;

        if (!renderInfo.ShouldItBeRendered && (int)model->ID < 0)
        {
            continue;
        }

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

            OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixModelID, model->ModelMatrix.Data);

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
            char buffer[30];

            if (image->ID == -1)
            {
              //  sprintf(buffer, "-");
            }
            else
            {
               // sprintf(buffer, "%u", image->ID);
            }       

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