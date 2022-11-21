#include "BitFireEngine.h"

#include "InputContainer.h"
#include "../UI/UIText.h"

#include <File/File.h>
#include <Format/Model.h>
#include <Text/Text.h>
#include <Graphic/Graphic.h>
#include <Async/Await.h>
#include <Time/PXStopWatch.h>

#include <stdlib.h>
#include <signal.h>
#include <Device/Controller.h>
#include <Event/Event.h>
#include <File/DataStream.h>
#include <Device/InputButton.h>
#include <Processor/Processor.h>

OpenGLID _matrixModelID;
OpenGLID _matrixViewID;
OpenGLID _matrixProjectionID;
OpenGLID _materialTextureID;
RefreshRateMode RefreshRate;

void CameraDataGet(PXWindow* const window, const unsigned int shaderID)
{
    _matrixModelID = GraphicShaderVariableIDFetch(&window->GraphicInstance, shaderID, "MatrixModel");
    _matrixViewID = GraphicShaderVariableIDFetch(&window->GraphicInstance, shaderID, "MatrixView");
    _matrixProjectionID = GraphicShaderVariableIDFetch(&window->GraphicInstance, shaderID, "MatrixProjection");
    _materialTextureID = GraphicShaderVariableIDFetch(&window->GraphicInstance, shaderID, "MaterialTexture");
}

void CameraDataUpdate(PXWindow* const window, PXCamera& camera)
{
    //BF::OpenGL::ShaderSetUniformMatrix4x4(_matrixModelID, camera.MatrixModel.Data);
    //Matrix4x4<float> viewModel = BF::Matrix4x4<float>(camera.MatrixModel);

    //auto pos = camera.MatrixModel.CurrentPosition();

    //viewModel.Multiply(camera.MatrixModel);

    //viewModel.Move(camera.MatrixModel.Data[11], camera.MatrixModel.Data[12], camera.MatrixModel.Data[13]);

    //viewModel.Print();

    GraphicShaderUpdateMatrix4x4F(&window->GraphicInstance, _matrixViewID, camera.MatrixView.Data);
    GraphicShaderUpdateMatrix4x4F(&window->GraphicInstance, _matrixProjectionID, camera.MatrixProjection.Data);
}


BF::BitFireEngine::BitFireEngine()
{
    IsRunning = false;
    _deltaTime = 0;

    _lastUsedShaderProgram = -1;
    _defaultShaderID = -1;
    _defaultTextureID = -1;
    DefaultSkyBox = nullptr;
    DefaultFont = nullptr;


    UpdateUICallBack = nullptr;
    StartUpCallBack = nullptr;
    ShutDownCallBack = nullptr;
    UpdateGameLogicCallBack = nullptr;
    UpdateInputCallBack = nullptr;

    PXCameraConstruct(&MainCamera);
}

void BF::BitFireEngine::Start()
{
    PXStopWatch stopwatch;

    // Create Banner
    {
        char stampBuffer[256];

        sprintf(stampBuffer, "%s - %s", __DATE__, __TIME__);

        printf
        (
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
        Processor processor;

        ProcessorFetchInfo(&processor);

        printf
        (
            "+---------------------------------------------------------+\n"
            "| Processor - Information                                 |\n"
            "+---------------------------------------------------------+\n"
            "| BrandName : %-43s |\n"
            "| Identity  : %-43s |\n"
            "| Cores     : %-43i |\n"
            "| Family    : %-43i |\n"
            "| Model     : %-43i |\n"
            "+---------------------------------------------------------+\n",
            processor.BrandName,
            processor.IdentityString,
            processor.NumberOfProcessors,
            processor.Family,
            processor.Model
        );
    }




   

    PXLockCreate(&_imageAdd);
    PXLockCreate(&_modelAdd);
    
    //SYSTEM_INFO systemInfo; // Windows SystemInfo
    //GetSystemInfo(&systemInfo);
    _mainWindow.EventReceiver = this;

    _mainWindow.MouseClickCallBack = OnMouseButton;
    _mainWindow.MouseMoveCallBack = OnMouseMove;
    _mainWindow.KeyBoardKeyCallBack = OnKeyBoardKey;
    _mainWindow.WindowCreatedCallBack = OnWindowCreated;
    _mainWindow.WindowSizeChangedCallBack = OnWindowSizeChanged;

    // Set signal
    {
        const auto functionPointer = signal(SIGABRT, OnSystemSignal);
        const bool validLinkage = functionPointer != SIG_ERR;

        if(!validLinkage)
        {
            fputs("[x][Core] An error occurred while setting a signal handler.\n", stderr);
        }
    }

    char* memww = (char*)MemoryAllocate(2048);

    PXLinkedListFixedNodeSet(&_renderList, memww, 2, (size_t)-1); // PXRendere
    PXLinkedListFixedNodeSet(&_textureList, memww+64, 2, sizeof(PXTexture));
    PXLinkedListFixedNodeSet(&_fontList, memww+128, 2, sizeof(PXFont));
    PXLinkedListFixedNodeSet(&_shaderProgramList, memww+256, 2, sizeof(ShaderProgram));



    PXTime timeBefore;

    PXStopWatchTrigger(&stopwatch, &timeBefore);


    PXWindowCreateA(&this->_mainWindow, -1, -1, "[BFE] <BitFireEngine>", 1);


    PXAwaitChangeCU(&_mainWindow.IsRunning);


    printf
    (
        "+---------------------------------------------------------+\n"
        "| Graphics Card - Information                             |\n"
        "+---------------------------------------------------------+\n"
        "| Vendor    : %-43s |\n"
        "| Model     : %-43s |\n"
        "| OpenGL    : %-43s |\n"
        "+---------------------------------------------------------+\n",
        _mainWindow.GraphicInstance.OpenGLInstance.Vendor,
        _mainWindow.GraphicInstance.OpenGLInstance.Renderer,
        _mainWindow.GraphicInstance.OpenGLInstance.VersionText    
    );



    PXCameraAspectRatioChange(&MainCamera, _mainWindow.Width, _mainWindow.Height);

    //AwaitChange(!_mainWindow.IsRunning);

    PXWindowCursorCaptureMode(&_mainWindow, PXWindowCursorLockAndHide);

    OpenGLContextSelect(&_mainWindow.GraphicInstance.OpenGLInstance);

    InvokeEvent(this->StartUpCallBack, this);


    PXTime timeAfter;

    PXStopWatchTrigger(&stopwatch, &timeAfter);

    size_t time = 0;// PXTimeMillisecondsDelta(&timeBefore, &timeAfter);
    float timeInS = time / 1000.0f;

    printf("[i][Info] Loading took %.2fs\n", timeInS);

    //PrintContent(true);

    IsRunning = true;
}

float _lastUIUpdate = 0;

void BF::BitFireEngine::Update()
{
    //---[Variable Reset]--------------------------------------------------
    PXTime current;

    PXTimeNow(&current);
    size_t deltaInt = PXTimeMillisecondsDelta(&_lastUpdate, &current);

    _lastUpdate = current;

    float deltaTime = deltaInt / 1000.0;
    _deltaTime = deltaTime;

    _lastUIUpdate += deltaTime;

    if(_lastUIUpdate >= .20f)
    {
        _lastUIUpdate = 0;
        //_callbackListener->OnUpdateUI();
    }
    //---------------------------------------------------------------------

    //---[User-Input]------------------------------------------------------
    const float red = 0.5f;
    const float green = 0.5f;
    const float blue = 0.5f;
    const float alpha = 1.0f;

    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if 0 // Triangle Test
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
    glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
    glEnd();
#else
    //---[Game-Logic]------------------------------------------------------
    //ModelsPhysicsApply(deltaTime);

    //_callbackListener->OnUpdateGameLogic(deltaTime);
    //---------------------------------------------------------------------

    //---[Render World]----------------------------------------------------
    ModelsRender(deltaTime);
    //---------------------------------------------------------------------
#endif

    GraphicImageBufferSwap(&_mainWindow.GraphicInstance);

   if(_mainWindow.HasSizeChanged)
   {
       const unsigned int width = _mainWindow.Width;
       const unsigned int height = _mainWindow.Height;

       printf("[Window] Size changed (%i x %i)\n", width, height);

       PXCameraAspectRatioChange(&MainCamera, width, height);

       glViewport(0, 0, width, height);

       _mainWindow.HasSizeChanged = false;
   }

    UpdateInput(_inputContainer);
    //---------------------------------------------------------------------
}

void BF::BitFireEngine::OnMouseButton(const void* const receiver, const PXWindow* sender, const MouseButton mouseButton, const ButtonState buttonState)
{
    BitFireEngine& engine = *(BitFireEngine*)receiver;

    /*
    Mouse& mouse = engine->_inputContainer.MouseInput;

    switch(mouseButton)
    {
        case MouseButtonLeft:
        {
            mouse.LeftButton.IncrementIfAlreadyPressed();
            break;
        }
        case MouseButtonMiddle:
        {
            mouse.ScrollButton.IncrementIfAlreadyPressed();
            break;
        }
        case MouseButtonRight:
        {
            mouse.RightButton.IncrementIfAlreadyPressed();
            break;
        }
    }*/

    //printf("[#][OnMouseButton]\n");
}

void BF::BitFireEngine::OnMouseMove(const void* const receiver, const PXWindow* sender, const Mouse* mouse)
{
    BitFireEngine& engine = *(BitFireEngine*)receiver;
    MouseCache& mouseInput = engine._inputContainer.MouseInput;

#if UseRawMouseData
    mouseInput.InputAxis[0] = -mouse->InputAxis[0];
    mouseInput.InputAxis[1] = -mouse->InputAxis[1];

    mouseInput.Position[0] = mouse->Position[0];
    mouseInput.Position[1] = mouse->Position[1];
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

void BF::BitFireEngine::OnKeyBoardKey(const void* const receiver, const PXWindow* sender, const KeyBoardKeyInfo keyBoardKeyInfo)
{
    BitFireEngine* engine = (BitFireEngine*)receiver;
    InputContainer& input = engine->_inputContainer;
    KeyBoardCache& keyBoard = input.KeyBoardInput;

    unsigned char* inputButton = nullptr;


    switch (keyBoardKeyInfo.Key)
    {
        case KeySpace: inputButton = &keyBoard.SpaceBar; break;
        case KeyShiftLeft: inputButton = &keyBoard.ShitftLeft; break;

        case KeyA:
        case KeyASmal: inputButton = &keyBoard.A; break;
        case KeyB:
        case KeyBSmal: inputButton = &keyBoard.B; break;
        case KeyC:
        case KeyCSmal: inputButton = &keyBoard.C; break;
        case KeyD:
        case KeyDSmal: inputButton = &keyBoard.D; break;
        case KeyE:
        case KeyESmal: inputButton = &keyBoard.E; break;
        case KeyF:
        case KeyFSmal: inputButton = &keyBoard.F; break;
        case KeyG:
        case KeyGSmal: inputButton = &keyBoard.G; break;
        case KeyH:
        case KeyHSmal: inputButton = &keyBoard.H; break;
        case KeyI:
        case KeyISmal: inputButton = &keyBoard.I; break;
        case KeyJ:
        case KeyJSmal: inputButton = &keyBoard.J; break;
        case KeyK:
        case KeyKSmal: inputButton = &keyBoard.K; break;

        case KeyL:
        case KeyLSmal: inputButton = &keyBoard.L; break;
        case KeyM:
        case KeyMSmal: inputButton = &keyBoard.M; break;
        case KeyN:
        case KeyNSmal: inputButton = &keyBoard.N; break;
        case KeyO:
        case KeyOSmal: inputButton = &keyBoard.O; break;
        case KeyP:
        case KeyPSmal: inputButton = &keyBoard.P; break;
        case KeyQ:
        case KeyQSmal: inputButton = &keyBoard.Q; break;
        case KeyR:
        case KeyRSmal: inputButton = &keyBoard.R; break;
        case KeyS:
        case KeySSmal: inputButton = &keyBoard.S; break;
        case KeyT:
        case KeyTSmal: inputButton = &keyBoard.T; break;
        case KeyU:
        case KeyUSmal: inputButton = &keyBoard.U; break;
        case KeyV:
        case KeyVSmal: inputButton = &keyBoard.V; break;
        case KeyW:
        case KeyWSmal:inputButton = &keyBoard.W; break;
        case KeyX:
        case KeyXSmal: inputButton = &keyBoard.X; break;
        case KeyY:
        case KeyYSmal: inputButton = &keyBoard.Y; break;
        case KeyZ:
        case KeyZSmal: inputButton = &keyBoard.Z; break;
    }

    if(!inputButton)
    {
        return;
    }

    switch(keyBoardKeyInfo.Mode)
    {
        case ButtonStateDown:
        {          
            InputButtonIncrement(inputButton);
            break;
        }
        case ButtonStateRelease:
        {
            InputButtonReset(inputButton);
            break;
        }
    }
}

void BF::BitFireEngine::OnWindowCreated(const void* const receiver, const PXWindow* sender)
{
    const PXWindow& window = *sender;

  
}

void BF::BitFireEngine::OnWindowSizeChanged(const void* const receiver, const PXWindow* sender, const size_t width, const size_t height)
{
    BitFireEngine* const engine = (BitFireEngine* const)receiver;

    if(engine)
    {
        PXCamera& camera = engine->MainCamera;

        PXCameraAspectRatioChange(&camera, width, height);
    }   

    printf("[Camera] Is now %zi x %zi\n", width, height);

    glViewport(0, 0, width, height);   
}

void BF::BitFireEngine::OnSystemSignal(int signalID)
{

}

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
            case CameraPerspective2D:                
                PXCameraViewChange(&MainCamera, PXCameraPerspective3D);
                break;

            case CameraPerspective3D:
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

void BF::BitFireEngine::Stop()
{
    IsRunning = false;

    UnloadAll();

    // Sound
    /*
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(_audioContext);
        alcCloseDevice(_audioDevice);
    }*/

    PXLockDelete(&_imageAdd);
    PXLockDelete(&_modelAdd);
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
    const ActionResult loadResult = resource->Load(filePath);

    printf("[#][Resource][ASYNC] Loaded <%ls> ... [%i]\n", filePath, loadResult);
    */
    return 0;
}

ActionResult BF::BitFireEngine::Load(PXRenderable& renderable, PXModel* model, const wchar_t* filePath, bool loadAsynchronously)
{
    PXLockEngage(&_modelAdd);
    PXLinkedListFixedNodeAdd(&_renderList, &renderable);
    PXLockRelease(&_modelAdd);
        
    if(loadAsynchronously)
    {
        //ResourceAsyncLoadInfo* resourceAsyncLoadInfo = new ResourceAsyncLoadInfo();

        // Thread::Run(LoadResourceAsync, &model);
    }
    else
    {
        const ActionResult fileActionResult = ModelLoadW(model, filePath);
        const bool successful = ActionSuccessful == fileActionResult;

        if(successful)
        {
            GraphicModelRegisterFromModel(&this->_mainWindow.GraphicInstance, &renderable, model);
        }
    }

    return ActionSuccessful;
}

ActionResult BF::BitFireEngine::Load(PXModel& model, const wchar_t* filePath, const bool loadAsynchronously)
{
    const ActionResult result = ActionInvalid;// model.Load(filePath);

    return result;
}

ActionResult BF::BitFireEngine::Load(PXRenderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize)
{
    /*
    Register(renderable, vertexData, vertexDataSize, indexList, indexListSize);

    _modelAdd.Lock();
    _renderList.Add(&renderable);
    _modelAdd.Release();*/

    return ActionSuccessful;
}

ActionResult BF::BitFireEngine::Load(Image& image, const wchar_t* filePath, const bool loadAsynchronously)
{
    return ActionSuccessful;
}

ActionResult BF::BitFireEngine::Load(PXTexture& texture, const wchar_t* filePath, bool loadAsynchronously)
{
    Image* image = &texture.Image;

    PXLockEngage(&_imageAdd);
    PXLinkedListFixedNodeAdd(&_textureList, &texture);
    PXLockRelease(&_imageAdd);

    if(loadAsynchronously)
    {
        PXThreadRun(0, LoadResourceAsync, &image);

        return ActionSuccessful;
    }
    else
    {
        const ActionResult imageLoadResult = ImageLoadW(image, filePath);
        const bool isSucessful = imageLoadResult == ActionSuccessful;

        if(isSucessful)
        {
            texture.Type = GraphicImageTypeTexture2D;
            texture.Filter = GraphicRenderFilterTrilinear;
            texture.LayoutNear = GraphicImageLayoutLinear;
            texture.LayoutFar = GraphicImageLayoutLinear;
            texture.WrapHeight = GraphicImageWrapRepeat;
            texture.WrapWidth = GraphicImageWrapRepeat;

            GraphicTextureRegister(&_mainWindow.GraphicInstance, &texture);
        }

        return imageLoadResult;
    }

    return ActionSuccessful;
}

ActionResult BF::BitFireEngine::Load(PXFont& font, const wchar_t* filePath, bool loadAsynchronously)
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
    }*/

    return ActionSuccessful;
}
/*
ActionResult BF::BitFireEngine::Load(AudioClip& audioClip, const wchar_t* filePath, bool loadAsynchronously)
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
        const ActionResult soundLoadResult = sound.Load(filePath);

        if(soundLoadResult != ActionSuccessful)
        {
            delete soundAdress;

            return soundLoadResult;
        }

        Register(audioClip, sound);
    }

    return ActionSuccessful;
}*/

ActionResult BF::BitFireEngine::Load(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath)
{
    printf("[+][Resource] ShaderProgram V:<%ls> F:<%ls> loading...\n", vertexShaderFilePath, fragmentShaderFilePath);
    
    const bool firstShaderProgram = _shaderProgramList.NodeListSizeCurrent == 0;
    const bool isRegistered = shaderProgram.ID != -1;

    if(!isRegistered)
    {
        PXLinkedListFixedNodeAdd(&_shaderProgramList, &shaderProgram);

        const ActionResult successful = GraphicShaderProgramCreateVFPath(&_mainWindow.GraphicInstance, &shaderProgram, vertexShaderFilePath, fragmentShaderFilePath);
     

        if(firstShaderProgram && successful)
        {
            _defaultShaderID = shaderProgram.ID;

            CameraDataGet(&_mainWindow, _defaultShaderID);
        }
    }

    return ActionSuccessful;
}

/*
ActionResult BF::BitFireEngine::Load(Resource* resource, const wchar_t* filePath, const bool loadAsynchronously)
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
}*/

ActionResult BF::BitFireEngine::Load(Level& level, const wchar_t* filePath, const bool loadAsynchronously)
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
        const ActionResult mappingResult = FileMapToVirtualMemoryW(&file, filePath, 0, MemoryReadOnly);
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

                const ActionResult result = Load(*loadedModel, filePathW, false);
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

                                    const ActionResult loadResult = Load(*texture, material.TextureFilePath, false);
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

                const ActionResult fileActionResult = Load(*texture, filePathW, false);
                const bool sucessful = fileActionResult == ResultSuccessful;

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

     */

return ActionSuccessful;
}
/*
ActionResult BF::BitFireEngine::Load(Sprite& sprite, const wchar_t* filePath)
{
    printf("[+][Resource] Sprite <%ls> loading...\n", filePath);

    Renderable& renderable = sprite;
    Texture* texture = sprite.UsedTexture = new Texture;

    const ActionResult textureLoadResult = Load(*texture, filePath, false);
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
ActionResult BF::BitFireEngine::Load(Sound& sound, const wchar_t* filePath, const bool loadAsynchronously)
{
    return ActionSuccessful;
}

*/

ActionResult BF::BitFireEngine::Load(Collider* collider)
{
   // _physicList.Add(collider);

    return ActionSuccessful;
}



ActionResult BF::BitFireEngine::Load
(
    PXSkyBox& skyBox,
    const wchar_t* shaderVertex,
    const wchar_t* shaderFragment,
    const wchar_t* textureRight,
    const wchar_t* textureLeft,
    const wchar_t* textureTop,
    const wchar_t* textureBottom,
    const wchar_t* textureBack,
    const wchar_t* textureFront
)
{
    printf("[+][Resource] SkyBox loading...\n");

    //ShaderProgram& shaderProgram = skyBox.Shader;

   // Load(shaderProgram, shaderVertex, shaderFragment);

    /*

    Image* imageList = skyBox.Texture.ImageList;

    const ActionResult textureRightResult = ImageLoadW(&imageList[0], textureRight);
    const ActionResult textureLeftResult = ImageLoadW(&imageList[1], textureLeft);
    const ActionResult textureTopResult = ImageLoadW(&imageList[2], textureTop);
    const ActionResult textureBottomResult = ImageLoadW(&imageList[3], textureBottom);
    const ActionResult textureBackResult = ImageLoadW(&imageList[4], textureBack);
    const ActionResult textureFrontResult = ImageLoadW(&imageList[5],textureFront);

    //GraphicSkyboxRegister(&skyBox);

    DefaultSkyBox = &skyBox;

    */

    return ActionSuccessful;
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
    }  */
}

void BF::BitFireEngine::ModelsRender(const float deltaTime)
{
    GraphicContext* graphicContext = &_mainWindow.GraphicInstance;

    //PXCameraUpdate(&MainCamera, deltaTime);

    /*

    if(1)// Render Skybox first, if it is used
    {
        const bool hasSkyBox = DefaultSkyBox != nullptr;

        OpenGL::RenderBothSides(true);

        if(hasSkyBox)
        {
            const SkyBox& skyBox = *DefaultSkyBox;
            const Renderable& renderable = skyBox.RenderInfo;
            const OpenGLID shaderID = skyBox.Shader.ID;
            Matrix4x4<float> viewTri(MainCamera.MatrixView);

            viewTri.ResetForthAxis();

            OpenGL::DepthMaskEnable(false);
            OpenGL::DrawOrder(true);

            GraphicShaderUse(shaderID);

            OpenGL::UseShaderProgram(shaderID);
            _lastUsedShaderProgram = shaderID;

            CameraDataGet(&_mainWindow, shaderID);
            CameraDataUpdate(graphicContext, MainCamera);

            OpenGL::ShaderSetUniformMatrix4x4(_matrixViewID, viewTri.Data);
            //OpenGL::Use(*DefaultSkyBox);

            const OpenGLID vao = renderable.ID;
            const OpenGLID vbo = renderable.ChunkList[0].ID;
            const OpenGLID ibo = renderable.ChunkList[0].SegmentList[0].ID;

            assert(vao != -1);
            assert(vbo != -1);
            assert(ibo != -1);

            OpenGLVertexArrayBind(&graphicContext->OpenGLInstance, vao);
            OpenGLBufferBind(&graphicContext->OpenGLInstance, OpenGLBufferArray, vbo);
            OpenGLBufferBind(&graphicContext->OpenGLInstance, OpenGLBufferElementArray, vbo);

            Use(ImageType::TextureCubeContainer, renderable.ChunkList[0].SegmentList[0].MaterialRange[0].TextureID);

            glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);

            GraphicTextureUse();
            
            Use(ImageType::TextureCubeContainer, 0);
            OpenGL::DepthMaskEnable(true);
            OpenGL::DrawOrder(false);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    }*/

  //  glDisable(GL_CULL_FACE);
    

    glPointSize(10);
    glLineWidth(5);


    PXLinkedListNodeFixed currentModel;

    PXLinkedListFixedNodeAt(&_renderList, &currentModel,0);

    do
    {
        const PXRenderable* const pxRenderable = (const PXRenderable* const)currentModel.BlockData;

        {
            const PXBool skip = !pxRenderable;

            if (skip)
            {
                break; // No data to render
            }
        }

        {
            const PXBool skip = !pxRenderable->DoRendering;

            if (skip)
            {
                continue;
            }
        }

        auto glContext = &_mainWindow.GraphicInstance.OpenGLInstance;

        // OpenGLVertexArrayBind(glContext, renderable.ID); ; // VAO
        GraphicShaderUse(&_mainWindow.GraphicInstance, 1);
        CameraDataGet(&_mainWindow, 1);
        CameraDataUpdate(&_mainWindow, MainCamera);

        GraphicShaderUpdateMatrix4x4F(&_mainWindow.GraphicInstance, _matrixModelID, pxRenderable->MatrixModel.Data);

        //glFrontFace(0x0900);

        OpenGLBufferBind(glContext, OpenGLBufferArray, pxRenderable->VBO);

        // Render mesh segments
        
        unsigned int renderAmountOffset = 0;

        OpenGLTextureActivate(glContext, 0);
        unsigned int shaderVarID = OpenGLShaderVariableIDGet(glContext, 1, "MaterialTexture");
        OpenGLShaderVariableIx1(glContext, shaderVarID, 0);

        for (size_t i = 0; i < pxRenderable->MeshSegmentListSize; ++i)
        {
            const PXRenderableMeshSegment* const pxRenderableMeshSegment = &pxRenderable->MeshSegmentList[i];
            const size_t renderAmount = pxRenderableMeshSegment->NumberOfVertices;
           
            OpenGLTextureBind(glContext, OpenGLTextureType2D, pxRenderableMeshSegment->TextureID);

            // Render
            //glDrawBuffer(GL_POINTS);
            //glDrawElements(GL_LINES, pxRenderable->RenderSize, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_POINTS, renderAmountOffset, renderAmount);
            //glDrawArrays(GL_LINES, 0, pxRenderable->RenderSize);
            glDrawArrays(GL_TRIANGLES, renderAmountOffset, renderAmount);

            renderAmountOffset += renderAmount;
        }
      

        OpenGLBufferUnbind(glContext, OpenGLBufferArray);

        //       OpenGLVertexArrayUnbind(glContext);
    } 
    while (PXLinkedListFixedNodeNext(&_renderList, &currentModel));




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

void BF::BitFireEngine::PrintContent(bool detailed)
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




        
        PXLinkedListNodeFixed currentModel;

        PXLinkedListFixedNodeAt(&_renderList, &currentModel, 0);

        do
        {
            const PXRenderable* const pxRenderable = (const PXRenderable* const)currentModel.BlockData;

            if (!pxRenderable)
            {
                break;
            }

            printf("| VAO %2i | VBO %2i | IBO %2i |\n", pxRenderable->VAO, pxRenderable->VBO, pxRenderable->IBO);

            size_t total = 0;

            printf("| %8s | %9s | %16s |\n", "ShaderID", "TextureID", "NumberOfVertices");

            for (size_t i = 0; i < pxRenderable->MeshSegmentListSize; ++i)
            {
                const PXRenderableMeshSegment* const pxRenderableMeshSegment = &pxRenderable->MeshSegmentList[i];

                printf("| %8i | %9i | %16i |\n", pxRenderableMeshSegment->ShaderID, pxRenderableMeshSegment->TextureID, pxRenderableMeshSegment->NumberOfVertices);

                total += pxRenderableMeshSegment->NumberOfVertices;
            }

            printf("| Total %-5i |\n", total);
            
     
        } while (PXLinkedListFixedNodeNext(&_renderList, &currentModel));


        printf("+-----------------------------\n");
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
        }*/



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
    }*/
    }
}



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
