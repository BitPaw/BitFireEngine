#include "ResouceManager.h"
#include "../../../SystemResource/Source/Font/FNT/FNTPage.h"
#include "../../../SystemResource/Source/File/FileStream.h"
#include "../../../SystemResource/Source/Time/StopWatch.h"
#include "../../../SystemResource/Source/Game/SkyBox.h"
#include "../../../SystemResource/Source/Math/Physic/GravityField.h"
#include "../../../SystemRender/Source/OpenGLAPI.h"
#include "../../../SystemResource/Source/Math/Geometry/Form/Cube.h"
#include "../../../SystemResource/Source/Math/Geometry/Shape/Rectangle.h"

#include "../../../SystemResource/Source/OSDefine.h"
#include "../../../SystemResource/Source/Math/Physic/GravityCube.h"
#include "../../../SystemResource/Source/File/File.h"
#include "../../../SystemResource/Source/File/Text.h"

#include <cassert>

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

BF::ResourceManager::ResourceManager()
{
    _lastUsedShaderProgram = -1;
    _defaultShaderID = -1;
    _defaultTextureID = -1;

    DefaultSkyBox = nullptr;
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
    size_t& modelID = model.ID;
    bool isAlreadyLinked = (int)modelID > 0;
    bool isUsable = modelID == ResourceIDLoaded || isAlreadyLinked;

    modelID = ResourceIDLoading;

    if (!isUsable)
    {
        return;
    }

    if (isAlreadyLinked)
    {
       // OpenGLAPI::VertexArrayUpdate(renderInfo.VertexBufferID, renderInfo.VertexDataSize * sizeof(float), renderInfo.VertexData);
    }
    else
    {   
        OpenGLAPI::RegisterModel(model);       
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

        if (model->ShallBeCached())
        {
            PushToGPU(*model);

            //model->PrintModelData();
        }    
    }

    for (LinkedListNode<Image*>* node = _imageList.GetFirst() ; node != nullptr ; node = node->Next)
    {
        Image* image = node->Element;

        if (image->ShallBeCached())
        {
            PushToGPU(*image);

            //image->PrintData();
        }
    }
}

BF::Resource* BF::ResourceManager::Load(const wchar_t* filePath)
{
    Resource* resource = nullptr;
    ResourceType resourceType = ResourceType::Unknown;
    bool loadAsync = true;

    {
        bool isModel = Model::FileFormatPeek(filePath) != ModelType::UnKown;
        bool isImage = Image::FileFormatPeek(filePath) != ImageFileFormat::Unkown;
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

            Add(*image, filePath, loadAsync);

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

            Add(*model, filePath, true);

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
        default:
        {
            printf("[!][Resource] Unkown file format detected! <%ls>\n", filePath);

            break;
        }
    }

    return resource;
}

void BF::ResourceManager::Load(Model& model)
{
    FileActionResult errorCode = model.Load();

    printf("[>][Model] Loading <%ls> ...\n", model.FilePath);

    if (errorCode == FileActionResult::Successful)
    {
        for (unsigned int i = 0; i < model.MaterialListSize; i++)
        {
            Material& modelMaterial = model.MaterialList[i];
            Image* newImage = new Image();

            if (newImage)
            {
                Image& image = *newImage;

                modelMaterial.Texture = newImage;

                image.ID = ResourceIDLoading;
                image.FilePathChange(modelMaterial.FilePath);

                Add(image, true);
            }
            else
            {
                printf("[!] Texture missing! <ls>\n");
            }           
        }

        model.ShouldItBeRendered = true;        
    }
    else
    {
        printf("[x][Model] Loading failed! <%i>\n", errorCode);
    }
}

void BF::ResourceManager::Load(Model& model, const wchar_t* filePath)
{
    model.FilePathChange(filePath);

    Load(model);   
}

void BF::ResourceManager::Load(Image& image)
{
    FileActionResult imageLoadingResult = image.Load();

    printf("[>][Model] Loading <%ls> ...\n", image.FilePath);

    if (imageLoadingResult != FileActionResult::Successful)
    {
        printf("[x][Model] Loading failed! <%i>\n", imageLoadingResult);
    }
}

void BF::ResourceManager::Load(Image& image, const wchar_t* filePath)
{
   image.FilePathChange(filePath);

    Load(image);
}

void BF::ResourceManager::Load(Sound& sound, const wchar_t* filePath)
{
    printf("[+][Resource] Font <%ls> loading...\n", filePath);

    //Add(sound);
}

void BF::ResourceManager::Load(Font& font, const wchar_t* filePath)
{
    printf("[+][Resource] Font <%ls> loading...\n", filePath);

    Text::Copy(font.FilePath, filePath, ResourceFilePathSize);

    Add(font);
   
    FileActionResult errorCode = font.Load(filePath);

    if (errorCode == FileActionResult::Successful)
    {
        font.ID = _fontList.Size();

        Text::Copy(font.FilePath, filePath, ResourceFilePathSize);

        for (unsigned int i = 0; i < font.AdditionalResourceListSize; i++)
        {   
            char* resourcePath = font.AdditionalResourceList[i];          
            wchar_t textureFilePath[PathMaxSize];   

            size_t pathIndex = Text::FindLast(filePath, PathMaxSize, '/');
            size_t copyedBytes = Text::Copy(textureFilePath, filePath, pathIndex+1);
            Text::Copy(textureFilePath + copyedBytes, resourcePath, PathMaxSize);
            
            
            // Does file exist?

            font.Texture = new Image();
            Load(*font.Texture, textureFilePath);

            if (errorCode == FileActionResult::Successful)
            {
                Add(*font.Texture, false);
            }
            else
            {
                delete font.Texture;
                font.Texture = nullptr;
            }     
        }          
    }
}

void BF::ResourceManager::Load(ShaderProgram& resource, const wchar_t* filePath)
{
    printf("[+][Resource] ShaderProgram <%ls> loading...\n", filePath);
}

void BF::ResourceManager::Load(Dialog& resource, const wchar_t* filePath)
{
    printf("[+][Resource] Dialog <%ls> loading...\n", filePath);
}

void BF::ResourceManager::Load(Level& level, const wchar_t* filePath)
{
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

    printf("[+][Resource] Level <%ls> loading...\n", filePath);

    FileStream file;
    FileActionResult FileActionResult = file.ReadFromDisk(filePath, true);
    char currentLineBuffer[256];

    if (FileActionResult != FileActionResult::Successful)
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
        char path[PathMaxSize];

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

                sscanf
                (
                    currentLineBuffer, 
                    "%s %s %s %s %s", 
                    dummyBuffer,
                    path, 
                    positionText,
                    rotationText, 
                    scaleText
                );                

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


                wchar_t pathW[PathMaxSize];
                Text::Copy(pathW, path, PathMaxSize);

                Add(*loadedModel, pathW, false);

                /*
                for (size_t i = 0; i < loadedModel->MeshListSize; i++)
                {
                    loadedModel->MeshList[i].Structure.RenderType = RenderMode::Point;
                }*/                

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
                Image* image = new Image();

                sscanf(currentLineBuffer, "%s %s", dummyBuffer, image->FilePath);

                Add(*image, true);

                level.ImageList[imageCounter++] = image;
                break;
            }
            case _musicToken:
            {
                sscanf(currentLineBuffer, "%s %s", dummyBuffer, path);

                wchar_t pathW[260];
                Text::Copy(pathW, path, 260);

                Sound* sound = new Sound();
                
                Load(*sound, pathW);

                level.SoundList[soundCounter++] = sound;
                break;
            }
            case _fontToken:
            {
                sscanf(currentLineBuffer, "%s %s", dummyBuffer, path);

                wchar_t pathW[260];
                Text::Copy(pathW, path, 260);

                Font* font = new Font();
                
                Load(*font, pathW);

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

void BF::ResourceManager::Load(ShaderProgram& shaderProgram, const wchar_t* vertexShader, const wchar_t* fragmentShader)
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
    const wchar_t* shaderVertex,
    const wchar_t* shaderFragment,
    const wchar_t* textureRight,
    const wchar_t* textureLeft,
    const wchar_t* textureTop,
    const wchar_t* textureBottom,
    const wchar_t* textureBack,
    const wchar_t* textureFront)
{
    skyBox.NameChange("SkyBox");
    
    Text::Copy(skyBox.MeshList[0].Name, "SkyBox", 50);
    
    Load(skyBox.Faces[0], textureRight);
    Load(skyBox.Faces[1], textureLeft);
    Load(skyBox.Faces[2], textureTop);
    Load(skyBox.Faces[3], textureBottom);
    Load(skyBox.Faces[4], textureBack);
    Load(skyBox.Faces[5], textureFront);

    skyBox.Faces[0].FlipHorizontal();
    skyBox.Faces[1].FlipHorizontal();
    //skyBox.Faces[2].FlipHorizontal();
    //skyBox.Faces[2].FlipVertical();
    skyBox.Faces[3].FlipHorizontal();
    skyBox.Faces[4].FlipHorizontal();
    skyBox.Faces[5].FlipHorizontal();

    Load(skyBox.Shader, shaderVertex, shaderFragment);

    Add(skyBox);
}

void BF::ResourceManager::Add(Sprite& sprite)
{
    Image* image = sprite.MaterialList[0].Texture;
    Model& model = (Model&)sprite; 
    Collider* collider = (Collider*)&sprite;

    Add(*image, false);



    float scaling = 0.01f;
    float scalingPos =  10;
    float xScaling = image->Width * scaling;
    float yScaling = image->Height * scaling;
    float xPos = model.MatrixModel.Data[TransformX] * scalingPos;
    float yPos = model.MatrixModel.Data[TransformY] * scalingPos * yScaling;
    float zPos = model.MatrixModel.Data[TransformZ];

    if (sprite.ID == ResourceIDShared)
    {
        model.MatrixModel.Scale(xScaling, yScaling, 1.0f);
    }
    else
    {
        BF::Rectangle rectangle(image->Width, image->Height);
        float vertexData[3*4];
        size_t vertexDataSize = 3 * 4;
        unsigned int indexData[4];
        size_t indexDataSize = 4;

        rectangle.GenerateVertexData(vertexData, vertexDataSize, indexData, indexDataSize);

        if (image->WrapWidth == ImageWrap::Repeat)
        {
            sprite.TextureScale[0] = model.MatrixModel.Data[ScaleX] / 10;
        }

        if (image->WrapHeight == ImageWrap::Repeat)
        {
            sprite.TextureScale[1] = model.MatrixModel.Data[ScaleY] / 10;
        }

        model.MatrixModel.Scale(scaling);

        sprite.ConvertFrom(vertexData, vertexDataSize, indexData, indexDataSize, RenderMode::Square, sprite.TextureScale[0], sprite.TextureScale[1]);
        
        sprite.MeshList[0].RenderInfo.MaterialID = 0;    
    }
   
    model.MatrixModel.MoveTo(xPos, yPos, zPos);

    Add(model);
    Add(collider);
}

void BF::ResourceManager::Add(Model& model, bool loadAsynchronously)
{
    bool isAlreadyLoaded = model.IsLoaded();

    _modelAdd.Lock();
    _modelList.Add(&model);
    _modelAdd.Release();

    if (isAlreadyLoaded)
    {
        model.ShouldItBeRendered = true;

        return; // No need to load if already loaded
    }

    if (loadAsynchronously)
    {
        std::thread* modelLoaderThread = new std::thread([](ResourceManager* resourceManager, Model* model)
        {
            resourceManager->Load(*model);
        }, this, &model);
    }
    else
    {
        Load(model);
    }
}

void BF::ResourceManager::Add(Model& model, const wchar_t* filePath, bool loadAsynchronously)
{
    model.FilePathChange(filePath);

    Add(model, loadAsynchronously);
}

void BF::ResourceManager::Add(Image& image, bool loadAsynchronously)
{  
    _imageAdd.Lock();
    _imageList.Add(&image);
    _imageAdd.Release();

    if (loadAsynchronously)
    {
        std::thread* imageLoaderThread = new std::thread([](ResourceManager* resourceManager, Image* image)
        {
            image->Load();
        }, this, &image);
    }
    else
    {
        image.Load();
        PushToGPU(image);
    }
}

void BF::ResourceManager::Add(Image& image, const wchar_t* filePath, bool loadAsynchronously)
{
    image.FilePathChange(filePath);

    Add(image, loadAsynchronously);
}

void BF::ResourceManager::Add(Font& font)
{
    bool firstImage = _fontList.Size() == 0;
    bool isRegistered = font.ID != -1;

    if (!isRegistered)
    {
        font.ID = _fontList.Size();
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
    OpenGLAPI::RegisterModel(skyBox);

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

        Vector2<float> position = collider->BoundingBox.Position;
        Vector2<float> size = collider->BoundingBox.Size;
        Vector3<float> boundingBox(size.X, size.Y, 0);
        Matrix4x4<float> boundingBoxModel;

        boundingBoxModel.Move(position.X, position.Y, 0);

        Matrix4x4<float> boundingBoxScaled = TransformBoundingBox(boundingBoxModel, boundingBox, false);
        Vector3<float> colliderPosition = boundingBoxScaled.PositionXYZ();
        Vector3<float> colliderScaling = boundingBoxScaled.ScaleXYZ();

        {
            // Color

            Matrix4x4<float>* bordermatrix = nullptr;
            Vector3<float>* borderSize = nullptr;
            Vector3<float> borderColor;


            switch (collider->Type)
            {
                case ColliderType::Gravity:
                {
                    bordermatrix = &boundingBoxModel;
                    borderSize = &boundingBox;
                    borderColor.Set(1, 0, 1);

                    BoundingBoxRender(*bordermatrix, *borderSize, borderColor);
                    break;
                }
                case ColliderType::HitBox:
                {
                    bordermatrix = &boundingBoxModel;
                    borderSize = &boundingBox;
                    borderColor.Set(0, 1, 0);
                    break;
                }
                case ColliderType::EffectBox:
                {
                    bordermatrix = &boundingBoxModel;
                    borderSize = &boundingBox;
                    borderColor.Set(0, 0, 1);
                    break;
                }
                default:
                {
                    bordermatrix = &boundingBoxModel;
                    borderSize = &boundingBox;
                    borderColor.Set(1, 1, 1);
                    break;
                }
            }

        }
    

        for (LinkedListNode<Model*>* modelNode = _modelList.GetFirst(); modelNode ; modelNode = modelNode->Next)
        {
            Model* model = modelNode->Element;
            Matrix4x4<float> modelMatrix = model->MatrixModel;
            Vector3<float> modelBoundingBox(model->MeshList[0].Structure.Width, model->MeshList[0].Structure.Height, model->MeshList[0].Structure.Depth);
            Matrix4x4<float> boundingBoxModelScaled = TransformBoundingBox(modelMatrix, modelBoundingBox, false);
            Vector3<float> modelPosition = boundingBoxModelScaled.PositionXYZ();
            Vector3<float> modelScaling = boundingBoxModelScaled.ScaleXYZ();

           // modelScaling.Z = INFINITY;       

            bool isColliding = collider->IsInBoundingBox(colliderPosition, colliderScaling, modelPosition, modelScaling);


            {
                // Color

                Matrix4x4<float>* bordermatrix = bordermatrix = &modelMatrix;
                Vector3<float>* borderSize = borderSize = &modelBoundingBox;
                Vector3<float> borderColor;

                switch (model->Type)
                {
                    case ColliderType::Gravity:
                    {
                        borderColor.Set(1, 0, 1);
                        break;
                    }
                    case ColliderType::HitBox:
                    {
                        borderColor.Set(0, 1, 0);
                        break;
                    }
                    case ColliderType::EffectBox:
                    {
                        borderColor.Set(0, 0, 1);
                        break;
                    }
                    default:
                    {
                        borderColor.Set(1, 1, 1);
                        break;
                    }
                }

                BoundingBoxRender(*bordermatrix, *borderSize, borderColor);
            }


            if (isColliding && model->EnablePhysics)
            {
                switch (collider->Type)
                {
                    case ColliderType::Gravity:
                    {
                        GravityField* gravityField = (GravityField*)collider;
                       
                        model->ApplyGravity(gravityField->PullDirection, gravityField->PullForce, deltaTime);
                        break;
                    }
                    case ColliderType::HitBox:
                    {
                        // Avoid Collsion / Bounce?   
                        break;
                    }
                    case ColliderType::EffectBox:
                    {
                        if (collider->OnCollisionCallBack)
                        {
                            collider->OnCollisionCallBack->OnCollisionDetected(collider, model);
                        }

                        break;
                    }
                }           
            }
        }
    }  
}

void BF::ResourceManager::ModelsRender(float deltaTime)
{
    MainCamera.Update(deltaTime);

    // Render Skybox first, if it is used
    {
        bool hasSkyBox = DefaultSkyBox != nullptr;

        if (hasSkyBox)
        {
            unsigned int shaderID = DefaultSkyBox->Shader.ID;
            Matrix4x4<float> viewTri(MainCamera.MatrixView);
            Mesh& skyMesh = DefaultSkyBox->MeshList[0];

            viewTri.ResetForthAxis();

            OpenGLAPI::RenderBothSides(true);
            OpenGLAPI::DepthMaskEnable(false);
            //OpenGLAPI::DrawOrder(true);

            OpenGLAPI::UseShaderProgram(shaderID);
            _lastUsedShaderProgram = shaderID;

            CameraDataGet(shaderID);
            CameraDataUpdate(MainCamera);

            OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixViewID, viewTri.Data);

            OpenGLAPI::SkyBoxUse(*DefaultSkyBox);          

            OpenGLAPI::Render(skyMesh.Structure.RenderType, 0, skyMesh.Structure.IndexDataSize);

            OpenGLAPI::DepthMaskEnable(true);
            //OpenGLAPI::DrawOrder(false);
        }
    }

    for (LinkedListNode<Model*>* currentModel = _modelList.GetFirst() ; currentModel ; currentModel = currentModel->Next)
    {
        Model* model = currentModel->Element;
        Model* parentModel = nullptr;
        bool isSharedModel = model->SharedModel != nullptr;
        bool skipRendering = !model->ShouldItBeRendered;       

        if (skipRendering)
        {
            continue; // Skip to next model.
        }

        if (isSharedModel)
        {
            parentModel = model;
            model = model->SharedModel;
        }               

        for (size_t meshIndex = 0; meshIndex < model->MeshListSize; meshIndex++)
        {
            Mesh& mesh = model->MeshList[meshIndex];
            unsigned int shaderProgramID = parentModel ? parentModel->SharedRenderInfoOverride.ShaderProgramID : mesh.RenderInfo.ShaderProgramID ;
            bool useDefaultShader = shaderProgramID == -1;
            bool changeShader = shaderProgramID != _lastUsedShaderProgram;
            bool isRegistered = ((int)1) >= 0;
            bool skipRendering = !(mesh.RenderInfo.ShouldBeRendered && isRegistered) || mesh.Structure.RenderType == RenderMode::Invalid;
            unsigned int vaoID = isSharedModel ? model->SharedModel->ID : mesh.Structure.VertexArrayID;
            Matrix4x4<float>& modelMatrix = isSharedModel ? parentModel->MatrixModel : model->MatrixModel;

            if (skipRendering) // Skip to next mesh.
            {
                continue;
            }

            assert(isRegistered);    

            //-----[Shader Lookup]---------------------------------------------
            {
                if (useDefaultShader)
                {
                    shaderProgramID = _defaultShaderID;
                    changeShader = shaderProgramID != _lastUsedShaderProgram;
                }

                if (changeShader)
                {
                    OpenGLAPI::UseShaderProgram(shaderProgramID);

                    _lastUsedShaderProgram = shaderProgramID;

                    CameraDataGet(shaderProgramID);
                }

                CameraDataUpdate(MainCamera);
            }           
            //-----------------------------------------------------------------

            OpenGLAPI::VertexArrayBind(vaoID);

            //-----[Position]--------------------------------------------------
            OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixModelID, modelMatrix.Data);
            //-----------------------------------------------------------------  

            //-----[Texture Lookup]--------------------------------------------
            unsigned int materialIndex = parentModel ? parentModel->SharedRenderInfoOverride.MaterialID : mesh.RenderInfo.MaterialID;
            unsigned int textureID = materialIndex != -1 ? model->MaterialList[materialIndex].Texture->ID : _defaultTextureID;

            OpenGLAPI::TextureUse(ImageType::Texture2D, textureID);
            //-----------------------------------------------------------------           

            //-----[RenderStyle]-----------------------------------------------                      
            OpenGLAPI::Render(mesh.Structure.RenderType, 0, mesh.Structure.IndexDataSize);
            //-----------------------------------------------------------------

#if 1// Show HitBoxes
            Vector3<float> boundingBox(mesh.Structure.Width, mesh.Structure.Height, mesh.Structure.Depth);

            //BoundingBoxRender(model->MatrixModel, boundingBox, Vector3<float>(0, 1, 1));
#endif
       
        }       
    }

    for (LinkedListNode<Collider*>* colliderCurrent = _physicList.GetFirst(); colliderCurrent ; colliderCurrent = colliderCurrent->Next)
    {
        Collider* collider = colliderCurrent->Element;
        Vector3<float> color(1.0f,1.0f,1.0f);
        Vector2<float> position = collider->BoundingBox.Position;
        Vector2<float> size = collider->BoundingBox.Size;
        Vector3<float> boundingBox(size.X, size.Y, 0);
        Matrix4x4<float> model;

        model.Move(position.X, position.Y, 0);

        switch (collider->Type)
        {
            case ColliderType::Gravity:
            {
                color.Set(0.69f, 0.0f, 1.0f);
                break;
            }
            case ColliderType::HitBox:
            {
                color.Set(0.69f, 1.0f, 0.0f);
                break;
            }
            case ColliderType::EffectBox:
            {
                color.Set(1.0f, 1.0f, 0.0f);
                break;
            }
        }

        //BoundingBoxRender(model, boundingBox, color);
    }
}

BF::Matrix4x4<float> BF::ResourceManager::TransformBoundingBox(Matrix4x4<float> modelMatrix, Vector3<float> boundingBox, bool half)
{
    Matrix4x4<float> matrixResult;
    Vector3<float> position = modelMatrix.PositionXYZ();
    Vector3<float> scalingModf = modelMatrix.ScaleXYZ();

    if (half)
    {
        scalingModf = scalingModf / 2.0f;
    }

    boundingBox *= scalingModf;

    if (half)
    {
        position.X += (boundingBox.X);
        position.Y += (boundingBox.Y);
    }
    else
    {
        //position.X -= (boundingBox.X);
        //position.Y -= (boundingBox.Y);
    }

    matrixResult.MoveTo(position);
    matrixResult.ScaleSet(boundingBox.X, boundingBox.Y, 1);

    return matrixResult;
}

void BF::ResourceManager::BoundingBoxRender(Matrix4x4<float> modelMatrix, Vector3<float> boundingBox, Vector3<float> color)
{
    Matrix4x4<float> boundingBoxScaled = TransformBoundingBox(modelMatrix, boundingBox, true);
    unsigned int shaderID = ShaderHitBox.ID;

    OpenGLAPI::UseShaderProgram(shaderID);
    _lastUsedShaderProgram = shaderID;
    CameraDataGet(shaderID);
    //OpenGLAPI::TextureUse(ImageType::Texture2D, 0);
    CameraDataUpdate(MainCamera);
    int shaderColorID = OpenGLAPI::ShaderGetUniformLocationID(shaderID, "HitBoxColor");

    boundingBoxScaled.Move(0, 0, -2);

    OpenGLAPI::VertexArrayBind(CubeHitBoxViewModel.MeshList[0].Structure.VertexArrayID);
    OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixModelID, boundingBoxScaled.Data);
    // Render middle
    OpenGLAPI::ShaderSetUniformVector4(shaderColorID , color.X, color.Y, color.Z, 0.05f);
    OpenGLAPI::Render(RenderMode::Square, 0, 4);
    // Render outLine
    OpenGLAPI::ShaderSetUniformVector4(shaderColorID, color.X, color.Y, color.Z, 1);
    OpenGLAPI::Render(RenderMode::LineLoop, 0, 4);
}

void ByteToString(char* string, size_t value)
{
    if (value > 1000)
    {
        value /= 1000;

        if (value > 1000)
        {
            value /= 1000;

            if (value > 1000)
            {
                value /= 1000;

                sprintf(string, "%i GB", value);
            }
            else
            {
                sprintf(string, "%i MB", value);
            }
        }
        else
        {
            sprintf(string, "%i KB", value);
        }
    }
    else
    {
        sprintf(string, "%i B", value);
    } 
}

void BF::ResourceManager::PrintContent(bool detailed)
{
    if (detailed)
    {
        const char* noValue = "| %-73s |\n";
        const char* message =
            "+-----------------------------------------------------------------------------+\r\n"
            "|  %-74s |\n"
            "+-----+-----------------------+--------------------------------------+--------+\n"
            "|  ID | Name                  | Source - FilePath                    | Size   |\n"
            "+-----+-----------------------+--------------------------------------+--------+\n";

        const char* endLine = "+-----+-----------------------+--------------------------------------+--------+\n\n";

        const char* line = "| %3i | %-21ls | %-36ls | %4i B |\n";

    
        printf(message, "Models");

        for (LinkedListNode<Model*>* currentModel = _modelList.GetFirst(); currentModel ; currentModel = currentModel->Next)
        {
            Model* model = currentModel->Element;
            unsigned int meshListSize = model->MeshListSize;

            printf(line, model->ID, model->Name, model->FilePath, sizeof(*model));

            for (size_t i = 0; i < meshListSize; i++)
            {           
                Mesh& mesh = model->MeshList[i];
                unsigned int vaoID = mesh.Structure.VertexArrayID;
                char subMeshTagBuffer[60];

                sprintf(subMeshTagBuffer, "(Sub-Mesh) [%2zu/%2zu]", i + 1, meshListSize);

                if ((int)mesh.Structure.VertexArrayID > 0)
                {   
                    printf(line, vaoID, mesh.Name, subMeshTagBuffer, sizeof(mesh));
                }
                else
                {
                    const char* idTag = nullptr;

                    switch (vaoID)
                    {
                        case ResourceIDUndefined:
                            idTag = "UDF";
                            break;

                        case ResourceIDLoading:
                            idTag = "LOA";
                            break;

                        case ResourceIDLoaded:
                            idTag = "O K";
                            break;

                        case ResourceIDShared:
                            idTag = "SHA";
                            break;

                        case ResourceIDFileNotFound:
                            idTag = "MIS";
                            break;

                        case ResourceIDOutOfMemory:
                            idTag = "ErM";
                            break;

                        case ResourceIDUnsuportedFormat:
                            idTag = "ErF";
                            break;
                    }

                    printf("| %3s | %-21s | %-36s | %4i B |\n", idTag, mesh.Name, subMeshTagBuffer, sizeof(mesh));
                }     
               
            }
        }

        printf(endLine);
        printf(message, "Images");

        for (LinkedListNode<Image*>* currentImage = _imageList.GetFirst() ;  currentImage ; currentImage = currentImage->Next)
        {
            Image* image = currentImage->Element;
            char byteStringBuffer[40];

            ByteToString(byteStringBuffer, image->FullSizeInMemory());

            printf("| %3i | %-21ls | %-36.36ls | %6s |\n", image->ID, image->Name, image->FilePath, byteStringBuffer);
        }

        printf(endLine);
        printf(message, "Sounds");

        for (LinkedListNode<Sound*>* currentSound = _soundList.GetFirst();  currentSound ; currentSound = currentSound->Next)
        {
            Sound* sound = currentSound->Element;

            printf(line, sound->ID, sound->Name, sound->FilePath, sizeof(*sound));
        }

        printf(endLine);
        printf(message, "Font");

        for (LinkedListNode<Font*>* currentFont = _fontList.GetFirst(); currentFont; currentFont = currentFont->Next)
        {
            Font* font = currentFont->Element;

            printf("| ID:%u Font Source: %ls\n", font->ID, font->FilePath);
        }

        printf(endLine);
        printf(message, "Shader");

        for (LinkedListNode<ShaderProgram*>* currentChaderProgram = _shaderProgramList.GetFirst(); currentChaderProgram ; currentChaderProgram = currentChaderProgram->Next)
        {
            ShaderProgram* shaderProgram = currentChaderProgram->Element;
            unsigned int shaderListSize = ShaderListSize;
            char buffer[50];

            sprintf(buffer, "(ShaderContainer) [%i]", shaderListSize);    
            wchar_t bufferW[260];

            Text::Copy(bufferW, buffer, 260);

            printf(line, shaderProgram->ID, bufferW, L"<Internal>", sizeof(ShaderProgram));

            for (size_t i = 0; i < shaderListSize; i++)
            {
                Shader& shader = shaderProgram->ShaderList[i];
                const char* shaderTypeString = ShaderTypeToString(shader.Type);
                wchar_t shaderTypeStringW[260];

                Text::Copy(shaderTypeStringW, shaderTypeString, 260);

                printf(line, shader.ID, shaderTypeStringW, shader.FilePath, sizeof(shader));
            }
        }

        printf(endLine);
        printf(message, "Dialog");

        for (LinkedListNode<Dialog*>* dialogList = _dialogList.GetFirst(); dialogList; dialogList = dialogList->Next)
        {
            Dialog* dialog = dialogList->Element;

            printf(line, dialog->ID, dialog->Name, dialog->FilePath, sizeof(*dialog));
        }
   
        printf(endLine);
    }
    else
    {
        unsigned int modelListSize = _modelList.Size();
        unsigned int imageListSize = _imageList.Size();
        unsigned int soundListSize = _soundList.Size();
        unsigned int shaderListSize = _shaderProgramList.Size();
        unsigned int fontListSize = _fontList.Size();
        unsigned int dialogListSize = _dialogList.Size();

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