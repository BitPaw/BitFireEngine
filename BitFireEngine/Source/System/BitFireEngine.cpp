#include "BitFireEngine.h"

#include <File/File.h>
#include <Image/BMP/BMP.h>
#include <Model/Model.h>
#include <Time/StopWatch.h>



#include "OpenGL.h"
#include "Device/InputContainer.h"

#include "../UI/UIText.h"

#include <stdlib.h>
#include <Controller/ControllerSystem.h>

int _matrixModelID;
int _matrixViewID;
int _matrixProjectionID;
int _materialTextureID;
BF::RefreshRateMode RefreshRate;

BF::BitFireEngine* BF::BitFireEngine::_instance = nullptr;

void CameraDataGet(unsigned int shaderID)
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

    BF::OpenGL::ShaderSetUniformMatrix4x4(_matrixViewID, camera.MatrixView.MatrixData);
    BF::OpenGL::ShaderSetUniformMatrix4x4(_matrixProjectionID, camera.MatrixProjection.MatrixData);
}


BF::BitFireEngine::BitFireEngine()
{
    _callbackListener = nullptr;
    IsRunning = false;
    _deltaTime = 0;

    _instance = this;

    _lastUsedShaderProgram = -1;
    _defaultShaderID = -1;
    _defaultTextureID = -1;
    DefaultSkyBox = nullptr;
    DefaultFont = nullptr;
}

void BF::BitFireEngine::SetCallBack(IBitFireEngineListener* callbackListener)
{
    _callbackListener = callbackListener;
}

void BF::BitFireEngine::ErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    bool openGLspecific = type == GL_DEBUG_TYPE_ERROR;
    const char* sourceText = 0;
    const char* typeText = 0;
    const char* servertyText = 0;

    switch (source)
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

    switch (type)
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

    switch (severity)
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

    stopwatch.Start();

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

    while (!_mainWindow.IsRunning);

    wglMakeCurrent(_mainWindow.HandleDeviceContext, _mainWindow.OpenGLRenderingContext);

    _callbackListener->OnStartUp();

    double time = stopwatch.Stop();

    printf("[i][Info] Loading took %.2fs\n", time);

    IsRunning = true;
}

float _lastUIUpdate = 0;

void BF::BitFireEngine::Update()
{
    //---[Variable Reset]--------------------------------------------------
    float deltaTime = _stopWatch.Reset();
    _deltaTime = deltaTime;

    _lastUIUpdate += deltaTime;

    if (_lastUIUpdate >= .20f)
    {
        _lastUIUpdate = 0;
        //_callbackListener->OnUpdateUI();
    }
    //---------------------------------------------------------------------

    //---[User-Input]------------------------------------------------------

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if 0 // Triangle Test       
        // glClearColor(0.5f, 0.5f, 0.5f, 1);

        glBegin(GL_POLYGON);
        glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
        glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
        glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
        glEnd();
#else
        //---[Game-Logic]------------------------------------------------------
        ModelsPhysicsApply(deltaTime);

        _callbackListener->OnUpdateGameLogic(deltaTime);
        //---------------------------------------------------------------------

        //---[Render World]----------------------------------------------------
        ModelsRender(deltaTime);
        //---------------------------------------------------------------------          
#endif

        glFlush();  // Flush drawing command buffer to make drawing happen as soon as possible.

        SwapBuffers(_mainWindow.HandleDeviceContext);

       //wglMakeCurrent(0, 0);
    

        UpdateInput(_inputContainer);
    _callbackListener->OnUpdateInput(_inputContainer);
    //---------------------------------------------------------------------
}

void BF::BitFireEngine::OnMouseButton(const MouseButton mouseButton, const ButtonState buttonState)
{
    BitFireEngine* engine = BitFireEngine::Instance();
    Mouse& mouse = engine->_inputContainer.MouseInput;

    switch (mouseButton)
    {
        case MouseButton::Left:
        {
            mouse.LeftButton.IncrementIfAlreadyPressed();
            break;
        }
        case MouseButton::Middle:
        {
            mouse.ScrollButton.IncrementIfAlreadyPressed();
            break;
        }
        case MouseButton::Right:
        {
            mouse.RightButton.IncrementIfAlreadyPressed();
            break;
        }
    }

    //printf("[#][OnMouseButton]\n");
}

void BF::BitFireEngine::OnMouseMove(const short x, const short y)
{
    BitFireEngine* engine = BitFireEngine::Instance();
    Mouse& mouse = engine->_inputContainer.MouseInput;
    Camera& camera = engine->MainCamera;
 
#if UseRawMouseData
    mouse.InputAxis[0] = -x;
    mouse.InputAxis[1] = -y;

    mouse.Position[0] -= x;
    mouse.Position[1] -= y;
#else
    // Calculate relative input
    mouse.InputAxis[0] = mouse.Position[0] - x;
    mouse.InputAxis[1] = mouse.Position[1] - y;

    // Update position
    mouse.Position[0] = x;
    mouse.Position[1] = y;
#endif   

    //printf("[#][OnMouseMove] X:%5i Y:%5i\n", mouse.InputAxis[0], mouse.InputAxis[1]);
}

void BF::BitFireEngine::OnKeyBoardKey(const KeyBoardKeyInfo keyBoardKeyInfo)
{
    BitFireEngine* engine = BitFireEngine::Instance();
    InputContainer& input = engine->_inputContainer;
    KeyBoard& keyBoard = input.KeyBoardInput;

    InputButton* inputButton = nullptr;
    

    switch (keyBoardKeyInfo.Key)
    {
        case KeyBoardKey::KeySpace: inputButton = &keyBoard.SpaceBar; break;
        case KeyBoardKey::KeyShiftLeft: inputButton = &keyBoard.ShitftLeft; break;

        case KeyBoardKey::KeyA: inputButton = &keyBoard.A; break;
        case KeyBoardKey::KeyB: inputButton = &keyBoard.B; break;
        case KeyBoardKey::KeyC: inputButton = &keyBoard.C; break;
        case KeyBoardKey::KeyD: inputButton = &keyBoard.D; break;
        case KeyBoardKey::KeyE: inputButton = &keyBoard.E; break;
        case KeyBoardKey::KeyF: inputButton = &keyBoard.F; break;
        case KeyBoardKey::KeyG: inputButton = &keyBoard.G; break;
        case KeyBoardKey::KeyH: inputButton = &keyBoard.H; break;
        case KeyBoardKey::KeyI: inputButton = &keyBoard.I; break;
        case KeyBoardKey::KeyJ: inputButton = &keyBoard.J; break;
        case KeyBoardKey::KeyK: inputButton = &keyBoard.K; break;
        case KeyBoardKey::KeyL: inputButton = &keyBoard.L; break;
        case KeyBoardKey::KeyM: inputButton = &keyBoard.M; break;
        case KeyBoardKey::KeyN: inputButton = &keyBoard.N; break;
        case KeyBoardKey::KeyO: inputButton = &keyBoard.O; break;
        case KeyBoardKey::KeyP: inputButton = &keyBoard.P; break;
        case KeyBoardKey::KeyQ: inputButton = &keyBoard.Q; break;
        case KeyBoardKey::KeyR: inputButton = &keyBoard.R; break;
        case KeyBoardKey::KeyS: inputButton = &keyBoard.S; break;
        case KeyBoardKey::KeyT: inputButton = &keyBoard.T; break;
        case KeyBoardKey::KeyU: inputButton = &keyBoard.U; break;
        case KeyBoardKey::KeyV: inputButton = &keyBoard.V; break;
        case KeyBoardKey::KeyW: inputButton = &keyBoard.W; break;
        case KeyBoardKey::KeyX: inputButton = &keyBoard.X; break;
        case KeyBoardKey::KeyY: inputButton = &keyBoard.Y; break;
        case KeyBoardKey::KeyZ: inputButton = &keyBoard.Z; break;
    }

    if (!inputButton)
    {
        return;
    }

    switch (keyBoardKeyInfo.Mode)
    {
        case ButtonState::Down:
        {
            inputButton->Increment();   
            break;
        }
        case ButtonState::Release:
        {
            inputButton->Reset();
            break;
        }
    }   
}

void BF::BitFireEngine::OnWindowCreated(Window& window)
{
    const PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    int letWindowsChooseThisPixelFormat = ChoosePixelFormat(window.HandleDeviceContext, &pfd);
    SetPixelFormat(window.HandleDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

    window.OpenGLRenderingContext = wglCreateContext(window.HandleDeviceContext);
    wglMakeCurrent(window.HandleDeviceContext, window.OpenGLRenderingContext);

    //GLEW
    {
        printf("[i][GLEW] Initialize... ");

        const GLenum result = glewInit();
        const bool success = result == GLEW_OK;

        printf("[%s]\n", (success ? "OK" : "Failed"));

        if (!success)
        {
            switch (result)
            {
                case GLEW_OK: // No Error
                {
                    break;
                }
                case GLEW_ERROR_NO_GL_VERSION:   /* missing GL version */
                {
                    printf("[x][OpenGL] No Version detected. Is the contect created?\n");
                    break;
                }
                case GLEW_ERROR_GL_VERSION_10_ONLY: /* Need at least OpenGL 1.1 */
                {
                    printf("[x][OpenGL] Version is outdated. You need al least Version 1.1\n");
                    break;
                }
                case GLEW_ERROR_GLX_VERSION_11_ONLY:  /* Need at least GLX 1.2 */
                {
                    printf("[x][OpenGL] Version is outdated. You need al least Version 1.2\n");
                    break;
                }
                case GLEW_ERROR_NO_GLX_DISPLAY:  /* Need GLX display for GLX support */
                {
                    printf("[x][OpenGL] No display detected that can support OpenGL\n\n");
                    break;
                }
                default:
                    break;
            }
        }

        glDebugMessageCallback(BF::BitFireEngine::ErrorMessageCallback, 0);
        glEnable(GL_DEBUG_OUTPUT);
    }

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

    if (true)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    if (true) // X-RAY
    {
        glEnable(GL_DEPTH_TEST);
    }

    if (true)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_COLOR, GL_DST_COLOR);

         //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    }

    wglMakeCurrent(0, 0);
}

void BF::BitFireEngine::OnWindowSizeChanged(const unsigned int width, const unsigned int height)
{
    BitFireEngine* engine = BitFireEngine::Instance();
    Camera& camera = engine->MainCamera;

    glViewport(0, 0, width, height);

    camera.AspectRatioSet(width, height);
}

void BF::BitFireEngine::UpdateInput(InputContainer& input)
{
    KeyBoard& keyboard = input.KeyBoardInput;
    Mouse& mouse = input.MouseInput;
    Camera& camera = MainCamera;

    Vector3<float> movement;

    _callbackListener->OnUpdateInput(input);

    if (keyboard.J.IsShortPressed())
    {
        PrintContent(true);
    }

    if (keyboard.R.IsShortPressed())
    {
        switch (_mainWindow.CursorCaptureMode())
        {
            case CursorMode::Show:
            {
                _mainWindow.CursorCaptureMode(CursorMode::Locked);
                break;
            }
            case CursorMode::Locked:
            {
                _mainWindow.CursorCaptureMode(CursorMode::Show);
                break;
            }
        }
       
        keyboard.R.Value = 0xFF;
    }

    if (keyboard.K.IsShortPressed())
    {
        Image image;

        //_mainWindow.TakeScreenShot(image);

        image.Save(L"ScreenShot.bmp", ImageFileFormat::BitMap);
    }

    if (keyboard.E.IsShortPressed())
    {
        keyboard.E.Value = 0xFF;

        switch (camera.Perspective)
        {
            case CameraPerspective::Orthographic:
                camera.PerspectiveChange(CameraPerspective::Perspective);
                break;

            case CameraPerspective::Perspective:
                camera.PerspectiveChange(CameraPerspective::Orthographic);
                break;
        }
    }

#if 1 DEBUG
    if (keyboard.ShitftLeft.IsPressed()) { movement.Add(0, -1, 0); }
    if (keyboard.W.IsPressed()) { movement.Add(0, 0, 1); }
    if (keyboard.A.IsPressed()) { movement.Add(-1, 0, 0); }
    if (keyboard.S.IsPressed()) { movement.Add(0, 0, -1); }
    if (keyboard.D.IsPressed()) { movement.Add(1, 0, 0); }
    if (keyboard.SpaceBar.IsPressed())
    {
        camera.Velocity.Set(0.0f, 6.0f, .0f);

        movement.Add(0, 1, 0);
    }

    

    double mouseX = 0;
    double mouseY = 0;

    // Add joystik
    {
        BF::ControllerData controllerData{ 0 };
        bool successful = BF::ControllerSystem::ControllerDataGet(0, controllerData);

        if (successful)
        {
            const int max = 32767;
            int viewXi = (int)controllerData.Axis[0] - max;
            int viewYi = (int)controllerData.Axis[1] - max;
            int posXi = (int)controllerData.Axis[2] - max;
            int posYi = (int)controllerData.Axis[3] - max;

            if (posXi != 0 || posYi != 0)
            {
                double xf = -posXi / 32768.0;
                double yf = -posYi / 32768.0;

                mouseX += xf;
                mouseY += yf;
            }

            if (viewXi != 0 || viewYi != 0)
            {
                double xf = viewXi / 32768.0;
                double yf = -viewYi / 32768.0;

                movement.Add(xf, 0, yf);
            }
        }       
    }

    camera.Move(movement);

    mouseX += mouse.InputAxis[0];
    mouseY += mouse.InputAxis[1];

    camera.Rotate(mouseX, mouseY);
    camera.Update(_deltaTime);
#endif
  
    keyboard.IncrementButtonTick();
    mouse.ResetAxis();
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

    const unsigned int format = ToImageFormat(image.Format);
    const unsigned int textureType = ToImageType(texture.Type);

    if (!image.PixelData)
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

    glBindTexture(textureType, 0);
}

void BF::BitFireEngine::Register(TextureCube& textureCube)
{
    unsigned int textureID = -1;

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

    for (unsigned int i = 0; i < 6; i++)
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
    size_t bufferIndexCounter = 0;
    size_t numberOfMeshes = model.MeshListSize;
    unsigned int vaoIDList[128u];
    memset(vaoIDList, -1, 128u * sizeof(unsigned int));

    glGenVertexArrays(numberOfMeshes, vaoIDList); // Generate VAOs  

    //printf("[OpenGL] Register Mesh <%ls> from <%ls>. Sub-Meshes <%zu>\n", model.Name, model.FilePath, model.MeshListSize);

    for (size_t meshIndex = 0; meshIndex < numberOfMeshes; meshIndex++)
    {
        const Mesh& mesh = model.MeshList[meshIndex];
        const unsigned int amountOfBuffers = mesh.SegmentListSize + 1; // +1 for VertexData

        const MeshSegment& meshSegment = mesh.SegmentList[meshIndex];

        unsigned int bufferIDList[128u];
        memset(bufferIDList, -1, 128u * sizeof(unsigned int));

        glGenBuffers(amountOfBuffers, bufferIDList); // Create Buffers

        unsigned int vao = vaoIDList[meshIndex];
        unsigned int vbo = bufferIDList[bufferIndexCounter++];
        unsigned int ibo = bufferIDList[bufferIndexCounter++];

        renderable.VAO = vao;
        renderable.VBO = vbo;
        renderable.IBO = ibo;

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo); // Select Buffer
        glBufferData(GL_ARRAY_BUFFER, mesh.VertexDataListSize * sizeof(float), mesh.VertexDataList, GL_STATIC_DRAW);

        OpenGL::VertexAttributeArrayDefine(sizeof(float), mesh.VertexDataStructureListSize, mesh.VertexDataStructureList);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshSegment.IndexDataListSize * sizeof(unsigned int), meshSegment.IndexDataList, GL_STATIC_DRAW);
    }

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void BF::BitFireEngine::Register(Renderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize)
{
    unsigned int id[3] = { -1,-1,-1 };

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

    renderable.VAO = id[0];
    renderable.VBO = id[1];
    renderable.IBO = id[2];
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

    renderable.TextureID = textureCube.ID;
}

bool BF::BitFireEngine::Register(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath)
{
    Shader vertexShader(ShaderType::Vertex);
    Shader fragmentShader(ShaderType::Fragment);

    {
        const bool isAlreadyLoaded = shaderProgram.ID != -1;
        const bool hasEmptyPaths = !vertexShaderFilePath || !fragmentShaderFilePath;

        if (isAlreadyLoaded)
        {
            return false;
        }

        if (hasEmptyPaths)
        {
            return false;
        }
    }

    //-----   
    {
        const FileActionResult vertexLoadResult = vertexShader.Load(vertexShaderFilePath);

        if (vertexLoadResult != FileActionResult::Successful)
        {
            return false;
        }
    }

    {
        const FileActionResult fragmentLoadResult = fragmentShader.Load(fragmentShaderFilePath);

        if (fragmentLoadResult != FileActionResult::Successful)
        {
            return false;
        }
    }
    //-----

    const unsigned int shaderProgrammID = glCreateProgram();
    const size_t shaderListSize = 2;
    const Shader* shaderList[shaderListSize]{ &vertexShader, &fragmentShader };
    unsigned int shaderIDList[shaderListSize] = { -1,-1 };
    unsigned int sucessfulCounter = 0;
    bool isValidShader = false;

    for (size_t i = 0; i < shaderListSize; ++i)
    {
        const Shader& shader = *shaderList[i];
        const unsigned int type = ToShaderType(shader.Type);
        const unsigned int shaderID = OpenGL::ShaderCompile(type, shader.Content);
        const bool compileFailed = shaderID == -1;

        if (compileFailed)
        {
            isValidShader = false;
            break;
        }

        shaderIDList[i] = shaderID;

        isValidShader = true;

        glAttachShader(shaderProgrammID, shaderID);
    }

    if (isValidShader)
    {
        glLinkProgram(shaderProgrammID);
        glValidateProgram(shaderProgrammID);

        shaderProgram.ID = shaderProgrammID;
    }

    // We used the Shaders above to compile, these elements are not used anymore.
    for (size_t i = 0; i < shaderListSize; i++)
    {
        const unsigned int shaderID = shaderIDList[i];
        const bool isLoaded = shaderID != -1;

        if (isLoaded)
        {
            glDeleteShader(shaderID);
        }
    }

    if (!isValidShader)
    {
        glDeleteProgram(shaderProgrammID);
    }

    return isValidShader;
}

void BF::BitFireEngine::Register(AudioSource& audioSource)
{
    /* REWORK THIS
    const unsigned int numberOfBuffers = 1u;
    unsigned int& sourceID = audioSource.ID;

    alGenSources(numberOfBuffers, &audioSource.ID);
    // check for errors    

    Update(audioSource);

    */
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
    const bool isValidTexture = textureID != -1;

#if 1 // Ignore
    if (!isValidTexture)
    {
        return;
    }
#else
    assert(isValidTexture);
#endif

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture

    const unsigned int imageTypeID = ToImageType(imageType);

    glBindTexture(imageTypeID, textureID);
}

void BF::BitFireEngine::Use(Renderable& renderable)
{
    // TODO
}

void BF::BitFireEngine::Use(SkyBox& skyBox)
{
    OpenGL::VertexArrayBind(skyBox.RenderInfo.VAO);

    int skyBoxTextureLocation = OpenGL::ShaderGetUniformLocationID(skyBox.Shader.ID, "SkyBoxTexture");


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

ThreadFunctionReturnType BF::BitFireEngine::LoadResourceAsync(void* resourceAdress)
{
    /*
    ResourceAsyncLoadInfo* resourceAsyncLoadInfo = (ResourceAsyncLoadInfo*)resourceAdress;
    Resource* resource = resourceAsyncLoadInfo->ResourceAdress;
    const wchar_t* filePath = resourceAsyncLoadInfo->FilePath;
    const FileActionResult loadResult = resource->Load(filePath);

    printf("[#][Resource][ASYNC] Loaded <%ls> ... [%i]\n", filePath, loadResult);
    */
    return 0;
}

BF::FileActionResult BF::BitFireEngine::Load(Renderable& renderable, const wchar_t* filePath, bool loadAsynchronously)
{
    _modelAdd.Lock();
    _renderList.Add(&renderable);
    _modelAdd.Release();

    if (loadAsynchronously)
    {
        // ResourceAsyncLoadInfo* resourceAsyncLoadInfo = new ResourceAsyncLoadInfo();

        // Thread::Run(LoadResourceAsync, &model);
    }
    else
    {
        Model model;

        const FileActionResult fileActionResult = model.Load(filePath);
        const bool successful = fileActionResult == FileActionResult::Successful;

        if (successful)
        {
            Register(renderable, model);
        }
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BitFireEngine::Load(Renderable& renderable, const float* vertexData, const size_t vertexDataSize, const unsigned int* indexList, const size_t indexListSize)
{
    Register(renderable, vertexData, vertexDataSize, indexList, indexListSize);

    _modelAdd.Lock();
    _renderList.Add(&renderable);
    _modelAdd.Release();

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BitFireEngine::Load(Texture& texture, const wchar_t* filePath, bool loadAsynchronously)
{
    Image& image = texture.DataImage;

    _imageAdd.Lock();
    _textureList.Add(&texture);
    _imageAdd.Release();

    texture.Type = ImageType::Texture2D;

    if (loadAsynchronously)
    {
        Thread::Run(LoadResourceAsync, &image);

        return FileActionResult::Successful;
    }
    else
    {
        const FileActionResult imageLoadResult = image.Load(filePath);
        const bool isSucessful = imageLoadResult == FileActionResult::Successful;

        if (isSucessful)
        {
            Register(texture);
        }

        return imageLoadResult;
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BitFireEngine::Load(Font& font, const wchar_t* filePath, bool loadAsynchronously)
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

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BitFireEngine::Load(AudioClip& audioClip, const wchar_t* filePath, bool loadAsynchronously)
{
    Sound* soundAdress = new Sound();

    if (!soundAdress)
    {
        return FileActionResult::OutOfMemory;
    }

    Sound& sound = *soundAdress;

    if (loadAsynchronously)
    {

    }
    else
    {
        const FileActionResult soundLoadResult = sound.Load(filePath);

        if (soundLoadResult != FileActionResult::Successful)
        {
            delete soundAdress;

            return soundLoadResult;
        }

        Register(audioClip, sound);
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BitFireEngine::Load(ShaderProgram& shaderProgram, const wchar_t* vertexShaderFilePath, const wchar_t* fragmentShaderFilePath)
{
    const bool firstShaderProgram = _shaderProgramList.Size() == 0;
    const bool isRegistered = shaderProgram.ID != -1;

    if (!isRegistered)
    {
        _shaderProgramList.Add(&shaderProgram);

        const bool successful = Register(shaderProgram, vertexShaderFilePath, fragmentShaderFilePath);

        if (firstShaderProgram && successful)
        {
            _defaultShaderID = shaderProgram.ID;

            CameraDataGet(_defaultShaderID);
        }
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BitFireEngine::Load(Sprite& sprite, const wchar_t* filePath)
{
    Renderable& renderable = sprite;
    Texture* texture = sprite.UsedTexture = new Texture;

    const FileActionResult textureLoadResult = Load(*texture, filePath, false);
    const bool sucessful = textureLoadResult == FileActionResult::Successful;

    if (sucessful)
    {
        const Texture& loadedTexture = *texture;
        const float scaling = 0.01;
        const size_t width = loadedTexture.DataImage.Width * scaling;
        const size_t height = loadedTexture.DataImage.Height * scaling;

        renderable.TextureID = loadedTexture.ID;
        renderable.Scale(width, height, 1.0f);
    }

    _modelAdd.Lock();
    _renderList.Add(&renderable);
    _modelAdd.Release();

    // Add(collider);
    // model.BoundingBoxUpdate();

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BitFireEngine::Load(Collider* collider)
{
    _physicList.Add(collider);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::BitFireEngine::Load
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
    ShaderProgram& shaderProgram = skyBox.Shader;

    Load(shaderProgram, shaderVertex, shaderFragment);

    skyBox.RenderInfo.ShaderID = shaderProgram.ID;

    Image* imageList = skyBox.Texture.ImageList;

    const FileActionResult textureRightResult = imageList[0].Load(textureRight);
    const FileActionResult textureLeftResult = imageList[1].Load(textureLeft);
    const FileActionResult textureTopResult = imageList[2].Load(textureTop);
    const FileActionResult textureBottomResult = imageList[3].Load(textureBottom);
    const FileActionResult textureBackResult = imageList[4].Load(textureBack);
    const FileActionResult textureFrontResult = imageList[5].Load(textureFront);

    Register(skyBox);

    DefaultSkyBox = &skyBox;

    return FileActionResult::Successful;
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

void BF::BitFireEngine::ModelsRender(float deltaTime)
{
    MainCamera.Update(deltaTime);

    // Render Skybox first, if it is used
    {
        bool hasSkyBox = DefaultSkyBox != nullptr;

        OpenGL::RenderBothSides(true);

        if (hasSkyBox)
        {
            const SkyBox& skyBox = *DefaultSkyBox;
            const Renderable& renderable = skyBox.RenderInfo;
            const unsigned int shaderID = skyBox.Shader.ID;
            Matrix4x4<float> viewTri(MainCamera.MatrixView);

            viewTri.ResetForthAxis();

            OpenGL::DepthMaskEnable(false);
            OpenGL::DrawOrder(true);

            OpenGL::UseShaderProgram(shaderID);
            _lastUsedShaderProgram = shaderID;

            CameraDataGet(shaderID);
            CameraDataUpdate(MainCamera);

            OpenGL::ShaderSetUniformMatrix4x4(_matrixViewID, viewTri.MatrixData);
            //OpenGL::Use(*DefaultSkyBox);          
            OpenGL::VertexArrayBind(renderable.VAO);
            OpenGL::VertexBufferBind(renderable.VBO, renderable.IBO);
            Use(ImageType::TextureCubeContainer, renderable.TextureID);

            glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);

            Use(ImageType::TextureCubeContainer, 0);
            OpenGL::DepthMaskEnable(true);
            OpenGL::DrawOrder(false);
        }
    }

    for (LinkedListNode<Renderable*>* currentModel = _renderList.GetFirst(); currentModel; currentModel = currentModel->Next)
    {
        const Renderable* renderableAdress = currentModel->Element;

        if (!renderableAdress)
        {
            continue;
        }

        const Renderable& renderable = *renderableAdress;
        const bool hasShader = renderable.ShaderID != -1;
        const bool hasMesh = renderable.VAO != -1;
        const unsigned int shaderID = hasShader ? renderable.ShaderID : _defaultShaderID;

        // Model* parentModel = nullptr;
         //bool isSharedModel = model->SharedModel != nullptr;
        bool skipRendering = !renderable.ShouldItBeRendered || !shaderID || !hasMesh;

        if (skipRendering)
        {
            continue; // Skip to next model.
        }

        //---<TEST>------------------------------------------------
        OpenGL::UseShaderProgram(shaderID);
        CameraDataGet(shaderID);
        CameraDataUpdate(MainCamera);
        OpenGL::ShaderSetUniformMatrix4x4(_matrixModelID, renderable.MatrixData);
        OpenGL::VertexArrayBind(renderable.VAO);
        OpenGL::VertexBufferBind(renderable.VBO, renderable.IBO);
        Use(ImageType::Texture2D, renderable.TextureID);

        {
            const unsigned int renderModeID = ToRenderMode(renderable.Mode);

            glPointSize(10);
            glLineWidth(5);

            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_POINTS, 24, GL_UNSIGNED_INT, 0);
            glDrawElements(renderModeID, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(renderModeID, 0, 24);

            /*
            bool wireFrame = true;
            if (wireFrame)
            {
                glPolygonMode(GL_FRONT, GL_LINE);
                glPolygonMode(GL_BACK, GL_LINE);

                glDrawArrays(GL_POLYGON, startIndex, amount);

                glPolygonMode(GL_FRONT, GL_FILL);
                glPolygonMode(GL_BACK, GL_FILL);
            }
            */
        }


        Use(ImageType::Texture2D, 0);
        //-----------------------------------------------------------

        /*

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
            unsigned int materialIndex = parentModel ? parentModel->SharedRenderInfoOverride.MaterialID : mesh.RenderInfo.MaterialID;
            unsigned int textureID = -1;

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

    for (LinkedListNode<Collider*>* colliderCurrent = _physicList.GetFirst(); colliderCurrent; colliderCurrent = colliderCurrent->Next)
    {
        Collider* collider = colliderCurrent->Element;
        Vector3<float> color(1.0f, 1.0f, 1.0f);
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

void BF::BitFireEngine::BoundingBoxRender(Matrix4x4<float> modelMatrix, Vector3<float> boundingBox, Vector3<float> color)
{
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


        /*
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
    switch (renderMode)
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

BF::ShaderType BF::BitFireEngine::ToShaderType(unsigned int token)
{
    return ShaderType();
}

unsigned int BF::BitFireEngine::ToShaderType(ShaderType shaderType)
{
    switch (shaderType)
    {
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;

        case   ShaderType::TessellationControl:
            return -1; // ???

        case   ShaderType::TessellationEvaluation:
            return -1; // ???

        case   ShaderType::Geometry:
            return GL_GEOMETRY_SHADER;

        case   ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;

        case  ShaderType::Compute:
            return GL_COMPUTE_SHADER;

        case ShaderType::Unkown:
        default:
            return -1;
    }
}

BF::ImageDataFormat BF::BitFireEngine::ToImageFormat(unsigned int token)
{
    return ImageDataFormat();
}

unsigned int BF::BitFireEngine::ToImageFormat(ImageDataFormat imageFormat)
{
    switch (imageFormat)
    {
        case ImageDataFormat::BGR:
            return GL_BGR;

        case ImageDataFormat::BGRA:
            return GL_BGRA;

        case ImageDataFormat::RGB:
            return GL_RGB;

        case ImageDataFormat::RGBA:
            return GL_RGBA;

        case ImageDataFormat::AlphaMask:
        default:
            return -1;
    }
}

BF::ImageType BF::BitFireEngine::ToImageType(unsigned int token)
{
    switch (token)
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
            return ImageType::TextureUnkown;
    }
}

unsigned int BF::BitFireEngine::ToImageType(ImageType imageType)
{
    switch (imageType)
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
    switch (imageWrap)
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
    switch (layout)
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

    switch (bitsPerSample)
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
    switch (type)
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


void BF::SystemSound::LoopPart(AudioSource& audioSource, unsigned int startIndex, unsigned int endIndex)
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
    unsigned int shaderID = ShaderHitBox.ID;

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