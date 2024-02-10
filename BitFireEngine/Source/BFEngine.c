#include "BFEngine.h"

#include <Media/PXText.h>
#include <Math/PXMatrix.h>

#include <OS/File/PXFile.h>
#include <OS/Async/PXAwait.h>
#include <OS/Time/PXStopWatch.h>
#include <OS/Hardware/PXProcessor.h>
#include <OS/Console/PXConsole.h>
#include <Math/PXCollision.h>
#include <OS/Time/PXTime.h>
#include <Math/PXMath.h>

#include <stdlib.h>
#include <signal.h>





PXInt32U _matrixModelID;
PXInt32U _matrixViewID;
PXInt32U _matrixProjectionID;
PXInt32U _materialTextureID;
PXRefreshRateMode RefreshRate;


float _lastUIUpdate = 0;

/*


void BF::BitFireEngine::UpdateInput(InputContainer& input)
{    
    KeyBoardCache& keyboard = input.KeyBoardInput;
    MouseCache& mouse = input.MouseInput;
    PXCamera& camera = MainCamera;

    if(InputButtonIsShortPressed(keyboard.J))
    {
        PrintContent(true);
    }   

    if(InputButtonIsShortPressed(keyboard.R))
    {
        switch(_mainWindow.CursorModeCurrent)
        {
            case PXWindowCursorShow:
            {
                PXWindowCursorCaptureMode(&_mainWindow, PXWindowCursorLockAndHide);
                break;
            }
            case PXWindowCursorLockAndHide:
            {
                PXWindowCursorCaptureMode(&_mainWindow, PXWindowCursorShow);
                break;
            }
        }

        keyboard.R = 0xFF;
    }

    if(InputButtonIsShortPressed(keyboard.K))
    {
        Image image;

        //_mainWindow.TakeScreenShot(image);

      //  ImageSave(L"ScreenShot.bmp", ImageFileFormatBitMap);
    }

    if(InputButtonIsShortPressed(keyboard.E))
    {
        keyboard.E = 0xFF;

        switch(camera.Perspective)
        {
            case PXCameraPerspective2D:
                PXCameraViewChange(&MainCamera, PXCameraPerspective3D);
                break;

            case PXCameraPerspective3D:
                PXCameraViewChange(&MainCamera, PXCameraPerspective2D);
                break;
        }
    }

#if 0 // DEBUG
    if(keyboard.ShitftLeft.IsPressed()) { movement.Add(0, -1, 0); }
    if(keyboard.W.IsPressed()) { movement.Add(0, 0, 1); }
    if(keyboard.A.IsPressed()) { movement.Add(-1, 0, 0); }
    if(keyboard.S.IsPressed()) { movement.Add(0, 0, -1); }
    if(keyboard.D.IsPressed()) { movement.Add(1, 0, 0); }
    if(keyboard.SpaceBar.IsPressed())
    {
        camera.Velocity.Set(0.0f, 6.0f, .0f);

        movement.Add(0, 1, 0);
    }



    if(_mainWindow.Interactable())
    {
        // Add joystik
        {
            Controller controllerData;
            controllerData.ID = 0;
            bool successful = ControllerDataGet(&controllerData);

            double mouseX = 0;
            double mouseY = 0;

            if(successful)
            {
                const int max = 32767;
                int viewXi = (int)controllerData.Axis[0] - max;
                int viewYi = (int)controllerData.Axis[1] - max;
                int posXi = (int)controllerData.Axis[2] - max;
                int posYi = (int)controllerData.Axis[3] - max;

                if(posXi != 0 || posYi != 0)
                {
                    double xf = -posXi / 32768.0;
                    double yf = -posYi / 32768.0;

                    mouseX += xf;
                    mouseY += yf;
                }

                if(viewXi != 0 || viewYi != 0)
                {
                    double xf = viewXi / 32768.0;
                    double yf = -viewYi / 32768.0;

                    movement.Add(xf, 0, yf);
                }
            }

            mouseX += mouse.InputAxis[0];
            mouseY += mouse.InputAxis[1];

            camera.Rotate(mouseX, mouseY);
        }

        camera.Move(movement);
    }

    camera.Update(_deltaTime);
#endif

    InvokeEvent(this->UpdateInputCallBack, this, _inputContainer);


 

    PXCameraUpdate(&camera, _deltaTime);

    keyboard.IncrementButtonTick();
    mouse.ResetAxis();

#if 0
    char buffer[256];

    PXMatrix4x4FPrint(&MainCamera.MatrixModel, buffer);

    printf("%s", buffer);
#endif
}

void BF::BitFireEngine::MakeRectangle(PXRenderable& renderable)
{
    const float vtx[12] =
    {
        0,0,0,
        0,1,0,
        1,1,0,
        1,0,0
    };

    const unsigned int itx[4] =
    {
        0,1,2,3
    };

    Load(renderable, vtx, 12, itx, 4);

    //renderable.Mode = GraphicRenderModeSquare;
}

PXThreadResult BF::BitFireEngine::LoadResourceAsync(void* resourceAdress)
{
    /*
    ResourceAsyncLoadInfo* resourceAsyncLoadInfo = (ResourceAsyncLoadInfo*)resourceAdress;
    Resource* resource = resourceAsyncLoadInfo->ResourceAdress;
    const wchar_t* filePath = resourceAsyncLoadInfo->FilePath;
    const PXActionResult loadResult = resource->Load(filePath);

    printf("[#][Resource][ASYNC] Loaded <%ls> ... [%i]\n", filePath, loadResult);
    * /
    return 0;
}

PXActionResult BF::BitFireEngine::Load(PXRenderable& renderable, const char* filePath, bool loadAsynchronously)
{
    return PXGraphicModelLoadA(&this->_mainWindow.GraphicInstance, &renderable, (char*)filePath);
}

PXActionResult BF::BitFireEngine::Load(PXModel& model, const wchar_t* filePath, const bool loadAsynchronously)
{
    const PXActionResult result = PXActionInvalid;// model.Load(filePath);

    return result;
}

PXActionResult BF::BitFireEngine::Load(PXRenderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize)
{
    /*
    Register(renderable, vertexData, vertexDataSize, indexList, indexListSize);

    _modelAdd.Lock();
    _renderList.Add(&renderable);
    _modelAdd.Release();* /

    return PXActionSuccessful;
}

PXActionResult BF::BitFireEngine::Load(Image& image, const wchar_t* filePath, const bool loadAsynchronously)
{
    return PXActionSuccessful;
}

PXActionResult BF::BitFireEngine::Load(PXTexture& texture, const wchar_t* filePath, bool loadAsynchronously)
{
    texture.Type = PXGraphicImageTypeTexture2D;
    texture.Filter = PXGraphicRenderFilterTrilinear;
    texture.LayoutNear = PXGraphicImageLayoutLinear;
    texture.LayoutFar = PXGraphicImageLayoutLinear;
    texture.WrapHeight = PXGraphicImageWrapRepeat;
    texture.WrapWidth = PXGraphicImageWrapRepeat;

    return PXGraphicTextureLoadW(&this->_mainWindow.GraphicInstance, &texture, (wchar_t*)filePath);
}

PXActionResult BF::BitFireEngine::Load(PXFont& font, const wchar_t* filePath, bool loadAsynchronously)
{
    /*
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
    }* /

    return PXActionSuccessful;
}
/*
PXActionResult BF::BitFireEngine::Load(AudioClip& audioClip, const wchar_t* filePath, bool loadAsynchronously)
{
    printf("[+][Resource] AudioClip <%ls> loading...\n", filePath);

    Sound* soundAdress = new Sound();

    if(!soundAdress)
    {
        return ResultOutOfMemory;
    }

    Sound& sound = *soundAdress;

    if(loadAsynchronously)
    {

    }
    else
    {
        const PXActionResult soundLoadResult = sound.Load(filePath);

        if(soundLoadResult != ActionSuccessful)
        {
            delete soundAdress;

            return soundLoadResult;
        }

        Register(audioClip, sound);
    }

    return ActionSuccessful;
}* /

PXActionResult BF::BitFireEngine::Load(ShaderProgram& shaderProgram, const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
{
    printf("[+][Resource] ShaderProgram V:<%ls> F:<%ls> loading...\n", vertexShaderFilePath, fragmentShaderFilePath);
   
    const PXActionResult successful = PXGraphicShaderProgramLoadGLSLA(&_mainWindow.GraphicInstance, &shaderProgram, (char*)vertexShaderFilePath, (char*)fragmentShaderFilePath);

    if (successful)
    {
        _defaultShaderID = shaderProgram.ID;

        CameraDataGet(&_mainWindow, _defaultShaderID);
    }

    return successful;
}

/*
PXActionResult BF::BitFireEngine::Load(Resource* resource, const wchar_t* filePath, const bool loadAsynchronously)
{
    ResourceType resourceType = ResourceType::Unknown;

    {
        bool isModel = Model::FileFormatPeek(filePath) != ModelType::UnKown;
        bool isImage = ImageGuessFormat(filePath) != ImageFileFormatUnkown;
        bool isSound = Sound::FileFormatPeek(filePath) != SoundFormat::Unkown;
        bool isFont = FontGuessFormat(filePath) != FontFileFormatUnkown;
        bool isShader = false;
        bool isDialog = false;
        bool isLevel = Level::IsLevelFile(filePath);

        if(isModel) resourceType = ResourceType::Model;
        if(isImage) resourceType = ResourceType::Image;
        if(isSound) resourceType = ResourceType::Sound;
        if(isFont) resourceType = ResourceType::Font;
        if(isShader) resourceType = ResourceType::Shader;
        if(isDialog) resourceType = ResourceType::Dialog;
        if(isLevel) resourceType = ResourceType::Level;
    }

    switch(resourceType)
    {
        case ResourceType::Dialog:
        {
            //Dialog* dialog = new Dialog();

            //Load(*dialog, filePath, loadAsynchronously);

            //resource = dialog;

            break;
        }

        case ResourceType::Font:
        {
            PXFont* font = new PXFont();

            Load(*font, filePath, loadAsynchronously);

            resource = (Resource*)font;

            break;
        }

        case ResourceType::Image:
        {
            Image* image = new Image();

            Load(*image, filePath, loadAsynchronously);

            resource = (Resource*)image;

            break;
        }

        case ResourceType::Level:
        {
            Level* level = new Level();

            Load(*level, filePath, loadAsynchronously);

            resource = level;

            break;
        }

        case ResourceType::Model:
        {
            Model* model = new Model();

            Load(*model, filePath, loadAsynchronously);

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

            Load(*sound, filePath, loadAsynchronously);

            resource = sound;

            break;
        }
        default:
        {
            printf("[!][Resource] Unkown file format detected! <%ls>\n", filePath);

            break;
        }
    }

    return ResultSuccessful;
}* /

PXActionResult BF::BitFireEngine::Load(Level& level, const wchar_t* filePath, const bool loadAsynchronously)
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
    /*
    DataStream dataStream;

    {
        const PXActionResult mappingResult = FileMapToVirtualMemoryW(&file, filePath, 0, MemoryReadOnly);
        const unsigned char sucessful = mappingResult == ResultSuccessful;

        if(!sucessful)
        {
            return ResultInvalid;
        }
    }

    ParsingStreamConstruct(&parsingStream, file.Data, file.DataSize);

    // Step I - Count objects
    do
    {
        unsigned char* character = ParsingStreamCursorPosition(&parsingStream);

        switch(character[0])
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
    while(ParsingStreamSkipLine(&parsingStream));

    // Step II - Reserve space
    level.ModelList.ReSize(modelCounter);
    level.TextureList.ReSize(imageCounter);
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

    ParsingStreamCursorToBeginning(&parsingStream);

    // Step II - Parse and Load
    do
    {
        const char* currentLineTypeData = (char*)ParsingStreamCursorPosition(&parsingStream);
        char character = currentLineTypeData[0];
        char filePathA[PathMaxSize]{ 0 };

        ParsingStreamSkipBlock(&parsingStream);

        const char* currentLine = (char*)ParsingStreamCursorPosition(&parsingStream);
        const size_t currentLineSize = ParsingStreamRemainingSize(&parsingStream);

        switch(character)
        {
            case _modelToken:
            {
                Vector3<float> position;
                Vector3<float> rotation;
                Vector3<float> scale;

                TextParseA
                (
                    currentLine,
                    currentLineSize,
                    "sf§f§ff§f§ff§f§f",
                    filePathA,
                    &position.X,
                    &position.Y,
                    &position.Z,
                    &rotation.X,
                    &rotation.Y,
                    &rotation.Z,
                    &scale.X,
                    &scale.Y,
                    &scale.Z
                );

                // Load Model----------------
                Model* loadedModel = new Model();

                wchar_t filePathW[PathMaxSize];
                TextCopyAW(filePathA, PathMaxSize, filePathW, PathMaxSize);

                const PXActionResult result = Load(*loadedModel, filePathW, false);
                const bool successful = result == ResultSuccessful;

                if(successful)
                {
                    /*
              for (size_t i = 0; i < loadedModel->MeshListSize; i++)
              {
                  loadedModel->MeshList[i].Structure.RenderType = RenderMode::Point;
              }* /

                    level.ModelList[modelCounter++] = loadedModel;
                    //-------------------

                    rotation.X = MathDegreeToRadians(rotation.X);
                    rotation.Y = MathDegreeToRadians(rotation.Y);
                    rotation.Z = MathDegreeToRadians(rotation.Z);

                    Renderable* renderable = new Renderable();

                    Register(*renderable, *loadedModel);

                    renderable->ShaderUse(_defaultShaderID);
                    renderable->TextureUse(_defaultTextureID);

                    //--[Apply Data]-------------
              //loadedModel->DirectMorth = false;
                    renderable->MoveTo(position);
                    renderable->Rotate(rotation);
                    renderable->Scale(scale);


                    for(size_t m = 0; m < loadedModel->MeshListSize; m++)
                    {
                        Mesh& mesh = loadedModel->MeshList[m];
                        RenderableChunk& renderChnunk = renderable->ChunkList[m];

                        for(size_t s = 0; s < mesh.SegmentListSize; s++)
                        {
                            MeshSegment& segment = mesh.SegmentList[s];
                            RenderableSegment& renderSegment = renderChnunk.SegmentList[s];

                            for(size_t i = 0; i < segment.MaterialInfoSize; i++)
                            {
                                OBJElementMaterialInfo& info = segment.MaterialInfo[i];
                                SegmentMaterialRange& materialRange = renderSegment.MaterialRange[i];

                                const size_t materialID = info.MaterialIndex;
                                const bool hasMaterial = (int)info.MaterialIndex != -1;

                                if(hasMaterial)
                                {
                                    const Material& material = loadedModel->MaterialList[materialID];

                                    Texture* texture = new Texture();

                                    const PXActionResult loadResult = Load(*texture, material.TextureFilePath, false);
                                    const bool sucessful = loadResult == ResultSuccessful;

                                    if(sucessful)
                                    {
                                        materialRange.TextureID = texture->ID;
                                    }
                                }
                            }
                        }
                    }

                    _renderList.Add(renderable);
                }

                //-----------------------
                break;
            }
            case _textureToken:
            {
                Texture* texture = new Texture();

                char filePathA[PathMaxSize];
                wchar_t filePathW[PathMaxSize];

                TextParseA
                (
                    currentLine,
                    currentLineSize,
                    "s",
                    filePathA
                );

                TextCopyAW(filePathA, PathMaxSize, filePathW, PathMaxSize);

                const PXActionResult filePXActionResult = Load(*texture, filePathW, false);
                const bool sucessful = filePXActionResult == ResultSuccessful;

                if(sucessful)
                {
                    level.TextureList[imageCounter++] = texture;
                }

                break;
            }
            case _musicToken:
            {
                TextParseA
                (
                    currentLine,
                    currentLineSize,
                    "s",
                    filePathA
                );

                wchar_t filePathW[PathMaxSize];
                TextCopyAW(filePathA, PathMaxSize, filePathW, PathMaxSize);

                Sound* sound = new Sound();

                Load(*sound, filePathW);

                level.SoundList[soundCounter++] = sound;
                break;
            }
            case _fontToken:
            {
                TextParseA
                (
                    currentLine,
                    currentLineSize,
                    "s",
                    filePathA
                );

                wchar_t filePathW[PathMaxSize];
                TextCopyAW(filePathA, PathMaxSize, filePathW, PathMaxSize);

                PXFont* font = new PXFont();

                Load(*font, filePathW);

                level.FontList[fontCounter++] = font;

                Register(*font);

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
    while(ParsingStreamSkipLine(&parsingStream));

     * /

return PXActionSuccessful;
}
/*
PXActionResult BF::BitFireEngine::Load(Sprite& sprite, const wchar_t* filePath)
{
    printf("[+][Resource] Sprite <%ls> loading...\n", filePath);

    Renderable& renderable = sprite;
    Texture* texture = sprite.UsedTexture = new Texture;

    const PXActionResult textureLoadResult = Load(*texture, filePath, false);
    const bool sucessful = textureLoadResult == ResultSuccessful;

    if(sucessful)
    {
        const Texture& loadedTexture = *texture;
        const float scaling = 0.01;
        const size_t width = loadedTexture.DataImage.Width * scaling;
        const size_t height = loadedTexture.DataImage.Height * scaling;

        // TODO:TEST REMOVAL !!!    renderable.TextureID = loadedTexture.ID;

        renderable.TextureUse(loadedTexture.ID);
        renderable.Scale(width, height, 1.0f);
    }

    _modelAdd.Lock();
    _renderList.Add(&renderable);
    _modelAdd.Release();

    // Add(collider);
    // model.BoundingBoxUpdate();

    return ActionSuccessful;
}
PXActionResult BF::BitFireEngine::Load(Sound& sound, const wchar_t* filePath, const bool loadAsynchronously)
{
    return ActionSuccessful;
}

* /

PXActionResult BF::BitFireEngine::Load(Collider* collider)
{
   // _physicList.Add(collider);

    return PXActionSuccessful;
}



PXActionResult BF::BitFireEngine::Load
(
    PXSkyBox* skyBox,
    const char* shaderVertex,
    const char* shaderFragment,
    const char* textureRight,
    const char* textureLeft,
    const char* textureTop,
    const char* textureBottom,
    const char* textureBack,
    const char* textureFront
)
{
    printf("[+][Resource] SkyBox loading...\n");

    const PXActionResult actionResult = PXGraphicSkyboxRegisterA
    (
        &this->_mainWindow.GraphicInstance,
        &skyBox,
        shaderVertex,
        shaderFragment,
        textureRight,
        textureLeft,
        textureTop,
        textureBottom,
        textureBack,
        textureFront
    );

    return actionResult;
}

void BF::BitFireEngine::UnloadAll()
{
}

void BF::BitFireEngine::ModelsPhysicsApply(float deltaTime)
{
    /*
    for (LinkedListNode<Collider*>* colliderNode = _physicList.GetFirst(); colliderNode ; colliderNode = colliderNode->Next)
    {
        Collider* collider = colliderNode->Element;

        const Vector2<float> position = collider->BoundingBox.Position;
        const Vector2<float> size = collider->BoundingBox.Size;
        const Vector3<float> boundingBox(size.X, size.Y, 0);
        Matrix4x4<float> boundingBoxModel;

        boundingBoxModel.Move(position.X, position.Y, 0);

        Matrix4x4<float> boundingBoxScaled = TransformBoundingBox(boundingBoxModel, boundingBox, false);
        const Vector3<float> colliderPosition = boundingBoxScaled.PositionXYZ();
        const Vector3<float> colliderScaling = boundingBoxScaled.ScaleXYZ();

        {
            Vector3<float> borderColor;

            switch (collider->Type)
            {
                case ColliderType::Gravity:
                {
                    GravityField& gravityField = *(GravityField*)collider;

                    model->ApplyGravity(gravityField->PullDirection, gravityField->PullForce, deltaTime);

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

            BoundingBoxRender(boundingBoxModel, boundingBox, borderColor);
        }


        for (LinkedListNode<Model*>* modelNode = _modelList.GetFirst(); modelNode ; modelNode = modelNode->Next)
        {
            Model* model = modelNode->Element;
            Matrix4x4<float> modelMatrix = model->MatrixModel;
            Vector3<float> modelBoundingBox(model->MeshList[0].Structure.Width, model->MeshList[0].Structure.Height, model->MeshList[0].Structure.Depth-50);
            Matrix4x4<float> boundingBoxModelScaled = TransformBoundingBox(modelMatrix, modelBoundingBox, false);
            Vector3<float> modelPosition = boundingBoxModelScaled.PositionXYZ();
            Vector3<float> modelScaling = boundingBoxModelScaled.ScaleXYZ();

           // modelScaling.Z = INFINITY;

            bool isColliding = collider->IsInBoundingBox(colliderPosition, colliderScaling, modelPosition, modelScaling);

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
    }  }
   

void BF::BitFireEngine::PrintContent(bool detailed)
{
    if (detailed)
    {
        const char* noValue = "| %-68s |\n";
        const char* message =
            "+---------------------------------------------------------+\n"
            "|  %-68s |\n"
            "+---------------------------------------------------------+\n";

        const char* endLine = "+-----+-----------------------+--------------------------------------+--------+\n\n";

        const char* line = "| %3i | %-21ls | %-36ls | %4i B |\n";

        printf(message, "Models");


        PXGraphic* pxGraphic = &this->_mainWindow.GraphicInstance;


        const size_t renderList = PXGraphicRenderableListSize(pxGraphic);


        for (size_t renderIndex = 0; renderIndex < renderList; ++renderIndex)
        {
            PXRenderable* pxRenderable;

            // Fetch
            {
                const PXBool succ = PXGraphicRenderableListGetFromIndex(pxGraphic, &pxRenderable, renderIndex);

                if (!succ)
                {
                    break; // Stop
                }
            }          

            size_t total = 0;

            printf("| %8s | %8s | %9s | %16s |\n", "Segment", "ShaderID", "TextureID", "NumberOfVertices");

            for (size_t i = 0; i < pxRenderable->MeshSegmentListSize; ++i)
            {
                const PXRenderableMeshSegment* const pxRenderableMeshSegment = &pxRenderable->MeshSegmentList[i];

                printf("| %2i/%2i | %8i | %9i | %16i |\n", i+1, pxRenderable->MeshSegmentListSize, pxRenderableMeshSegment->ShaderID, pxRenderableMeshSegment->TextureID, pxRenderableMeshSegment->NumberOfVertices);

                total += pxRenderableMeshSegment->NumberOfVertices;
            }

            printf("| VAO %2i, VBO %2i, IBO %2i | Vertex Total %-5i |\n", pxRenderable->VAO, pxRenderable->VBO, pxRenderable->IBO, total);
            printf("+---------------------------------------------------------+\n");
        }

        /*
        for(LinkedListNode<PXRenderable*>* currentRenderable = _renderList.GetFirst(); currentRenderable; currentRenderable = currentRenderable->Next)
        {
            const PXRenderable& renderable = *currentRenderable->Element;
            //const size_t chunkListSize = renderable.ChunkListSize;

            printf("ID:%i\n", renderable.ID);

            /*

            printf("| Rendable ID:%i |\n", renderable.ID);

            for(size_t c = 0; c < chunkListSize; c++)
            {
                const RenderableChunk renderableChunk = renderable.ChunkList[c];
                const size_t segmentListSize = renderableChunk.SegmentListSize;

                printf("| Mesh ID:%3i (%3zi/%3zi) |\n", renderableChunk.ID, c + 1, chunkListSize);

                printf("| ID                       | ShaderID  | TextureID | Size |\n");

                for(size_t i = 0; i < segmentListSize; i++)
                {
                    const RenderableSegment segment = renderableChunk.SegmentList[i];

                    printf
                    (
                        "| Segment ID:%3i (%3zi/%3zi) | %5i |\n",
                        segment.ID,
                        i + 1,
                        segmentListSize,
                        segment.Size
                    );

                    for(size_t i = 0; i < segment.MaterialRangeSize; i++)
                    {
                        const SegmentMaterialRange& segmentMaterialRange = segment.MaterialRange[i];

                        printf
                        (
                            "| >>> | %8i | %9i | %9i |\n",
                            segmentMaterialRange.ShaderID,
                            segmentMaterialRange.TextureID,
                            segmentMaterialRange.Size
                        );
                    }
                }
            }* /
        }



        printf(endLine);
        printf(message, "Images");

        for(LinkedListNode<PXTexture*>* currentTexture = _textureList.GetFirst(); currentTexture; currentTexture = currentTexture->Next)
        {
            const PXTexture& texture = *currentTexture->Element;

           // printf("| %3i | %4zix%4zi | \n", texture.ID, texture.DataImage.Width, texture.DataImage.Height );
        }

        printf(endLine);
        printf(message, "Shader");

        for(LinkedListNode<ShaderProgram*>* currentChaderProgram = _shaderProgramList.GetFirst(); currentChaderProgram; currentChaderProgram = currentChaderProgram->Next)
        {
            const ShaderProgram& shaderProgram = *currentChaderProgram->Element;


            printf("Shader ID:%3i \n", shaderProgram.ID);
        }* /



        /*

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
        printf(message, "Dialog");

        for (LinkedListNode<Dialog*>* dialogList = _dialogList.GetFirst(); dialogList; dialogList = dialogList->Next)
        {
            Dialog* dialog = dialogList->Element;

            printf(line, dialog->ID, dialog->Name, dialog->FilePath, sizeof(*dialog));
        }

        printf(endLine);* /
    }
    else
    {
        printf
        (
            "+--------------------------------------------------+\n"
            "| Loaded Resources\n"
            "| - Models <%u>\n"
            "| - Image  <%u>\n"
            "| - Sound  <%u>\n"
            "| - Font   <%u>\n"
            "| - Shader <%u>\n"
            "| - Dialog <%u>\n"
            "+--------------------------------------------------+\n",
            _renderList.Size(),
            _textureList.Size(),
            -1,//_soundList.Size(),
            _fontList.Size(),
            _shaderProgramList.Size(),
            -1//_dialogList.Size()
        );
    }* /
    }
}
*/



/*void BF::Rectangle::GenerateVertexData(float* vertexData, size_t vertexDataSize, unsigned int* indexData, size_t indexDataSize)
{
    float vertexDataInput[] =
    {
        Size.X, Size.Y, 0,  // top right
        Size.X, Position.Y, 0,  // bottom right
        Position.X, Position.Y, 0,  // bottom left
        Position.X, Size.Y, 0   // top left
    };

    const unsigned int indexListInput[] =
    {
        0, 1, 2, 3
    };

    const size_t vertexDataInputSize = sizeof(vertexDataInput);
    const size_t indexDataInputSize = sizeof(indexListInput);

    memcpy(vertexData, vertexDataInput, vertexDataInputSize);
    memcpy(indexData, indexListInput, indexDataInputSize);
}*/




/*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*


void BF::SystemSound::LoopPart(AudioSource& audioSource, float startIndex, float endIndex)
{
    alSourcei(audioSource.ID, AL_BYTE_OFFSET, (ALint)startIndex);
    alSourcei(audioSource.ID, AL_SEC_OFFSET, (ALint)endIndex);
}

*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
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
    float shaderID = ShaderHitBox.ID;

    OpenGL::UseShaderProgram(shaderID);
    _lastUsedShaderProgram = shaderID;
    CameraDataGet(shaderID);
    //OpenGL::TextureUse(ImageType::Texture2D, 0);
    CameraDataUpdate(MainCamera);
    int shaderColorID = OpenGL::ShaderGetUniformLocationID(shaderID, "HitBoxColor");

    boundingBoxScaled.Move(0, 0, -2);

    OpenGL::VertexArrayBind(CubeHitBoxViewModel.MeshList[0].Structure.VertexArrayID);
    OpenGL::ShaderSetUniformMatrix4x4(_matrixModelID, boundingBoxScaled.MatrixData);

    // Render outLine
    OpenGL::ShaderSetUniformVector4(shaderColorID, color.X, color.Y, color.Z, 1);
    OpenGL::Render(RenderMode::LineLoop, 0, 4);
    // Render middle
    OpenGL::ShaderSetUniformVector4(shaderColorID, color.X, color.Y, color.Z, 0.10f);
    OpenGL::Render(RenderMode::Square, 0, 4);
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
*/

void BFEngineConstruct(BFEngine* const bfEngine)
{
    PXMemoryClear(bfEngine, sizeof(BFEngine));

    PXCameraConstruct(&bfEngine->CameraPlayer);

    bfEngine->Engine.Window.EventReceiver = bfEngine;
    bfEngine->Engine.Window.MouseScrollCallBack = PXNull;
    bfEngine->Engine.Window.MouseClickCallBack = PXNull;
    bfEngine->Engine.Window.MouseClickDoubleCallBack = PXNull;
    bfEngine->Engine.Window.MouseEnterCallBack = PXNull;
    bfEngine->Engine.Window.MouseLeaveCallBack = PXNull;
    bfEngine->Engine.Window.MouseMoveCallBack = BFEngineOnMouseMove;
    bfEngine->Engine.Window.KeyBoardKeyCallBack = BFEngineOnKeyBoardKey;

    bfEngine->Engine.Owner = bfEngine;
    bfEngine->Engine.OnStartUp = BFEngineStart;
    bfEngine->Engine.OnShutDown = BFEngineStop;
    //bfEngine->Engine.OnUserUpdate = xxxxxxxx;
    //bfEngine->Engine.OnNetworkUpdate = xxxxxxxx;
    bfEngine->Engine.OnGameUpdate = BFEngineUpdate;
    bfEngine->Engine.OnRenderUpdate = BFEngineSceneRender;

    bfEngine->Engine.Window.WindowSizeChangedCallBack = BFEngineOnWindowSizeChanged;
}

void BFEngineOnMouseButton(const BFEngine* const receiver, const PXWindow* sender, const PXMouseButton mouseButton, const PXKeyPressState buttonState)
{

  

    //printf("[#][OnMouseButton]\n");
}

void BFEngineOnMouseMove(const BFEngine* const engine, const PXWindow* sender, const PXMouse* mouse)
{

#if UseRawMouseData

#else
    // Calculate relative input
    mouse.InputAxis[0] = mouse.Position[0] - deltaX;
    mouse.InputAxis[1] = mouse.Position[1] - deltaY;

    // Update position
    mouse.Position[0] = x;
    mouse.Position[1] = y;
#endif


    //printf("[#][OnMouseMove] X:%5i Y:%5i\n", mouse->Position[0], mouse->Position[1]);
    //printf("[#]------------- X:%5i Y:%5i\n", mouse->InputAxis[0], mouse->InputAxis[1]);
}

void BFEngineOnKeyBoardKey(const BFEngine* const engine, const PXWindow* sender, const PXKeyBoardKeyInfo keyBoardKeyInfo)
{
    BFInputContainer* input = &engine->InputContainer;
    KeyBoardCache* keyBoard = &input->KeyBoardInput;

    unsigned char* inputButton = 0;


    switch (keyBoardKeyInfo.Key)
    {
        case KeySpace: inputButton = &keyBoard->SpaceBar; break;
        case KeyShiftLeft: inputButton = &keyBoard->ShitftLeft; break;

        case KeyA:
        case KeyASmal: inputButton = &keyBoard->A; break;
        case KeyB:
        case KeyBSmal: inputButton = &keyBoard->B; break;
        case KeyC:
        case KeyCSmal: inputButton = &keyBoard->C; break;
        case KeyD:
        case KeyDSmal: inputButton = &keyBoard->D; break;
        case KeyE:
        case KeyESmal: inputButton = &keyBoard->E; break;
        case KeyF:
        case KeyFSmal: inputButton = &keyBoard->F; break;
        case KeyG:
        case KeyGSmal: inputButton = &keyBoard->G; break;
        case KeyH:
        case KeyHSmal: inputButton = &keyBoard->H; break;
        case KeyI:
        case KeyISmal: inputButton = &keyBoard->I; break;
        case KeyJ:
        case KeyJSmal: inputButton = &keyBoard->J; break;
        case KeyK:
        case KeyKSmal: inputButton = &keyBoard->K; break;

        case KeyL:
        case KeyLSmal: inputButton = &keyBoard->L; break;
        case KeyM:
        case KeyMSmal: inputButton = &keyBoard->M; break;
        case KeyN:
        case KeyNSmal: inputButton = &keyBoard->N; break;
        case KeyO:
        case KeyOSmal: inputButton = &keyBoard->O; break;
        case KeyP:
        case KeyPSmal: inputButton = &keyBoard->P; break;
        case KeyQ:
        case KeyQSmal: inputButton = &keyBoard->Q; break;
        case KeyR:
        case KeyRSmal: inputButton = &keyBoard->R; break;
        case KeyS:
        case KeySSmal: inputButton = &keyBoard->S; break;
        case KeyT:
        case KeyTSmal: inputButton = &keyBoard->T; break;
        case KeyU:
        case KeyUSmal: inputButton = &keyBoard->U; break;
        case KeyV:
        case KeyVSmal: inputButton = &keyBoard->V; break;
        case KeyW:
        case KeyWSmal:inputButton = &keyBoard->W; break;
        case KeyX:
        case KeyXSmal: inputButton = &keyBoard->X; break;
        case KeyY:
        case KeyYSmal: inputButton = &keyBoard->Y; break;
        case KeyZ:
        case KeyZSmal: inputButton = &keyBoard->Z; break;
    }

    if (!inputButton)
    {
        return;
    }

    switch (keyBoardKeyInfo.Mode)
    {
        case PXKeyPressStateDown:
        {
            PXInputButtonIncrement(inputButton);
            break;
        }
        case PXKeyPressStateUp:
        {
            PXInputButtonReset(inputButton);
            break;
        }
    }
}

void BFEngineOnWindowCreated(const BFEngine* const receiver, const PXWindow* sender)
{
    
}

void BFEngineOnWindowSizeChanged(const BFEngine* const receiver, const PXWindow* sender)
{
    return;

    if (receiver )
    {
        if (receiver->Engine.CameraCurrent)
        {
            PXCameraAspectRatioChange(receiver->Engine.CameraCurrent, sender->Width, sender->Height);
        }  
    }

    //printf("[Camera] Is now %i x %i\n", sender->Width, sender->Height);

    PXViewPort pxViewPort;
    pxViewPort.X = 0;
    pxViewPort.Y = 0;
    pxViewPort.Width = sender->Width;
    pxViewPort.Height = sender->Height;
    pxViewPort.ClippingMinimum = 0;
    pxViewPort.ClippingMaximum = 1;

    PXFunctionInvoke(receiver->Engine.Graphic.ViewPortSet, receiver->Engine.Graphic.EventOwner, &pxViewPort);
}

void BFEngineOnWindowsMouseCaptureChanged(const BFEngine* const receiver, const PXWindow* sender)
{

}

void BFEngineStart(BFEngine* const bfEngine, PXEngine* const pxEngine)
{ 
    PXLogPrint
    (
        PXLoggingInfo,
        "BFEngine",
        "Start",
        "Loading start..."
    );

    PXMemorySet(&bfEngine->pxModelTEST, 0, sizeof(PXModel));    

    PXStopWatch stopwatch;

    PXStopWatchConstruct(&stopwatch);

    // Create Banner
    {
        char stampBuffer[256];

        sprintf(stampBuffer, "%s - %s", __DATE__, __TIME__);

        printf
        (
           // LoggingInfo,
            "\n"
            "+++-----------------------------------------------------+++\n"
            "||| %51s |||\n"
            "+++-----------------------------------------------------+++\n"
            "|/| __________ .__   __  __________.__                  |/|\n"
            "|/| \\______   \\|__|_/  |_\\_  _____/|__|_______   ____   |/|\n"
            "|/|  |    |  _/|  |\\   __\\|  __)   |  |\\_  __ \\_/ __ \\  |/|\n"
            "|/|  |    |   \\|  | |  |  |  |     |  | |  | \\/\\  ___/  |/|\n"
            "|/|  |________/|__| |__|  \\__|     |__| |__|    \\_____> |/|\n"
            "|/|_____________________________________________________|/|\n"
            "+-+-----------------------------------------------------+-+\n\n",
            stampBuffer
        );
    }

    // Processor
    {
        PXProcessor processor;

        PXProcessorFetchInfo(&processor);

        printf
        (
            //LoggingInfo,
            "+---------------------------------------------------------+\n"
            "| Processor - Information                                 |\n"
            "+---------------------------------------------------------+\n"
            "| BrandName : %-43s |\n"
            "| Identity  : %-43s |\n"
            "| Cores     : %-43i |\n"
            "| Family    : %-43i |\n"
            "| Model     : %-43i |\n"
            "+---------------------------------------------------------+\n\n",
            processor.BrandName,
            processor.IdentityString,
            processor.NumberOfProcessors,
            processor.Family,
            processor.Model
        );
    }


    //SYSTEM_INFO systemInfo; // Windows SystemInfo
    //GetSystemInfo(&systemInfo);

   


    PXTime timeBefore;

    PXStopWatchTrigger(&stopwatch, &timeBefore);


   // PXFunctionInvoke(pxBitFireEngine->StartUpCallBack, pxBitFireEngine);


    PXCameraViewChangeToPerspective(bfEngine->Engine.CameraCurrent, 75, PXCameraAspectRatio(bfEngine->Engine.CameraCurrent), 0, 1);

    PXLogPrint
    (
        PXLoggingInfo,
        "BFEngine",
        "Load",
        "Done."
    ); 

    PXFunctionInvoke(bfEngine->OnStartUp, bfEngine, pxEngine);
}

void BFEngineUpdate(BFEngine* const bfEngine, PXEngine* const pxEngine)
{
    PXGraphic* const pxGraphic = &bfEngine->Engine.Graphic;
    // Pre-input

    //PXWindowUpdate(&pxBitFireEngine->WindowMain);


    {
        //const PXColorRGBAF pxColorRGBAF = { 0, 0, 0, 1 }; // 0.315, 0.15, 0.15
        //pxGraphic->Clear(pxGraphic->EventOwner, &pxColorRGBAF);
    }

    //---<Fetch UI-Input>----------------------------------------------------------
    {
        const PXSize uiElementAmount = pxGraphic->UIElementLookUp.EntryAmountCurrent;

        PXUIHoverState* lastEntry = 0;
        int lastTargetID = -1;

        PXMouse* const mouse = &bfEngine->Engine.Window.MouseCurrentInput;

        float mouseHitBoxOffset = 0.01f;
        float scale = PXWindowScreenRatio(&bfEngine->Engine.Window);
        float mouseAX = mouse->PositionNormalisized[0] + mouseHitBoxOffset * scale;
        float mouseAY = mouse->PositionNormalisized[1] - mouseHitBoxOffset * scale;
        float mouseBX = mouse->PositionNormalisized[0] - mouseHitBoxOffset * scale;
        float mouseBY = mouse->PositionNormalisized[1] + mouseHitBoxOffset * scale;


        bfEngine->CollisionCheckInfo.MousePosition[0] = mouseAX;
        bfEngine->CollisionCheckInfo.MousePosition[1] = mouseAY;
        bfEngine->CollisionCheckInfo.MousePosition[2] = mouseBX;
        bfEngine->CollisionCheckInfo.MousePosition[3] = mouseBY;




        // Drag
        if(lastTargetID != -1)
        {
            PXDictionaryEntry pxDictionaryEntry;

            PXDictionaryIndex(&pxGraphic->UIElementLookUp, lastTargetID, &pxDictionaryEntry);

            PXUIElement* const pxUIElement = *(PXUIElement**)pxDictionaryEntry.Value;
            PXKeyBoard* const keyBoard = &bfEngine->Engine.Window.KeyBoardCurrentInput;
            PXMouse* const mouse = &bfEngine->Engine.Window.MouseCurrentInput;

            if (IsPressedButtonLeft(mouse->Buttons))
            {
                
                //deltaNormal[0] *= 0.005f;
                //deltaNormal[1] *= 0.005f;
                float deadZone = 0.001f;               
                //deltaNormal[0] *= !PXMathIsInRange(deltaNormal[0], -deadZone, deadZone);
                //deltaNormal[1] *= !PXMathIsInRange(deltaNormal[1], -deadZone, deadZone);

               // printf("MD %8.6f, %8.6f\n", mouse->DeltaNormalisized[0], mouse->DeltaNormalisized[1]);

                float scale = 0.005f;

                pxUIElement->Margin.Left += mouse->Delta[0] * scale;
                pxUIElement->Margin.Top -= mouse->Delta[1] * scale;
                pxUIElement->Margin.Right += mouse->Delta[0] * scale;
                pxUIElement->Margin.Bottom -= mouse->Delta[1] * scale;

            }
        }  
    }
   //--------------------------------------------------------------------------


   //---<Update everything>----------------------------------------------------
    //PXFunctionInvoke(pxBitFireEngine->UpdateInputCallBack, pxBitFireEngine, &pxBitFireEngine->InputContainer);
 
    
    // 
   // 
    //UpdateInput(_inputContainer);


    // UI collision

    // Should we even try to check? if cursor is not locked, we cant even click.
#if 0       
    const PXBool shouldRegisterUIInput = pxBitFireEngine->WindowMain.CursorModeCurrent == PXWindowCursorShow;

    if (shouldRegisterUIInput)
    {
        float* mpos = pxBitFireEngine->WindowMain.MouseCurrentInput.PositionNormalisized;

        for (PXSize i = 0; i < pxBitFireEngine->WindowMain.GraphicInstance._pxUIElements.NodeListSizeCurrent; i++) // loop trough all ui elements
        {
            // if we found things, check collision
            PXLinkedListNodeFixed pxLinkedListNodeFixed;

            const PXBool successful = PXLinkedListFixedNodeAt(&pxBitFireEngine->WindowMain.GraphicInstance._pxUIElements, &pxLinkedListNodeFixed, i);

            if (!successful)
            {
                break;
            }

            PXUIElement* const uiElement = (PXUIElement*)pxLinkedListNodeFixed.BlockData;

            PXMatrix4x4F* matrix = &uiElement->Renderable.MatrixModel;

            //PXMatrix4x4FScaleGet(matrix, &buttonSize[0], &buttonSize[1], &buttonSize[2]);

            float mx = mpos[0];
            float my = -mpos[1];
            float bx = (1 - matrix->Data[ScaleX]) * matrix->Data[TransformX];
            float by = (1 - matrix->Data[ScaleY]) * matrix->Data[TransformY];
            float bWidth = (1 - matrix->Data[ScaleX]) * (matrix->Data[TransformX] + 1);
            float bHeight = (1 - matrix->Data[ScaleY]) * (matrix->Data[TransformY] + 1);

            PXBool isInX = bx <= mx && mx <= bWidth;
            PXBool isInY = by <= my && my <= bHeight;

            // printf("[x] S:%i,%i, M:%5.3f,%5.3f B:%5.3f,%5.3f\n", isInX, isInY, mx, my, bx, by);

            if (isInX && isInY)
            {
                if (!uiElement->HasMouseHover)
                {
                    uiElement->HasMouseHover = 1;

                    InvokeEvent(uiElement->OnMouseEnterCallback, uiElement);
                }
            }
            else
            {
                if (uiElement->HasMouseHover)
                {
                    uiElement->HasMouseHover = 0;
                    InvokeEvent(uiElement->OnMouseLeaveCallback, uiElement);
                }
            }
        }
    }
#endif


    //--------------------------------------------------------------------------

    //---<Render>---------------------------------------------------------------

    //---[Game-Logic]------------------------------------------------------
    //ModelsPhysicsApply(deltaTime);

   // PXFunctionInvoke(pxBitFireEngine->UpdateGameLogicCallBack, pxBitFireEngine, deltaTime);

    //---------------------------------------------------------------------

    //---[Render World]----------------------------------------------------    
    //BFEngineSceneRender(bfEngine);
    //---------------------------------------------------------------------
    // 
    //--------------------------------------------------------------------------

    //PXThreadSleep(0, 12);

    PXFunctionInvoke(bfEngine->OnGameUpdate, bfEngine, pxEngine);
}

void BFEngineStop(BFEngine* const bfEngine, PXEngine* const pxEngine)
{
    PXFunctionInvoke(bfEngine->OnShutDown, bfEngine, pxEngine);
}

void BFEngineSceneRender(BFEngine* const bfEngine, PXEngine* const pxEngine)
{
    PXGraphic* const pxGraphic = &bfEngine->Engine.Graphic;
    PXOpenGL* const openGLContext = &pxGraphic->OpenGLInstance;
    PXWindow* const window = (PXWindow*)pxGraphic->AttachedWindow;
    
    //-------------------------------------------------------------------------
    // UI-Rendering
    //-------------------------------------------------------------------------
#if 1

  
    PXGraphicUIElementIterator(pxGraphic, bfEngine, BFEngineUIElementRender, PXNull);

    PXGraphicUIElementIterator(pxGraphic, bfEngine, BFEngineUIElementCollision, PXNull);
#else
    PXFunctionInvoke(bfEngine->OnRenderUpdate, bfEngine, pxEngine);
#endif // 1



#if 0
    const PXSize uiElementAmount = pxGraphic->UIElementLookUp.EntryAmountCurrent;

    if(uiElementAmount > 0)
    {
        PXMouse* const mouse = &pxBitFireEngine->WindowMain.MouseCurrentInput;

        float mouseX = mouse->PositionNormalisized[0];
        float mouseY = mouse->PositionNormalisized[1];
     
        pxGraphic->DrawColorRGBAF(pxGraphic->EventOwner, 1, 1, 1, 1);

       // printf("%5.2f, %5.2f\n", mouseX, mouseY);

        float mouseHitBoxOffset = 0.05f;
       // glRectf(mouseX - mouseHitBoxOffset, mouseY + mouseHitBoxOffset, mouseX + mouseHitBoxOffset, mouseY - mouseHitBoxOffset);

        // glDisable(GL_DEPTH_TEST);
        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_ALPHA_TEST);   
        //glDepthFunc(GL_LEQUAL);
       /// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        for (PXSize i = 0; i < uiElementAmount; ++i)
        {
            PXDictionaryEntry pxDictionaryEntry;

            PXDictionaryIndex(&pxGraphic->UIElementLookUp, i, &pxDictionaryEntry);

            PXUIElement* const pxUIElement = *(PXUIElement**)pxDictionaryEntry.Value;

          
        }
    }
    //-------------------------------------------------------------------------
#endif

#if 0
    //-------------------------------------------------------------------------
    // 2D-Scene Rendering (Sprites)
    //-------------------------------------------------------------------------
    const PXSize spriteListSize = pxGraphic->SpritelLookUp.EntryAmountCurrent;

    for (PXSize i = 0; i < spriteListSize; ++i)
    {
        PXDictionaryEntry pxDictionaryEntry;

        PXDictionaryIndex(&pxGraphic->SpritelLookUp, i, &pxDictionaryEntry);

        PXSprite* const pxSprite = *(PXSprite**)pxDictionaryEntry.Value;

        PXGraphicSpriteDraw(pxGraphic, pxSprite, bfEngine->Engine.CameraCurrent);
    }
    //-------------------------------------------------------------------------
#endif
   // PXFunctionInvoke(bfEngine->OnRenderUpdate, bfEngine, pxEngine);
}

void BFEngineRenderScene(BFEngine* const bfEngine)
{
    PXGraphic* const pxGraphicContext = &bfEngine->Engine.Graphic;

    //-------------------------------------------------------------------------
    // 3D-Scene Rendering (Models)
    //-------------------------------------------------------------------------

    //PXOpenGLShaderProgramUse(openGLContext, 0); 

    const PXSize renderList = PXGraphicRenderableListSize(pxGraphicContext);

    for (PXSize renderIndex = 0; renderIndex < renderList; ++renderIndex)
    {
        PXRenderable* pxRenderable;

        // Fetch
        {
            const PXBool fetchSuccessful = PXGraphicRenderableListGetFromIndex(pxGraphicContext, &pxRenderable, renderIndex);

            if (!fetchSuccessful)
            {
                break; // Stop
            }
        }

        // Should be rendered?
        {
            const PXBool doRender = pxRenderable->DoRendering;

            if (!doRender)
            {
                continue;
            }
        }

#if 0
        // Shader
        {
            if (pxRenderable->MeshSegmentList)
            {
                const unsigned int shaderID = pxRenderable->MeshSegmentList[0].ShaderID;

                pxGraphicContext->ShaderProgramSelect(pxGraphicContext->EventOwner, shaderID);                

                pxGraphicContext->ShaderVariableIDFetch(pxGraphicContext->EventOwner, shaderID, &_matrixModelID, "MatrixModel");
                pxGraphicContext->ShaderVariableIDFetch(pxGraphicContext->EventOwner, shaderID, &_matrixViewID, "MatrixView");
                pxGraphicContext->ShaderVariableIDFetch(pxGraphicContext->EventOwner, shaderID, &_matrixProjectionID, "MatrixProjection");
                pxGraphicContext->ShaderVariableIDFetch(pxGraphicContext->EventOwner, shaderID, &_materialTextureID, "MaterialTexture");

                PXGraphicShaderUpdateMatrix4x4F(pxGraphicContext, _matrixViewID, bfEngine->CameraCurrent->MatrixView.Data);
                PXGraphicShaderUpdateMatrix4x4F(pxGraphicContext, _matrixProjectionID, bfEngine->CameraCurrent->MatrixProjection.Data);
                PXGraphicShaderUpdateMatrix4x4F(pxGraphicContext, _matrixModelID, pxRenderable->MatrixModel.Data);

                
            }
        }
#endif
  

       // PXGraphicVertexStructureDraw(&pxBitFireEngine->WindowMain.GraphicInstance, &pxBitFireEngine->pxModelTEST, &pxBitFireEngine->MainCamera);
    }






    /*

    for(size_t chunkIndex = 0; chunkIndex < renderable.ChunkListSize; ++chunkIndex)
    {
        const RenderableChunk& chunk = renderable.ChunkList[chunkIndex];
        const OpenGLID vertexDataBufferID = chunk.ID;

        assert(vertexDataBufferID != -1);

        glBindBuffer(GL_ARRAY_BUFFER, vertexDataBufferID); // AVO

        for(size_t segmentIndex = 0; segmentIndex < chunk.SegmentListSize; ++segmentIndex)
        {
            const RenderableSegment& segment = chunk.SegmentList[segmentIndex];
            ImageType textureType = segment.TextureType;
            const OpenGLID indexBufferID = segment.ID;
            //const size_t chunkSizeFull = segment.Size;
            size_t chunkSizeConsumed = 0;

            for(size_t i = 0; i < segment.MaterialRangeSize ; i++)
            {
                const SegmentMaterialRange& segmentMaterialRange = segment.MaterialRange[i];

                const OpenGLID shaderID = segmentMaterialRange.ShaderID != -1 ? segmentMaterialRange.ShaderID : _defaultShaderID;
                const OpenGLID textureID = segmentMaterialRange.TextureID != -1 ? segmentMaterialRange.TextureID : _defaultTextureID;
                const size_t chunkSizeElement = segmentMaterialRange.Size != -1 ? segmentMaterialRange.Size : 0;

                // assert(textureID != -1);
                assert(indexBufferID != -1);


                //printf("[Render] T:%i\n", textureID);

                // Check if shader need to be changed

                GraphicShaderUse(shaderID);

                CameraDataGet(shaderID);
                CameraDataUpdate(MainCamera);

                GraphicShaderUpdateMatrix4x4F(_matrixModelID, renderable.Data);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID); // IBO

                Use(textureType, textureID);

#if 0
                    glDrawElements(GL_POINTS, drawAmount, GL_UNSIGNED_INT, 0);
                    glDrawElements(GL_LINES, drawAmount, GL_UNSIGNED_INT, 0);
                    glDrawElements(renderModeID, drawAmount, GL_UNSIGNED_INT, 0);
#else


                    //glDrawArrays(GL_POINTS, chunkSizeConsumed, chunkSizeElement);
                    //glDrawArrays(GL_LINES, chunkSizeConsumed, chunkSizeElement);
                    glDrawArrays(renderModeID, chunkSizeConsumed, chunkSizeElement);
#endif // 0

                    chunkSizeConsumed += chunkSizeElement;

                   // Use(textureType, 0);
                }

                //printf("[>] Render %i\n", indexBufferID);
            }
        }
        */

        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);




        /*

        for (size_t meshIndex = 0; meshIndex < model->MeshListSize; meshIndex++)
        {
            Mesh& mesh = model->MeshList[meshIndex];
            float shaderProgramID = parentModel ? parentModel->SharedRenderInfoOverride.ShaderProgramID : mesh.RenderInfo.ShaderProgramID ;
            bool useDefaultShader = shaderProgramID == -1;
            bool changeShader = shaderProgramID != _lastUsedShaderProgram;
            bool isRegistered = ((int)1) >= 0;
            bool skipRendering = !(mesh.RenderInfo.ShouldBeRendered && isRegistered) || mesh.Structure.RenderType == RenderMode::Invalid;
            float vaoID = isSharedModel ? model->SharedModel->ID : mesh.Structure.VertexArrayID;
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
                    OpenGL::UseShaderProgram(shaderProgramID);

                    _lastUsedShaderProgram = shaderProgramID;

                    CameraDataGet(shaderProgramID);
                }

                CameraDataUpdate(MainCamera);
            }
            //-----------------------------------------------------------------

            OpenGL::VertexArrayBind(vaoID);

            //-----[Position]--------------------------------------------------
            OpenGL::ShaderSetUniformMatrix4x4(_matrixModelID, modelMatrix.Data);
            //-----------------------------------------------------------------

            //-----[Texture Lookup]--------------------------------------------
            float materialIndex = parentModel ? parentModel->SharedRenderInfoOverride.MaterialID : mesh.RenderInfo.MaterialID;
            float textureID = -1;

            if (materialIndex != -1)
            {
                const Material& material = model->MaterialList[materialIndex];

                if (material.Texture)
                {
                    const Image& image = *material.Texture;

                    textureID = image.ID;
                }
                else
                {
                    textureID = -1;
                }
            }
            else
            {
                textureID = _defaultTextureID;
            }

            OpenGL::TextureUse(ImageType::Texture2D, textureID);
            //-----------------------------------------------------------------

            //-----[RenderStyle]-----------------------------------------------
            OpenGL::Render(mesh.Structure.RenderType, 0, mesh.Structure.IndexDataSize);
            //-----------------------------------------------------------------

#if 1// Show HitBoxes
            Vector3<float> boundingBox(mesh.Structure.Width, mesh.Structure.Height, mesh.Structure.Depth);

            //BoundingBoxRender(model->MatrixModel, boundingBox, Vector3<float>(0, 1, 1));
#endif

        }
    }

    for(LinkedListNode<Collider*>* colliderCurrent = _physicList.GetFirst(); colliderCurrent; colliderCurrent = colliderCurrent->Next)
    {
        Collider* collider = colliderCurrent->Element;
        Vector3<float> color(1.0f, 1.0f, 1.0f);
        Vector2<float> position(collider->BoundingBox.X, collider->BoundingBox.Y);
        Vector2<float> size(collider->BoundingBox.Width, collider->BoundingBox.Height);
        Vector3<float> boundingBox(size.X, size.Y, 0);
        Matrix4x4<float> model;

        model.Move(position.X, position.Y, 0);

        switch(collider->Type)
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

     */
}

void PXPositionTranslate(PXRectangleOffset* const pxRectangleOffset)
{
    pxRectangleOffset->Left = -1 + pxRectangleOffset->Left;
    pxRectangleOffset->Top = -1 + pxRectangleOffset->Top; 
    pxRectangleOffset->Right = 1 - pxRectangleOffset->Right;
    pxRectangleOffset->Bottom = 1- pxRectangleOffset->Bottom;
}

void BFEngineUIElementCollision
(
    BFEngine* const bfEngine,
    PXUIElement* const pxUIElement
)
{
    const PXBool checkCollision = pxUIElement->FlagsList & PXUIElementIsHoverable;

    if (!checkCollision)
    {
        return;
    }

    PXRectangleOffset currentOffset;

    PXCopy(PXRectangleOffset, &pxUIElement->Margin, &currentOffset);

    // Calculate accululated offset
    for (PXUIElement* pxUIElementParent = pxUIElement->Parent; pxUIElementParent; pxUIElementParent = pxUIElementParent->Parent)
    {
        currentOffset.Left += pxUIElementParent->Margin.Left;
        currentOffset.Top += pxUIElementParent->Margin.Top;
        currentOffset.Right += pxUIElementParent->Margin.Right;
        currentOffset.Bottom += pxUIElementParent->Margin.Bottom;
    }



#if 0
    bfEngine->Engine.Graphic.DrawModeSet(bfEngine->Engine.Graphic.EventOwner, PXGraphicDrawFillModeLines);
    bfEngine->Engine.Graphic.DrawColorRGBAF(bfEngine->Engine.Graphic.EventOwner, 0, 0.7, 0, 1);
    bfEngine->Engine.Graphic.RectangleDraw
    (
        bfEngine->Engine.Graphic.EventOwner,
        bfEngine->CollisionCheckInfo.MousePosition[0],
        bfEngine->CollisionCheckInfo.MousePosition[1],
        bfEngine->CollisionCheckInfo.MousePosition[2],
        bfEngine->CollisionCheckInfo.MousePosition[3],
        0x01
    );
#endif

    PXPositionTranslate(&currentOffset);

#if 0
    bfEngine->Engine.Graphic.DrawModeSet(bfEngine->Engine.Graphic.EventOwner, PXGraphicDrawFillModeLines);
    bfEngine->Engine.Graphic.DrawColorRGBAF(bfEngine->Engine.Graphic.EventOwner, 0, 1, 0, 1);
    bfEngine->Engine.Graphic.RectangleDraw
    (
        bfEngine->Engine.Graphic.EventOwner,
        currentOffset.Left,
        currentOffset.Top,
        currentOffset.Right,
        currentOffset.Bottom,
        0x01
    );
#endif

    const PXBool isCollising = PXCollisionAABB
    (
        currentOffset.Left,
        currentOffset.Top,
        currentOffset.Right,
        currentOffset.Bottom,
        bfEngine->CollisionCheckInfo.MousePosition[0],
        bfEngine->CollisionCheckInfo.MousePosition[1],
        bfEngine->CollisionCheckInfo.MousePosition[2],
        bfEngine->CollisionCheckInfo.MousePosition[3]
    );

    if (!isCollising)
    {
        pxUIElement->Hover = PXUIHoverStateNotBeeingHovered;
        return; // Is not collideing, quit.
    }

    if (bfEngine->CollisionCheckInfo.CurrentElement) // if we have a current target, it will be overlapped now.
    {
        bfEngine->CollisionCheckInfo.OverlappedElement = bfEngine->CollisionCheckInfo.CurrentElement; // Store old entry as overlapped
        bfEngine->CollisionCheckInfo.OverlappedElement->Hover = PXUIHoverStateHoveredButOverlapped;
    }

    bfEngine->CollisionCheckInfo.CurrentElement = pxUIElement; // Store new element 
    bfEngine->CollisionCheckInfo.CurrentElement->Hover = PXUIHoverStateHovered;
}

void BFEngineUIElementRender(BFEngine* const bfEngine, PXUIElement* const pxUIElement)
{
    bfEngine->Engine.Graphic.ShaderProgramSelect(bfEngine->Engine.Graphic.EventOwner, 0);

    const PXBool isEnabled = pxUIElement->FlagsList & PXUIElementDoRendering;

    if (!isEnabled)
    {
#if 0
        printf("[Render] Canceled <%i>\n", pxUIElement->ID);
#endif
        return;
    }

    PXGraphic* const pxGraphic = &bfEngine->Engine.Graphic;

    PXRectangleOffset currentOffset;

    PXCopy(PXRectangleOffset, &pxUIElement->Margin, &currentOffset);

#if 0
    printf("[Render] Do <%i>\n", pxUIElement->ID);
#endif

    // Calculate accululated offset
    for (PXUIElement* pxUIElementParent = pxUIElement->Parent; pxUIElementParent; pxUIElementParent = pxUIElementParent->Parent)
    {
        currentOffset.Left += pxUIElementParent->Margin.Left;
        currentOffset.Top += pxUIElementParent->Margin.Top;
        currentOffset.Right += pxUIElementParent->Margin.Right;
        currentOffset.Bottom += pxUIElementParent->Margin.Bottom;
    }

#if 0 // Debug
    pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeLines);
    pxGraphic->DrawColorRGBAF(pxGraphic->EventOwner, 0.2f, 1.0f, 1.0f, 1.0f);
    pxGraphic->RectangleDraw(pxGraphic->EventOwner, currentOffset.Left, currentOffset.Top, currentOffset.Right, currentOffset.Bottom, 0x02);
    return;
#endif

    switch (pxUIElement->Type)
    {
        case PXUIElementTypePanel:
        {
            pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeFill);
            //pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeLines);

            const float colorSelectedOffset = (pxUIElement->Hover == PXUIHoverStateHovered) * 0.3f;
           // const float titleBarHeight = 0.06;
           // const float titleBarCorrectingOffset = 1.90;

            // Panel Color
            pxGraphic->DrawColorRGBAF
            (
                pxGraphic->EventOwner,
                pxUIElement->ColorTintReference->Red + colorSelectedOffset,
                pxUIElement->ColorTintReference->Green + colorSelectedOffset,
                pxUIElement->ColorTintReference->Blue + colorSelectedOffset,
                pxUIElement->ColorTintReference->Alpha
            );
            // Panel base
            pxGraphic->RectangleDraw(pxGraphic->EventOwner, currentOffset.Left, currentOffset.Top, currentOffset.Right, currentOffset.Bottom, 0x02);




            // title Color
            //pxGraphic->DrawColorRGBAF(pxGraphic->EventOwner, titleColor.Red, titleColor.Green, titleColor.Blue, titleColor.Alpha);

            // title base
            //pxGraphic->RectangleDraw(pxGraphic->EventOwner, currentOffset.Left, currentOffset.Top + titleBarCorrectingOffset, currentOffset.Right, currentOffset.Bottom, 0x02);


         //   PXUIElementColorSet4F(pxUIElement, uuu.Red, uuu.Green, uuu.Blue, uuu.Alpha);

          
           // pxGraphic->RectangleDraw(pxGraphic->EventOwner, currentOffset.Left, currentOffset.Top, currentOffset.Right, currentOffset.Bottom, 0x02);


            break;
        }
#if 1
        case PXUIElementTypeText:
        {
            PXFont* const font = pxUIElement->TextInfo.FontID;
            float offsetX = 0;         

            if (!font)
            {
                return;
            }

#if 1 // Text debug
            pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeFill);
            pxGraphic->DrawColorRGBAF(pxGraphic->EventOwner, 1,1,1,1);
            pxGraphic->Texture2DSelect(pxGraphic->EventOwner, &font->MainPage.Texture);
#endif

            PXOpenGLBlendingMode(pxGraphic->EventOwner, PXBlendingModeOneToOne); 

            for (PXSize i = 0; pxUIElement->TextInfo.Content[i]; ++i)
            {
                PXFontPageCharacter* const pxFontPageCharacter = PXFontPageCharacterFetch(&font->MainPage, pxUIElement->TextInfo.Content[i]);

                float textureWidth;
                float textureHeight;
                float charWidth;
                float charHeight;
                float charWidthSpacing;
                float tx1;
                float ty1;
                float tx2;
                float ty2;

                if (pxFontPageCharacter)
                {
                    textureWidth = font->MainPage.Texture.Image.Width;
                    textureHeight = font->MainPage.Texture.Image.Height;

                    charWidth = pxFontPageCharacter->Size[0];
                    charHeight = pxFontPageCharacter->Size[1];
                    charWidthSpacing = pxFontPageCharacter->XAdvance;

                    tx1 = pxFontPageCharacter->Position[0] / textureWidth;
                    ty1 = pxFontPageCharacter->Position[1] / textureHeight;
                    tx2 = ((pxFontPageCharacter->Position[0] + pxFontPageCharacter->Size[0]) / textureWidth);
                    ty2 = ((pxFontPageCharacter->Position[1] + pxFontPageCharacter->Size[1]) / textureHeight);
                }
                else
                {
                    textureWidth = 20;
                    textureHeight = 20;

                    charWidth = 40;
                    charHeight = 60;
                    charWidthSpacing = 45;

                    tx1 = 0;
                    ty1 = 0;
                    tx2 = 1;
                    ty2 = 1;
                }

                pxUIElement->TextInfo.Scale = 0.35;

                float sclaingWidth = pxUIElement->TextInfo.Scale * (9.0f / 16.0f);
                float scalingHeight = pxUIElement->TextInfo.Scale;

                float x1 = -1 + offsetX;// currentOffset.Left + offsetX; // offset // currentOffset.Left  
                float y1 = -1;// currentOffset.Bottom;

                // Add offset
                x1 += currentOffset.Left;
                y1 += currentOffset.Top;

                float x2 = (x1 + ((charWidth / textureWidth) * sclaingWidth));
                float y2 = (y1 + ((charHeight / textureHeight) * scalingHeight));

                offsetX += ((charWidthSpacing / textureWidth) * sclaingWidth);



                //x1 -= 1.0;
                //y1 += 0.9;
                //x2 -= 1.0;
                //y2 += 0.9;

                if (pxUIElement->TextInfo.Content[i] == ' ')
                {
                    continue;
                }

                pxGraphic->DrawColorRGBAF // Text color
                (
                    pxGraphic->EventOwner,
                    pxUIElement->ColorTintReference->Red,
                    pxUIElement->ColorTintReference->Green,
                    pxUIElement->ColorTintReference->Blue,
                    pxUIElement->ColorTintReference->Alpha
                );

#if 0 // Text debug
                pxGraphic->Texture2DSelect(pxGraphic->EventOwner, 0);
                pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeFill);
                pxGraphic->DrawColorRGBAF(pxGraphic->EventOwner, 0, 1, 0, 1);
                pxGraphic->RectangleDraw(pxGraphic->EventOwner, x1, y1, x2, y2, 0x01);
#else

                if (pxFontPageCharacter)
                {
                    pxGraphic->RectangleDrawTx(pxGraphic->EventOwner, x1, y1, x2, y2, tx1, ty1, tx2, ty2, 0x01);
                }
                else
                {
                    pxGraphic->Texture2DSelect(pxGraphic->EventOwner, PXNull);
                    pxGraphic->RectangleDraw(pxGraphic->EventOwner, x1, y1, x2, y2, 0x01);
                    pxGraphic->Texture2DSelect(pxGraphic->EventOwner, &font->MainPage.Texture);
                }
#endif // Text debug

            }

            pxGraphic->Texture2DSelect(pxGraphic->EventOwner, PXNull);
            PXOpenGLBlendingMode(pxGraphic, PXBlendingModeNone);

#if 0 // Text debug
            pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeFill);
            pxGraphic->DrawColorRGBAF(pxGraphic->EventOwner, 0, 1, 0, 1);
            pxGraphic->RectangleDraw(pxGraphic->EventOwner, currentOffset.Left, currentOffset.Top, currentOffset.Right, currentOffset.Bottom, 0x02);
#endif // Text debug


            break;
        }
        case PXUIElementTypeButton:
        {
            pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeFill);

            const float colorSelectedOffset = (pxUIElement->Hover == PXUIHoverStateHovered) * 0.3f;

            pxGraphic->DrawColorRGBAF
            (
                pxGraphic->EventOwner,
                pxUIElement->ColorTintReference->Red + colorSelectedOffset,
                pxUIElement->ColorTintReference->Green + colorSelectedOffset,
                pxUIElement->ColorTintReference->Blue + colorSelectedOffset,
                pxUIElement->ColorTintReference->Alpha
            );

            pxGraphic->RectangleDraw(pxGraphic->EventOwner, currentOffset.Left, currentOffset.Top, currentOffset.Right, currentOffset.Bottom, 0x02);

            break;
        }
        case PXUIElementTypeImage:
        {
            const float colorSelectedOffset = (pxUIElement->Hover == PXUIHoverStateHovered) * 0.3f;

            pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeFill);

            pxGraphic->DrawColorRGBAF
            (
                pxGraphic->EventOwner,
                pxUIElement->ColorTintReference->Red + colorSelectedOffset,
                pxUIElement->ColorTintReference->Green + colorSelectedOffset,
                pxUIElement->ColorTintReference->Blue + colorSelectedOffset,
                pxUIElement->ColorTintReference->Alpha
            );

            pxGraphic->Texture2DSelect(pxGraphic->EventOwner, pxUIElement->ImageInfo.TextureReference);
            pxGraphic->RectangleDrawTx(pxGraphic->EventOwner, currentOffset.Left, currentOffset.Top, currentOffset.Right, currentOffset.Bottom, 0, 1, 1, 0, 0x01);

            break;
        }
        case PXUIElementTypeDropDown:
        {
            pxGraphic->DrawColorRGBAF
            (
                pxGraphic->EventOwner,
                pxUIElement->ColorTintReference->Red,
                pxUIElement->ColorTintReference->Green,
                pxUIElement->ColorTintReference->Blue,
                pxUIElement->ColorTintReference->Alpha
            );

            pxGraphic->RectangleDrawTx(pxGraphic->EventOwner, currentOffset.Left, currentOffset.Top, currentOffset.Right, currentOffset.Bottom, 0, 1, 1, 0, 0x01);

            break;
        }
        case PXUIElementTypeToggle:
            break;

        case PXUIElementTypeCheckBox:
            break;

        case PXUIElementTypeColorPicker:
            break;

        case PXUIElementTypeSlider:
            break;

        case PXUIElementTypeRadioButton:
            break;

        case PXUIElementTypeToolTip:
            break;

        case PXUIElementTypeCustom:
            break;

        case PXUIElementTypeRenderFrame:
        {
#if 0
            pxGraphic->DrawColorRGBAF
            (
                pxGraphic->EventOwner,
                pxUIElement->ColorTintReference->Red,
                pxUIElement->ColorTintReference->Green,
                pxUIElement->ColorTintReference->Blue,
                pxUIElement->ColorTintReference->Alpha
            );
            pxGraphic->RectangleDraw(pxGraphic->EventOwner, currentOffset.Left, currentOffset.Top, currentOffset.Right, currentOffset.Bottom, 0x02);
#endif

#if 1
            PXWindow* const pxWindows = &bfEngine->Engine.Window;
            PXViewPort pxViewPort;

            // Offset -> -1/+1 => 0/2 => 0/1 => 
            float viewSize[4] =
            {
                pxWindows->Width* (((-1 + currentOffset.Left) + 1) / 2.0f),
                pxWindows->Height* (((-1 + currentOffset.Top) + 1) / 2.0f),
                pxWindows->Width* (((+1 - currentOffset.Right) + 1) / 2.0f),
                pxWindows->Height* (((+1 - currentOffset.Bottom) + 1) / 2.0f)
            };
            viewSize[2] -= viewSize[0];
            viewSize[3] -= viewSize[1];       

            // Render to our framebuffer
            //glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
            // Render on the whole framebuffer, complete from the lower left corner to the upper right
            PXViewPortSetXYWH(&pxViewPort, viewSize[0], viewSize[1], viewSize[2], viewSize[3]);
            pxGraphic->ViewPortSet(pxGraphic->EventOwner, &pxViewPort);

            // Make Black
            pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeFill);
            PXOpenGLDrawColorRGBF(&pxGraphic->OpenGLInstance, 0, 0, 0);
            PXOpenGLRectangleDraw(&pxGraphic->OpenGLInstance, -1, -1, 1, 1, 0x01);
     

            PXOpenGLSkyboxDraw(&pxGraphic->OpenGLInstance, bfEngine->DefaultSkyBox, bfEngine->Engine.CameraCurrent);

#if 1

            

            PXFunctionInvoke(bfEngine->OnRenderUpdate, bfEngine, &bfEngine->Engine);
     //       BFEngineRenderScene(bfEngine);
#else
        
    

            pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeLines);
            glLineWidth(10);
            PXOpenGLDrawBegin(&pxGraphic->OpenGLInstance, PXGraphicDrawModeTriangle);
            PXOpenGLDrawColorRGBF(&pxGraphic->OpenGLInstance, 1, 0, 0);
            PXOpenGLDrawVertexXYZF(&pxGraphic->OpenGLInstance, -0.5, -0.5, 0);
            PXOpenGLDrawColorRGBF(&pxGraphic->OpenGLInstance, 0, 0, 1);
            PXOpenGLDrawVertexXYZF(&pxGraphic->OpenGLInstance, 0.5, -0.5, 0);
            PXOpenGLDrawColorRGBF(&pxGraphic->OpenGLInstance, 0, 1, 0);
            PXOpenGLDrawVertexXYZF(&pxGraphic->OpenGLInstance, 0.0, 0.5, 0);
            PXOpenGLDrawEnd(&pxGraphic->OpenGLInstance);
            glLineWidth(1);
#endif
            // Render to our framebuffer
            //glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
            PXViewPortSetWH(&pxViewPort, pxWindows->Width, pxWindows->Height);
            pxGraphic->ViewPortSet(pxGraphic->EventOwner, &pxViewPort);

            pxGraphic->ShaderProgramSelect(pxGraphic->EventOwner, 0);

#endif

            break;
        }
#endif
        default:
            // Error
            break;
    }

    // Rendering panel border
    if (PXUIElementDrawBorder & pxUIElement->FlagsList)
    {
        glLineWidth(1);
        pxGraphic->DrawModeSet(pxGraphic->EventOwner, PXGraphicDrawFillModeLines);
        pxGraphic->DrawColorRGBAF(pxGraphic->EventOwner, 0.2f, 0.2f, 0.2f, 1.0f);
        pxGraphic->RectangleDraw(pxGraphic->EventOwner, currentOffset.Left, currentOffset.Top, currentOffset.Right, currentOffset.Bottom, 0x02);
    }   
}