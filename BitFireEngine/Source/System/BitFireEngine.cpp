#include "BitFireEngine.h"

#include "InputContainer.h"
#include "../UI/UIText.h"

#include <File/File.h>
#include <Media/Image/BMP/BMPP.h>
#include <Model/Model.h>
#include <Time/StopWatch.h>
#include <Text/Text.h>
#include <Graphic/OpenGL/OpenGL.h>
#include <Graphic/OpenGL/ResourceType.hpp>
#include <Async/Await.h>
#include <File/ParsingStream.h>

#include <stdlib.h>
#include <signal.h>
#include <Device/Controller.h>
#include <Event/Event.h>

OpenGLID _matrixModelID;
OpenGLID _matrixViewID;
OpenGLID _matrixProjectionID;
OpenGLID _materialTextureID;
RefreshRateMode RefreshRate;

void CameraDataGet(const unsigned int shaderID)
{
    _matrixModelID = BF::OpenGL::ShaderGetUniformLocationID(shaderID, "MatrixModel");
    _matrixViewID = BF::OpenGL::ShaderGetUniformLocationID(shaderID, "MatrixView");
    _matrixProjectionID = BF::OpenGL::ShaderGetUniformLocationID(shaderID, "MatrixProjection");
    _materialTextureID = BF::OpenGL::ShaderGetUniformLocationID(shaderID, "MaterialTexture");
}

void CameraDataUpdate(BF::Camera& camera)
{
    //BF::OpenGL::ShaderSetUniformMatrix4x4(_matrixModelID, camera.MatrixModel.Data);
    BF::Matrix4x4<float> viewModel = BF::Matrix4x4<float>(camera.MatrixModel);

    //auto pos = camera.MatrixModel.CurrentPosition();

    //viewModel.Multiply(camera.MatrixModel);

    //viewModel.Move(camera.MatrixModel.Data[11], camera.MatrixModel.Data[12], camera.MatrixModel.Data[13]);

    //viewModel.Print();

    BF::OpenGL::ShaderSetUniformMatrix4x4(_matrixViewID, camera.MatrixView.Data);
    BF::OpenGL::ShaderSetUniformMatrix4x4(_matrixProjectionID, camera.MatrixProjection.Data);
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
}

void BF::BitFireEngine::ErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    bool openGLspecific = type == GL_DEBUG_TYPE_ERROR;
    const char* sourceText = 0;
    const char* typeText = 0;
    const char* servertyText = 0;

    switch(source)
    {
        case GL_DEBUG_SOURCE_API:
            sourceText = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            sourceText = "Window";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            sourceText = "Shader";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            sourceText = "3rd Party";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            sourceText = "Application";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            sourceText = "Other";
            break;

        default:
            break;
    }

    switch(type)
    {
        case GL_DEBUG_TYPE_ERROR:
            typeText = "Error";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeText = "DEPRECATED_BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeText = "UNDEFINED_BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            typeText = "PORTABILITY";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            typeText = "PERFORMANCE";
            break;

        case GL_DEBUG_TYPE_OTHER:
            typeText = "OTHER";
            break;

        case GL_DEBUG_TYPE_MARKER:
            typeText = "MARKER";
            break;

        case GL_DEBUG_TYPE_PUSH_GROUP:
            typeText = "PUSH_GROUP";
            break;

        case GL_DEBUG_TYPE_POP_GROUP:
            typeText = "POP_GROUP";
            break;

        default:
            break;
    }

    switch(severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            servertyText = "High";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            servertyText = "Medium";
            break;

        case GL_DEBUG_SEVERITY_LOW:
            servertyText = "Low";
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            servertyText = "Info";
            break;

        default:
            break;
    }


    // (0x%x)

    fprintf
    (
        stderr,
        "[x][OpenGL][%s][%s][%s] %s\n",
        sourceText,
        typeText,
        servertyText,
        message
    );
}

void BF::BitFireEngine::Start()
{
    BF::StopWatch stopwatch;  

    printf
    (
        "+------------------------------------------------------+----------------------+\n"
        "| __________ .__   __  ___________.__                  |                      |\n"
        "| \\______   \\|__|_/  |_\\_   _____/|__|_______   ____   | Date %15s |\n"
        "|  |    |  _/|  |\\   __\\|   __)   |  |\\_  __ \\_/ __ \\  | Time %15s |\n"
        "|  |    |   \\|  | |  |  |   |     |  | |  | \\/\\  ___/  |                      |\n"
        "|  |________/|__| |__|  \\___|     |__| |__|    \\_____> |                      |\n"
        "+------------------------------------------------------+----------------------+\n",
        __DATE__,
        __TIME__
    );

    _imageAdd.Create();
    _modelAdd.Create();

    //SYSTEM_INFO systemInfo; // Windows SystemInfo
    //GetSystemInfo(&systemInfo);

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

    stopwatch.Start();

    _mainWindow.Create(600 * 2, 400 * 2, "[BFE] <BitFireEngine>");

    // Sound
    /*
    {
        //---<Select Device>
        _audioDevice = alcOpenDevice(nullptr);

        if (!_audioDevice)
        {
            // Failed to get Sound device
            ALCenum error;

            error = alGetError();

            if (error != AL_NO_ERROR)
            {
                // something wrong happened
            }
        }
        //----------------------------------------------


        // Create context
        _audioContext = alcCreateContext(_audioDevice, nullptr);
        bool contextCreationSuccessful = alcMakeContextCurrent(_audioContext);

        if (!contextCreationSuccessful)
        {
            // failed to make context current
        }

        /*
        // test for errors here using alGetError();

        ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

        alListener3f(AL_POSITION, 0, 0, 1.0f);
        // check for errors
        alListener3f(AL_VELOCITY, 0, 0, 0);
        // check for errors
        alListenerfv(AL_ORIENTATION, listenerOri);
        // check for errors

        * /
    }*/

    while(!_mainWindow.IsRunning);

    //AwaitChange(!_mainWindow.IsRunning);

    _mainWindow.FrameBufferContextRegister();

    InvokeEvent(this->StartUpCallBack, this);


    double time = stopwatch.Stop();

    printf("[i][Info] Loading took %.2fs\n", time);

    //PrintContent(true);

    IsRunning = true;
}

float _lastUIUpdate = 0;

void BF::BitFireEngine::Update()
{
    //---[Variable Reset]--------------------------------------------------
    float deltaTime = _stopWatch.Reset();
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

   _mainWindow.FrameBufferSwap();

   if(_mainWindow.HasSizeChanged)
   {
       const unsigned int width = _mainWindow.Width;
       const unsigned int height = _mainWindow.Height;

       printf("[Window] Size chnaged %i x %i\n", width, height);

       MainCamera.AspectRatioSet(width, height);

       glViewport(0, 0, width, height);

       _mainWindow.HasSizeChanged = false;
   }

    UpdateInput(_inputContainer);

    InvokeEvent(this->UpdateInputCallBack, this, _inputContainer);
    //---------------------------------------------------------------------
}

void BF::BitFireEngine::OnMouseButton(const void* const receiver, const CWindow* sender, const MouseButton mouseButton, const ButtonState buttonState)
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

void BF::BitFireEngine::OnMouseMove(const void* const receiver, const CWindow* sender, const Mouse* mouse)
{
    BitFireEngine& engine = *(BitFireEngine*)receiver;
    //Mouse& mouse = engine->_inputContainer.MouseInput;

#if UseRawMouseData
    //mouse.InputAxis[0] = -deltaX;
    //mouse.InputAxis[1] = -deltaY;

    //mouse.Position[0] = positionX;
    //mouse.Position[1] = positionY;
#else
    // Calculate relative input
    mouse.InputAxis[0] = mouse.Position[0] - deltaX;
    mouse.InputAxis[1] = mouse.Position[1] - deltaY;

    // Update position
    mouse.Position[0] = x;
    mouse.Position[1] = y;
#endif

 
  // printf("[#][OnMouseMove] X:%5i Y:%5i\n", mouse.Position[0], mouse.Position[1]);
  // printf("[#]------------- X:%5i Y:%5i\n", mouse.InputAxis[0], mouse.InputAxis[1]);
}

void BF::BitFireEngine::OnKeyBoardKey(const void* const receiver, const CWindow* sender, const KeyBoardKeyInfo keyBoardKeyInfo)
{
    BitFireEngine* engine = (BitFireEngine*)receiver;
    InputContainer& input = engine->_inputContainer;
    //KeyBoard& keyBoard = input.KeyBoardInput;

    /*InputButton* inputButton = nullptr;


    switch(keyBoardKeyInfo.Key)
    {
        case KeyBoardKey::KeySpace: inputButton = &keyBoard.SpaceBar; break;
        case KeyBoardKey::KeyShiftLeft: inputButton = &keyBoard.ShitftLeft; break;

        case KeyBoardKey::KeyA:
        case KeyBoardKey::KeyASmal: inputButton = &keyBoard.A; break;
         case KeyBoardKey::KeyB:
        case KeyBoardKey::KeyBSmal: inputButton = &keyBoard.B; break;
         case KeyBoardKey::KeyC:
        case KeyBoardKey::KeyCSmal: inputButton = &keyBoard.C; break;
         case KeyBoardKey::KeyD:
        case KeyBoardKey::KeyDSmal: inputButton = &keyBoard.D; break;
         case KeyBoardKey::KeyE:
        case KeyBoardKey::KeyESmal: inputButton = &keyBoard.E; break;
         case KeyBoardKey::KeyF:
        case KeyBoardKey::KeyFSmal: inputButton = &keyBoard.F; break;
         case KeyBoardKey::KeyG:
        case KeyBoardKey::KeyGSmal: inputButton = &keyBoard.G; break;
         case KeyBoardKey::KeyH:
        case KeyBoardKey::KeyHSmal: inputButton = &keyBoard.H; break;
         case KeyBoardKey::KeyI:
        case KeyBoardKey::KeyISmal: inputButton = &keyBoard.I; break;
         case KeyBoardKey::KeyJ:
        case KeyBoardKey::KeyJSmal: inputButton = &keyBoard.J; break;
         case KeyBoardKey::KeyK:
        case KeyBoardKey::KeyKSmal: inputButton = &keyBoard.K; break;

         case KeyBoardKey::KeyL:
        case KeyBoardKey::KeyLSmal: inputButton = &keyBoard.L; break;
        case KeyBoardKey::KeyM:
        case KeyBoardKey::KeyMSmal: inputButton = &keyBoard.M; break;
        case KeyBoardKey::KeyN:
        case KeyBoardKey::KeyNSmal: inputButton = &keyBoard.N; break;
        case KeyBoardKey::KeyO:
        case KeyBoardKey::KeyOSmal: inputButton = &keyBoard.O; break;
        case KeyBoardKey::KeyP:
        case KeyBoardKey::KeyPSmal: inputButton = &keyBoard.P; break;
         case KeyBoardKey::KeyQ:
        case KeyBoardKey::KeyQSmal: inputButton = &keyBoard.Q; break;
        case KeyBoardKey::KeyR:
        case KeyBoardKey::KeyRSmal: inputButton = &keyBoard.R; break;
       case KeyBoardKey::KeyS:
        case KeyBoardKey::KeySSmal: inputButton = &keyBoard.S; break;
        case KeyBoardKey::KeyT:
        case KeyBoardKey::KeyTSmal: inputButton = &keyBoard.T; break;
        case KeyBoardKey::KeyU:
        case KeyBoardKey::KeyUSmal: inputButton = &keyBoard.U; break;
        case KeyBoardKey::KeyV:
        case KeyBoardKey::KeyVSmal: inputButton = &keyBoard.V; break;
        case KeyBoardKey::KeyW:
         case KeyBoardKey::KeyWSmal:inputButton = &keyBoard.W; break;
        case KeyBoardKey::KeyX:
        case KeyBoardKey::KeyXSmal: inputButton = &keyBoard.X; break;
          case KeyBoardKey::KeyY:
        case KeyBoardKey::KeyYSmal: inputButton = &keyBoard.Y; break;
         case KeyBoardKey::KeyZ:
        case KeyBoardKey::KeyZSmal: inputButton = &keyBoard.Z; break;
    }

    if(!inputButton)
    {
        return;
    }

    switch(keyBoardKeyInfo.Mode)
    {
        case ButtonDown:
        {
            inputButton->Increment();
            break;
        }
        case ButtonRelease:
        {
            inputButton->Reset();
            break;
        }
    }*/
}

void BF::BitFireEngine::OnWindowCreated(const void* const receiver, const CWindow* sender)
{
    const CWindow& window = *sender;

    printf
    (
        "+------------------------------------------------------+\n"
        "| Graphics Card - Information                          |\n"
        "+------------------------------------------------------+\n"
        "| Vendor           : %-33s |\n"
        "| Model            : %-33s |\n"
        "| OpenGL Version   : %-33s |\n"
        "| Texture Slots    : %-33u |\n"
        "| Maximal Textures : %-33u |\n"
        "+------------------------------------------------------+\n",
        OpenGL::GPUVendorName(),
        OpenGL::GPUModel(),
        OpenGL::GLSLVersionPrimary(),
        OpenGL::TextureMaxSlots(),
        OpenGL::TextureMaxLoaded()
    );

#if 0 // Debug
    glDebugMessageCallback(BF::BitFireEngine::ErrorMessageCallback, 0);
    glEnable(GL_DEBUG_OUTPUT);
#endif
}

void BF::BitFireEngine::OnWindowSizeChanged(const void* const receiver, const CWindow* sender, const size_t width, const size_t height)
{
    BitFireEngine* engine = (BitFireEngine*)receiver;
    Camera& camera = engine->MainCamera;

    printf("[Camera] Is now %li x %li\n", width, height);

    glViewport(0, 0, width, height);

    camera.AspectRatioSet(width, height);
}

void BF::BitFireEngine::OnSystemSignal(int signalID)
{

}

void BF::BitFireEngine::UpdateInput(InputContainer& input)
{
    /*
    KeyBoard& keyboard = input.KeyBoardInput;
    Mouse& mouse = input.MouseInput;
    Camera& camera = MainCamera;

    Vector3<float> movement;

    _callbackListener->OnUpdateInput(input);

    if(keyboard.J.IsShortPressed())
    {
        PrintContent(true);
    }

    if(keyboard.R.IsShortPressed())
    {
        switch(_mainWindow.CursorModeCurrent)
        {
            case CWindowCursorShow:
            {
                _mainWindow.CursorCaptureMode(CWindowCursorLockAndHide);
                break;
            }
            case CWindowCursorLockAndHide:
            {
                _mainWindow.CursorCaptureMode(CWindowCursorShow);
                break;
            }
        }

        keyboard.R.Value = 0xFF;
    }

    if(keyboard.K.IsShortPressed())
    {
        Image image;

        //_mainWindow.TakeScreenShot(image);

      //  ImageSave(L"ScreenShot.bmp", ImageFileFormatBitMap);
    }

    if(keyboard.E.IsShortPressed())
    {
        keyboard.E.Value = 0xFF;

        switch(camera.Perspective)
        {
            case CameraPerspective::Orthographic:
                camera.ViewChange(CameraPerspective::Perspective);
                break;

            case CameraPerspective::Perspective:
                camera.ViewChange(CameraPerspective::Orthographic);
                break;
        }
    }

#if 1 // DEBUG
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

    keyboard.IncrementButtonTick();
    mouse.ResetAxis();*/
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

    _imageAdd.Delete();
    _modelAdd.Delete();
}

void BF::BitFireEngine::Register(Texture& texture)
{
    Image& image = texture.DataImage;

    const OpenGLID format = ToImageFormat(image.Format);
    const OpenGLID textureType = ToImageType(texture.Type);

    if(!image.PixelData)
    {
        return; // No image data
    }

    glGenTextures(1, &texture.ID);

    glBindTexture(textureType, texture.ID);

    // Texture Style
    {
        const int textureWrapWidth = ImageWrapToOpenGLFormat(texture.WrapWidth);
        const int textureWrapHeight = ImageWrapToOpenGLFormat(texture.WrapHeight);
        const int textueFilterNear = ImageLayoutToOpenGLFormat(texture.LayoutNear);
        const int textueFilterFar = ImageLayoutToOpenGLFormat(texture.LayoutFar);

        glTexParameteri(textureType, GL_TEXTURE_WRAP_S, textureWrapWidth);
        glTexParameteri(textureType, GL_TEXTURE_WRAP_T, textureWrapHeight);
        glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, textueFilterNear);
        glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, textueFilterFar);
        glTexParameteri(textureType, GL_GENERATE_MIPMAP, GL_FALSE);
    }

    //glTexParameterf(textureType, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

    // ToDO: erro?
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(textureType, 0, GL_RGBA, image.Width, image.Height, 0, format, GL_UNSIGNED_BYTE, image.PixelData);

    //glGenerateMipmap(textureType);

    //glBindTexture(textureType, 0);


    if(_defaultTextureID == -1)
    {
        _defaultTextureID = texture.ID;
    }
}

void BF::BitFireEngine::Register(TextureCube& textureCube)
{
    OpenGLID textureID = -1;

    // Check
    {
        const bool isValid = textureCube.HasTextures();

        if(!isValid)
        {
            return;
        }
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    for(size_t i = 0; i < 6; i++)
    {
        Image& image = textureCube.ImageList[i];
        const unsigned int textureTypeID = (unsigned int)GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
        const unsigned int imageFormat = ToImageFormat(image.Format);
        const ImageType imageType = ToImageType(textureTypeID);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(textureTypeID, 0, GL_RGB, image.Width, image.Height, 0, imageFormat, GL_UNSIGNED_BYTE, image.PixelData);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    textureCube.ID = textureID;
}

void BF::BitFireEngine::Register(Renderable& renderable, const Model& model)
{
    //float vaoIDList[128u];
    //memset(vaoIDList, -1, 128u * sizeof(unsigned int));

    //glGenVertexArrays(numberOfMeshes, vaoIDList); // Generate VAOs

    glGenVertexArrays(1, &renderable.ID); // Create VAO

    glBindVertexArray(renderable.ID);

    // VBO creator
    {
        const size_t numberOfMeshes = model.MeshListSize;
        size_t meshIndexCounter = 0;

        OpenGLID meshIDList[128u];
        MemorySet(meshIDList, 128u * sizeof(OpenGLID), -1);

        glGenBuffers(numberOfMeshes, meshIDList); // Create VBO Buffers

        renderable.ChunkListSize = numberOfMeshes;
        renderable.ChunkList = new RenderableChunk[numberOfMeshes];

        for(size_t i = 0; i < numberOfMeshes; ++i)
        {
            const Mesh& mesh = model.MeshList[i];
            const size_t segmentListSize = mesh.SegmentListSize;
            const OpenGLID vertexBufferID = meshIDList[meshIndexCounter++];

            assert(vertexBufferID != -1);

            RenderableChunk& chunk = renderable.ChunkList[i];

            chunk.ID = vertexBufferID;
            chunk.SegmentListSize = segmentListSize;
            chunk.SegmentList = new RenderableSegment[segmentListSize];

            // Select VBO
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID); // Select Buffer
            glBufferData(GL_ARRAY_BUFFER, mesh.VertexDataListSize * sizeof(float), mesh.VertexDataList, GL_STATIC_DRAW);

            OpenGL::VertexAttributeArrayDefine(sizeof(float), mesh.VertexDataStructureListSize, mesh.VertexDataStructureList);

#if 0
            printf("+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+\n");

            printf
            (
                "| %7s | %7s | %7s | %7s | %7s | %7s | %7s | %7s | %7s | %7s | %7s | %7s |\n",
                "x",
                "y",
                "z",
                "nx",
                "ny",
                "nz",
                "r",
                "g",
                "b",
                "a",
                "u",
                "v"
            );

            for(size_t i = 0; i < mesh.VertexDataListSize; )
            {
                float x = mesh.VertexDataList[i++];
                float y = mesh.VertexDataList[i++];
                float z = mesh.VertexDataList[i++];

                float nx = mesh.VertexDataList[i++];
                float ny = mesh.VertexDataList[i++];
                float nz = mesh.VertexDataList[i++];

                float r = mesh.VertexDataList[i++];
                float g = mesh.VertexDataList[i++];
                float b = mesh.VertexDataList[i++];
                float a = mesh.VertexDataList[i++];

                float u = mesh.VertexDataList[i++];
                float v = mesh.VertexDataList[i++];

                printf
                (
                    "| %7.2f | %7.2f | %7.2f | %7.2f | %7.2f | %7.2f | %7.2f | %7.2f | %7.2f | %7.2f | %7.2f | %7.2f |\n",
                    x,
                    y,
                    z,
                    nx,
                    ny,
                    nz,
                    r,
                    g,
                    b,
                    a,
                    u,
                    v
                );
            }

            printf("+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+\n");
#endif
            size_t segmentIndexCounter = 0;

            OpenGLID segmentIDList[128u];
            MemorySet(segmentIDList, 128u * sizeof(OpenGLID), -1);

            glGenBuffers(segmentListSize, segmentIDList); // Generate IBO

            for(size_t segmentIndex = 0; segmentIndex < segmentListSize; ++segmentIndex)
            {
                const MeshSegment& meshSegment = mesh.SegmentList[segmentIndex];
                const OpenGLID indexBufferID = segmentIDList[segmentIndexCounter++];
                RenderableSegment& segment = chunk.SegmentList[segmentIndex];            

                assert(indexBufferID != -1);               

                segment.ID = indexBufferID;
                segment.Size = meshSegment.IndexDataListSize;


                segment.MaterialRangeSize = meshSegment.MaterialInfoSize;
                segment.MaterialRange = new SegmentMaterialRange[meshSegment.MaterialInfoSize];

                for(size_t i = 0; i < meshSegment.MaterialInfoSize; i++)
                {
                    const OBJElementMaterialInfo& info = meshSegment.MaterialInfo[i];
                    SegmentMaterialRange& range = segment.MaterialRange[i];

                    range.Size = info.Size;
                    range.TextureID = 3;
                    
                }

#if 0

                for(size_t i = 0; i < meshSegment.IndexDataListSize; )
                {
                    unsigned int x = meshSegment.IndexDataList[i++];
                    unsigned int y = meshSegment.IndexDataList[i++];
                    unsigned int z = meshSegment.IndexDataList[i++];

                    printf("| %5i | %5i | %5i |\n", x, y, z);
                }
#endif
                // Select IBÒ
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshSegment.IndexDataListSize * sizeof(unsigned int), meshSegment.IndexDataList, GL_STATIC_DRAW);
            }
        }
    }

   // printf("[OpenGL] Register Mesh <%ls> from <%ls>. Sub-Meshes <%zu>\n", , model.FilePath, model.MeshListSize);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Merge
}

void BF::BitFireEngine::Register(Renderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize)
{
    // Check
    {
        const bool hasData = vertexData && vertexDataSize && indexList && indexListSize;

        if(!hasData)
        {
            return;
        }
    }

    OpenGLID id[3] = { (unsigned int)-1,(unsigned int)-1,(unsigned int)-1 };

    glGenVertexArrays(1, &id[0]);

    glBindVertexArray(id[0]);

    glGenBuffers(2, &id[1]);

    glBindBuffer(GL_ARRAY_BUFFER, id[1]);
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize * sizeof(float), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexListSize * sizeof(unsigned int), indexList, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    renderable.ID = id[0];
    renderable.ChunkListSize = 1;
    renderable.ChunkList = new RenderableChunk();
    renderable.ChunkList->ID = id[1];
    renderable.ChunkList->SegmentListSize = 1;
    renderable.ChunkList->SegmentList = new RenderableSegment();
    renderable.ChunkList->SegmentList[0].ID = id[2];
    renderable.ChunkList->SegmentList[0].Size = indexListSize;
    renderable.ChunkList->SegmentList[0].MaterialRange = new SegmentMaterialRange();
    renderable.ChunkList->SegmentList[0].MaterialRangeSize = 1;
    renderable.ChunkList->SegmentList[0].MaterialRange[0].Size = indexListSize;
}

void BF::BitFireEngine::Register(SkyBox& skyBox)
{
    const float vertexData[] =
    {
         1,  1,  1,
        -1,  1,  1,
         1, -1,  1,
        -1, -1,  1,
         1,  1, -1,
        -1,  1, -1,
         1, -1, -1,
        -1, -1, -1,
    };
    const unsigned int indexList[] =
    {
        0,1,3,2, // Left OK
        6,7,5,4, // Right  OK
        4,5,1,0, // Top OK
        2,3,7,6, // Bot OK
        0,2,6,4, // Front OK
        5,7,3,1 // Back OK
    };
    const size_t vertexDataSize = sizeof(vertexData) / sizeof(float);
    const size_t indexListSize = sizeof(indexList) / sizeof(unsigned int);
    TextureCube& textureCube = skyBox.Texture;
    Renderable& renderable = skyBox.RenderInfo;

    Register(renderable, vertexData, vertexDataSize, indexList, indexListSize);
    Register(textureCube);

    renderable.TextureUse(textureCube.ID);
}

bool BF::BitFireEngine::Register(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath)
{
    Shader vertexShader;
    Shader fragmentShader;
    File vertexShaderFile;
    File fragmentFile;

    FileConstruct(&vertexShaderFile);
    FileConstruct(&fragmentFile);

    {
        const bool isAlreadyLoaded = shaderProgram.ID != -1;
        const bool hasEmptyPaths = !vertexShaderFilePath || !fragmentShaderFilePath;

        if(isAlreadyLoaded)
        {
            return false;
        }

        if(hasEmptyPaths)
        {
            return false;
        }
    }


    {
        const ActionResult actionResult = FileMapToVirtualMemoryW(&vertexShaderFile, vertexShaderFilePath, MemoryReadOnly);
        const unsigned char sucessful = ResultSuccessful == actionResult;

        if(!sucessful)
        {
            return false;
        }

        vertexShader.Type = ShaderTypeVertex;
        vertexShader.Content = (char*)vertexShaderFile.Data;
        vertexShader.ContentSize = vertexShaderFile.DataSize;
    }
  

    {
        const ActionResult actionResult = FileMapToVirtualMemoryW(&fragmentFile, fragmentShaderFilePath, MemoryReadOnly);
        const unsigned char sucessful = ResultSuccessful == actionResult;

        if(!sucessful)
        {
            return false;
        }

        fragmentShader.Type = ShaderTypeFragment;
        fragmentShader.Content = (char*)fragmentFile.Data;
        fragmentShader.ContentSize = fragmentFile.DataSize;
    }
    //-----

    const size_t shaderListSize = 2;
    const Shader* shaderList[shaderListSize]{ &vertexShader, &fragmentShader };
    const OpenGLID shaderProgrammID = OpenGL::ShaderProgramCreate();
    OpenGLID shaderIDList[shaderListSize] = { (unsigned int)-1,(unsigned int)-1 };
    unsigned int  sucessfulCounter = 0;
    bool isValidShader = false;

    for(size_t i = 0; i < shaderListSize; ++i)
    {
        const Shader& shader = *shaderList[i];
        const OpenGLID type = ToShaderType(shader.Type);
        const OpenGLID shaderID = OpenGL::ShaderCompile(type, shader.Content);
        const bool compileFailed = shaderID == -1;

        if(compileFailed)
        {
            isValidShader = false;

            const wchar_t* text = i == 0 ? vertexShaderFilePath : fragmentShaderFilePath;
            printf("[x][OpenGL][Shader] Failed to compile <%ls>!\n", text);
            break;
        }

        shaderIDList[i] = shaderID;

        isValidShader = true;

        glAttachShader(shaderProgrammID, shaderID);
    }

    if(isValidShader)
    {
        glLinkProgram(shaderProgrammID);
        glValidateProgram(shaderProgrammID);

        shaderProgram.ID = shaderProgrammID;
    }

    // We used the Shaders above to compile, these elements are not used anymore.
    for(size_t i = 0; i < shaderListSize; i++)
    {
        const OpenGLID shaderID = shaderIDList[i];
        const bool isLoaded = shaderID != -1;

        if(isLoaded)
        {
            glDeleteShader(shaderID);
        }
    }

    if(!isValidShader)
    {
        glDeleteProgram(shaderProgrammID);
    }

    FileDestruct(&vertexShaderFile);
    FileDestruct(&fragmentFile);

    return isValidShader;
}

void BF::BitFireEngine::Register(AudioSource& audioSource)
{
    /* REWORK THIS
    const float numberOfBuffers = 1u;
    unsigned int& sourceID = audioSource.ID;

    alGenSources(numberOfBuffers, &audioSource.ID);
    // check for errors

    Update(audioSource);

    */
}

void BF::BitFireEngine::Register(Font& font)
{

}

void BF::BitFireEngine::Register(AudioClip& audioClip, const Sound& sound)
{
    /* REWORK THIS
    const ALuint numberOfBuffers = 1;

    alGenBuffers(numberOfBuffers, &audioClip.ID);

    {
        const ALenum format = ToChannalFormat(sound.NumerOfChannels, sound.BitsPerSample);

        alBufferData(audioClip.ID, format, sound.Data, sound.DataSize, sound.SampleRate);
    }*/
}

void BF::BitFireEngine::Use(Texture& texture)
{
    Use(texture.Type, texture.ID);
}

void BF::BitFireEngine::Use(const ImageType imageType, const int textureID)
{
    const bool isValidTexture = textureID != -1 && imageType != ImageType::Invalid;

#if 1 // Ignore
    if(!isValidTexture)
    {
        return;
    }
#else
    assert(isValidTexture);
#endif

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture

    const OpenGLID imageTypeID = ToImageType(imageType);

    glBindTexture(imageTypeID, textureID);
}

void BF::BitFireEngine::Use(Renderable& renderable)
{
    // TODO
}

void BF::BitFireEngine::Use(SkyBox& skyBox)
{
    // TODO:TEST REMOVAL !!!    OpenGL::VertexArrayBind(skyBox.RenderInfo.VAO);

    OpenGLID skyBoxTextureLocation = OpenGL::ShaderGetUniformLocationID(skyBox.Shader.ID, "SkyBoxTexture");


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_CUBE_MAP);



    glUniform1i(skyBoxTextureLocation, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox.Texture.ID);
    // glBindTexture(GL_TEXTURE_2D, skyBox.Texture.ID);

}

void BF::BitFireEngine::Use(const AudioSource& audioSource, const AudioClip& audioClip)
{
    /*
    // Bind
    alSourcei(audioSource.ID, AL_BUFFER, audioClip.ID);
    // check for errors


    alSourcePlay(audioSource.ID);
    // check for errors

    //----<Check State>---------------
    //int sourceState;

    //alGetSourcei(audioSource.ID, AL_SOURCE_STATE, &sourceState);
    // check for errors
    //while (sourceState == AL_PLAYING)
    //{
        //alGetSourcei(audioSource.ID, AL_SOURCE_STATE, &sourceState);
        // check for errors
    //}
    //---------------------------------*/
}

void BF::BitFireEngine::Update(const AudioSource& audioSource)
{
    /*
    alSourcef(audioSource.ID, AL_PITCH, audioSource.Pitch);
    // check for errors
    alSourcef(audioSource.ID, AL_GAIN, audioSource.Volume);
    // check for errors
    alSource3f(audioSource.ID, AL_POSITION, audioSource.Position[0], audioSource.Position[1], audioSource.Position[2]);
    // check for errors
    alSource3f(audioSource.ID, AL_VELOCITY, audioSource.Velocity[0], audioSource.Velocity[1], audioSource.Velocity[2]);
    // check for errors
    alSourcei(audioSource.ID, AL_LOOPING, audioSource.Looping);
    */
}

void BF::BitFireEngine::UnRegister(AudioSource& audioSource)
{
    // alDeleteSources(1, &audioSource.ID);
}

void BF::BitFireEngine::UnRegister(AudioClip& audioClip)
{
    //  alDeleteBuffers(1, &audioClip.ID);
}

void BF::BitFireEngine::MakeRectangle(Renderable& renderable)
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

    renderable.Mode = RenderMode::Square;
}

ThreadResult BF::BitFireEngine::LoadResourceAsync(void* resourceAdress)
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

ActionResult BF::BitFireEngine::Load(Renderable& renderable, const wchar_t* filePath, bool loadAsynchronously)
{
    _modelAdd.Lock();
    _renderList.Add(&renderable);
    _modelAdd.Release();

    if(loadAsynchronously)
    {
        // ResourceAsyncLoadInfo* resourceAsyncLoadInfo = new ResourceAsyncLoadInfo();

        // Thread::Run(LoadResourceAsync, &model);
    }
    else
    {
        Model model;

        const ActionResult fileActionResult = model.Load(filePath);
        const bool successful = fileActionResult == ResultSuccessful;

        if(successful)
        {
            renderable.Mode = RenderMode::Triangle;

            Register(renderable, model);
        }
    }

    return ResultSuccessful;
}

ActionResult BF::BitFireEngine::Load(Model& model, const wchar_t* filePath, const bool loadAsynchronously)
{
    const ActionResult result = model.Load(filePath);

    return result;
}

ActionResult BF::BitFireEngine::Load(Renderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize)
{
    Register(renderable, vertexData, vertexDataSize, indexList, indexListSize);

    _modelAdd.Lock();
    _renderList.Add(&renderable);
    _modelAdd.Release();

    return ResultSuccessful;
}

ActionResult BF::BitFireEngine::Load(Image& image, const wchar_t* filePath, const bool loadAsynchronously)
{
    return ResultSuccessful;
}

ActionResult BF::BitFireEngine::Load(Texture& texture, const wchar_t* filePath, bool loadAsynchronously)
{
    Image& image = texture.DataImage;

    _imageAdd.Lock();
    _textureList.Add(&texture);
    _imageAdd.Release();

    if(loadAsynchronously)
    {
        ThreadRun(LoadResourceAsync, &image);

        return ResultSuccessful;
    }
    else
    {
        const ActionResult imageLoadResult = ImageLoadW(&image, filePath);
        const bool isSucessful = imageLoadResult == ResultSuccessful;

        if(isSucessful)
        {
            texture.Type = ImageType::Texture2D;
            texture.Filter = ImageFilter::Trilinear;
            texture.LayoutNear = ImageLayout::Linear;
            texture.LayoutFar = ImageLayout::Linear;
            texture.WrapHeight = ImageWrap::Repeat;
            texture.WrapWidth = ImageWrap::Repeat;

            Register(texture);
        }

        return imageLoadResult;
    }

    return ResultSuccessful;
}

ActionResult BF::BitFireEngine::Load(Font& font, const wchar_t* filePath, bool loadAsynchronously)
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

    return ResultSuccessful;
}

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

        if(soundLoadResult != ResultSuccessful)
        {
            delete soundAdress;

            return soundLoadResult;
        }

        Register(audioClip, sound);
    }

    return ResultSuccessful;
}

ActionResult BF::BitFireEngine::Load(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath)
{
    printf("[+][Resource] ShaderProgram V:<%ls> F:<%ls> loading...\n", vertexShaderFilePath, fragmentShaderFilePath);

    const bool firstShaderProgram = _shaderProgramList.Size() == 0;
    const bool isRegistered = shaderProgram.ID != -1;

    if(!isRegistered)
    {
        _shaderProgramList.Add(&shaderProgram);

        const bool successful = Register(shaderProgram, vertexShaderFilePath, fragmentShaderFilePath);

        if(firstShaderProgram && successful)
        {
            _defaultShaderID = shaderProgram.ID;

            CameraDataGet(_defaultShaderID);
        }
    }

    return ResultSuccessful;
}

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
            Font* font = new Font();

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
}

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

    File file;
    ParsingStream parsingStream;

    {
        const ActionResult mappingResult = FileMapToVirtualMemoryW(&file, filePath, MemoryReadOnly);
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
              }*/

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

                Font* font = new Font();

                Load(*font, filePathW);

                level.FontList[fontCounter++] = font;

                for(size_t i = 0; i < font->AdditionalResourceListSize; i++)
                {
                    font->AdditionalResourceList[i];
                }

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
}

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

    return ResultSuccessful;
}

ActionResult BF::BitFireEngine::Load(Collider* collider)
{
    _physicList.Add(collider);

    return ResultSuccessful;
}

ActionResult BF::BitFireEngine::Load(Sound& sound, const wchar_t* filePath, const bool loadAsynchronously)
{
    return ResultSuccessful;
}

ActionResult BF::BitFireEngine::Load
(
    SkyBox& skyBox,
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

    ShaderProgram& shaderProgram = skyBox.Shader;

    Load(shaderProgram, shaderVertex, shaderFragment);

    Image* imageList = skyBox.Texture.ImageList;

    const ActionResult textureRightResult = ImageLoadW(&imageList[0], textureRight);
    const ActionResult textureLeftResult = ImageLoadW(&imageList[1], textureLeft);
    const ActionResult textureTopResult = ImageLoadW(&imageList[2], textureTop);
    const ActionResult textureBottomResult = ImageLoadW(&imageList[3], textureBottom);
    const ActionResult textureBackResult = ImageLoadW(&imageList[4], textureBack);
    const ActionResult textureFrontResult = ImageLoadW(&imageList[5],textureFront);
    
    Register(skyBox);

    DefaultSkyBox = &skyBox;

    return ResultSuccessful;
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
    MainCamera.Update(deltaTime);

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

            OpenGL::UseShaderProgram(shaderID);
            _lastUsedShaderProgram = shaderID;

            CameraDataGet(shaderID);
            CameraDataUpdate(MainCamera);

            OpenGL::ShaderSetUniformMatrix4x4(_matrixViewID, viewTri.Data);
            //OpenGL::Use(*DefaultSkyBox);

            const OpenGLID vao = renderable.ID;
            const OpenGLID vbo = renderable.ChunkList[0].ID;
            const OpenGLID ibo = renderable.ChunkList[0].SegmentList[0].ID;

            assert(vao != -1);
            assert(vbo != -1);
            assert(ibo != -1);

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            Use(ImageType::TextureCubeContainer, renderable.ChunkList[0].SegmentList[0].MaterialRange[0].TextureID);

            glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);

            Use(ImageType::TextureCubeContainer, 0);
            OpenGL::DepthMaskEnable(true);
            OpenGL::DrawOrder(false);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    }

    glPointSize(10);
    glLineWidth(5);

    for(LinkedListNode<Renderable*>* currentModel = _renderList.GetFirst(); currentModel; currentModel = currentModel->Next)
    {
        const Renderable* renderableAdress = currentModel->Element;

        if(!renderableAdress)
        {
            continue;
        }

        const Renderable& renderable = *renderableAdress;
        const OpenGLID vertexArrayID = renderable.ID;
        const bool hasMesh = renderable.IsRegistered();
        const bool skipRendering = !(renderable.DoRendering && hasMesh);
        const OpenGLID renderModeID = ToRenderMode(renderable.Mode);

        if(skipRendering)
        {
            continue; // Skip to next model.
        }

        assert(vertexArrayID != -1);

        glBindVertexArray(vertexArrayID); // VAO

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

                    OpenGL::UseShaderProgram(shaderID);
                    CameraDataGet(shaderID);
                    CameraDataUpdate(MainCamera);
                    OpenGL::ShaderSetUniformMatrix4x4(_matrixModelID, renderable.Data);

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

        }      */
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
}

void BF::BitFireEngine::BoundingBoxRender(Matrix4x4<float> modelMatrix, Vector3<float> boundingBox, Vector3<float> color)
{

}

void BF::BitFireEngine::PrintContent(bool detailed)
{
    if(detailed)
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


        printf("+-----------------------------\n");

        for(LinkedListNode<Renderable*>* currentRenderable = _renderList.GetFirst(); currentRenderable; currentRenderable = currentRenderable->Next)
        {
            const Renderable& renderable = *currentRenderable->Element;
            const size_t chunkListSize = renderable.ChunkListSize;

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
            }
        }



        printf(endLine);
        printf(message, "Images");

        for(LinkedListNode<Texture*>* currentTexture = _textureList.GetFirst(); currentTexture; currentTexture = currentTexture->Next)
        {
            const Texture& texture = *currentTexture->Element;

            printf("| %3i | %4zix%4zi | \n", texture.ID, texture.DataImage.Width, texture.DataImage.Height );
        }

        printf(endLine);
        printf(message, "Shader");

        for(LinkedListNode<ShaderProgram*>* currentChaderProgram = _shaderProgramList.GetFirst(); currentChaderProgram; currentChaderProgram = currentChaderProgram->Next)
        {
            const ShaderProgram& shaderProgram = *currentChaderProgram->Element;


            printf("Shader ID:%3i \n", shaderProgram.ID);
        }



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

        printf(endLine);*/
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
    }
}

const unsigned short BF::BitFireEngine::ToRenderMode(const RenderMode renderMode)
{
    switch(renderMode)
    {
        case RenderMode::Point:
            return GL_POINTS;

        case RenderMode::Line:
            return GL_LINES;

        case RenderMode::LineAdjacency:
            return GL_LINES_ADJACENCY;

        case RenderMode::LineStripAdjacency:
            return GL_LINE_STRIP_ADJACENCY;

        case RenderMode::LineLoop:
            return GL_LINE_LOOP;

        case RenderMode::LineStrip:
            return GL_LINE_STRIP;

        case RenderMode::Triangle:
            return GL_TRIANGLES;

        case RenderMode::TriangleAdjacency:
            return GL_TRIANGLES_ADJACENCY;

        case RenderMode::TriangleFAN:
            return GL_TRIANGLE_FAN;

        case RenderMode::TriangleStrip:
            return GL_TRIANGLE_STRIP;

        case RenderMode::TriangleStripAdjacency:
            return GL_TRIANGLE_STRIP_ADJACENCY;

        case RenderMode::Square:
            return GL_QUADS;

        case RenderMode::Patches:
            return GL_PATCHES;

        case RenderMode::Invalid:
            return -1;
    }
}

const ShaderType BF::BitFireEngine::ToShaderType(const OpenGLID token)
{
    return ShaderType();
}

const OpenGLID BF::BitFireEngine::ToShaderType(ShaderType shaderType)
{
    switch(shaderType)
    {
        case ShaderTypeVertex:
            return GL_VERTEX_SHADER;

        case   ShaderTypeTessellationControl:
            return -1; // ???

        case   ShaderTypeTessellationEvaluation:
            return -1; // ???

        case   ShaderTypeGeometry:
            return GL_GEOMETRY_SHADER;

        case   ShaderTypeFragment:
            return GL_FRAGMENT_SHADER;

        case  ShaderTypeCompute:
            return GL_COMPUTE_SHADER;

        case ShaderTypeUnkown:
        default:
            return -1;
    }
}

const ImageDataFormat BF::BitFireEngine::ToImageFormat(const OpenGLID token)
{
    return ImageDataFormat();
}

const OpenGLID BF::BitFireEngine::ToImageFormat(ImageDataFormat imageFormat)
{
    switch(imageFormat)
    {
        case ImageDataFormatBGR:
            return GL_BGR;

        case ImageDataFormatBGRA:
            return GL_BGRA;

        case ImageDataFormatRGB:
            return GL_RGB;

        case ImageDataFormatRGBA:
            return GL_RGBA;

        case ImageDataFormatAlphaMask:
        default:
            return -1;
    }
}

const BF::ImageType BF::BitFireEngine::ToImageType(const OpenGLID token)
{
    switch(token)
    {
        case GL_TEXTURE_2D:
            return ImageType::Texture2D;

        case GL_TEXTURE_3D:
            return ImageType::Texture3D;

        case GL_TEXTURE_CUBE_MAP:
            return ImageType::TextureCubeContainer;

        case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
            return ImageType::TextureCubeRight;

        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
            return ImageType::TextureCubeLeft;

        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
            return ImageType::TextureCubeTop;

        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
            return ImageType::TextureCubeDown;

        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
            return ImageType::TextureCubeBack;

        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
            return ImageType::TextureCubeFront;

        default:
            return ImageType::Invalid;
    }
}

const OpenGLID BF::BitFireEngine::ToImageType(ImageType imageType)
{
    switch(imageType)
    {
        case ImageType::Texture2D:
            return GL_TEXTURE_2D;

        case ImageType::Texture3D:
            return GL_TEXTURE_3D;

        case ImageType::TextureCubeContainer:
            return GL_TEXTURE_CUBE_MAP;

        case ImageType::TextureCubeRight:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_X;

        case ImageType::TextureCubeLeft:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;

        case ImageType::TextureCubeTop:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;

        case ImageType::TextureCubeDown:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;

        case ImageType::TextureCubeBack:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;

        case ImageType::TextureCubeFront:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;

        default:
            return -1;
    }
}

int BF::BitFireEngine::ImageWrapToOpenGLFormat(ImageWrap imageWrap)
{
    switch(imageWrap)
    {
        case ImageWrap::NoModification:
            return GL_CLAMP_TO_BORDER;

        case ImageWrap::StrechEdges:
            return GL_CLAMP_TO_EDGE;

        case ImageWrap::StrechEdgesAndMirror:
            return GL_MIRROR_CLAMP_TO_EDGE;

        case ImageWrap::Repeat:
            return GL_REPEAT;

        case ImageWrap::RepeatAndMirror:
            return GL_MIRRORED_REPEAT;
    }
}

int BF::BitFireEngine::ImageLayoutToOpenGLFormat(ImageLayout layout)
{
    switch(layout)
    {
        case ImageLayout::Nearest:
            return GL_NEAREST;

        case ImageLayout::Linear:
            return GL_LINEAR;

        case ImageLayout::MipMapNearestNearest:
            return GL_NEAREST_MIPMAP_NEAREST;

        case ImageLayout::MipMapLinearNearest:
            return GL_LINEAR_MIPMAP_NEAREST;

        case ImageLayout::MipMapNNearestLinear:
            return GL_NEAREST_MIPMAP_LINEAR;

        case ImageLayout::MipMapLinearLinear:
            return GL_LINEAR_MIPMAP_LINEAR;
    }
}

unsigned int BF::BitFireEngine::ToChannalFormat(const unsigned short numerOfChannels, const unsigned short bitsPerSample)
{
    bool stereo = (numerOfChannels > 1);

    switch(bitsPerSample)
    {
        //case 16u:
        //    return stereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;

        //case 8u:
        //    return stereo ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;

        default:
            return -1;
    }
}

const char* BF::BitFireEngine::ShaderTypeToString(int type)
{
    switch(type)
    {
        case GL_VERTEX_SHADER:
            return "Vertex";

        case  GL_GEOMETRY_SHADER:
            return "Geometry";

        case  GL_FRAGMENT_SHADER:
            return "Fragment";

        case  GL_COMPUTE_SHADER:
            return "Compute";

        default:
            return "Unkown";
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
