#include "Window.h"

BF::Window* BF::Window::_instance;

void BF::Window::UpdateInput()
{
    KeyBoard* keyboard = &CurrentPlayer->Input.KeyBoardInput;
    Mouse* mouse = &CurrentPlayer->Input.MouseInput;
    FirstPersonCamera* camera = &CurrentPlayer->Camera;

    if (keyboard->Letter.W)
    {
        camera->Move(Direcion::Forward);
    }

    if (keyboard->Letter.A)
    {
        camera->Move(Direcion::Left);
    }

    if (keyboard->Letter.S)
    {
        camera->Move(Direcion::Backward);
    }

    if (keyboard->Letter.D)
    {
        camera->Move(Direcion::Right);
    }

    if (keyboard->SpaceBar)
    {
        camera->Move(Direcion::Up);
    }

    if (keyboard->FunktionKey.ShitftLeft)
    {
        camera->Move(Direcion::Down);
    }

    if (keyboard->Letter.R)
    {
        bool axisEnabled = mouse->ShoudRegisterInput();
            
        if (axisEnabled)
        {
            SetCursorMode(CursorMode::Ignore);
        }
        else
        {
            SetCursorMode(CursorMode::Locked);        
        }
    }

    if (keyboard->Letter.K)
    {
       // PixelArray px = TakeScreenShot();
      //  PixelArrayLoader::SaveToFile("C:/_WorkSpace/C++/image.hex",px);
    }

    /*
    if (window->KeyBoardInput->Letter.F)
    {
        camera->Settings->Mode = camera->Settings->Mode == CameraMode::Perspectdive ? CameraMode::Orthographic : CameraMode::Perspectdive;
    }*/

    camera->Rotate(mouse->InputAxis.X, mouse->InputAxis.Y);

    camera->Update();

    mouse->ResetAxis();
}

BF::Window* BF::Window::GetInstance()
{
    return _instance;
}

BF::Window::Window(Player* player)
{
    CurrentPlayer = player;

    bool successful = Create();

    _instance = this;
    _exitWindow = false;

    if (!successful)
    {
        printf("Error loading window\n");
    }
}

BF::Window::~Window()
{
    float cx = TimeCollection::ActiveTime;

    if (cx >= 60)
    {
        printf("Window was active for : %.2fm\n", cx / 60.0f);
    }
    else
    {
        printf("Window was active for : %.2fs\n", cx);
    }

    glfwTerminate();
}

void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    BF::Window* currentWindow = BF::Window::GetInstance();
    BF::KeyBoard* keyBoard = &currentWindow->CurrentPlayer->Input.KeyBoardInput;

    /* [key]
        The key will be GLFW_KEY_UNKNOWN
    */

    /* [action]
    0 = GLFW_RELEASE
    1 = GLFW_PRESS
    2 = GLFW_REPEAT
    */

    /* [mods]
    GLFW_STICKY_KEYS "Caps"
    GLFW_LOCK_KEY_MODS "NumPad"
    */

    switch (key)
    {
    case GLFW_KEY_A: keyBoard->Letter.A = action; break;
    case GLFW_KEY_B: keyBoard->Letter.B = action; break;
    case GLFW_KEY_C: keyBoard->Letter.C = action; break;
    case GLFW_KEY_D: keyBoard->Letter.D = action; break;
    case GLFW_KEY_E: keyBoard->Letter.E = action; break;
    case GLFW_KEY_F: keyBoard->Letter.F = action; break;
    case GLFW_KEY_G: keyBoard->Letter.G = action; break;
    case GLFW_KEY_H: keyBoard->Letter.H = action; break;
    case GLFW_KEY_I: keyBoard->Letter.I = action; break;
    case GLFW_KEY_J: keyBoard->Letter.J = action; break;
    case GLFW_KEY_K: keyBoard->Letter.K = action; break;
    case GLFW_KEY_L: keyBoard->Letter.L = action; break;
    case GLFW_KEY_M: keyBoard->Letter.M = action; break;
    case GLFW_KEY_N: keyBoard->Letter.N = action; break;
    case GLFW_KEY_O: keyBoard->Letter.O = action; break;
    case GLFW_KEY_P: keyBoard->Letter.P = action; break;
    case GLFW_KEY_Q: keyBoard->Letter.Q = action; break;
    case GLFW_KEY_R: keyBoard->Letter.R = action; break;
    case GLFW_KEY_S: keyBoard->Letter.S = action; break;
    case GLFW_KEY_T: keyBoard->Letter.T = action; break;
    case GLFW_KEY_U: keyBoard->Letter.U = action; break;
    case GLFW_KEY_V: keyBoard->Letter.V = action; break;
    case GLFW_KEY_W: keyBoard->Letter.W = action; break;
    case GLFW_KEY_X: keyBoard->Letter.X = action; break;
    case GLFW_KEY_Y: keyBoard->Letter.Y = action; break;
    case GLFW_KEY_Z: keyBoard->Letter.Z = action; break;


        // Fuction Keys
    case GLFW_KEY_LEFT_SHIFT: keyBoard->FunktionKey.ShitftLeft = action; break;
    case GLFW_KEY_SPACE: keyBoard->SpaceBar = action; break;

    }
}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    BF::Window* currentWindow = BF::Window::GetInstance();
    BF::Mouse* mouse = &currentWindow->CurrentPlayer->Input.MouseInput;

    /*
    0 = GLFW_MOUSE_BUTTON_1 | GLFW_MOUSE_BUTTON_LEFT
    1 = GLFW_MOUSE_BUTTON_2 | GLFW_MOUSE_BUTTON_RIGHT
    2 = GLFW_MOUSE_BUTTON_3 | GLFW_MOUSE_BUTTON_MIDDLE
    3 = GLFW_MOUSE_BUTTON_4
    4 = GLFW_MOUSE_BUTTON_5
    5 = GLFW_MOUSE_BUTTON_6
    6 = GLFW_MOUSE_BUTTON_7
    7 = GLFW_MOUSE_BUTTON_8 | GLFW_MOUSE_BUTTON_LAST
    */

    switch (button)
    {
    case GLFW_MOUSE_BUTTON_1:
        mouse->LeftButton = action;
        break;

    case GLFW_MOUSE_BUTTON_2:
        mouse->RightButton = action;
        break;

    case GLFW_MOUSE_BUTTON_3:
        mouse->ScrollButton = action;
        break;

    case GLFW_MOUSE_BUTTON_4:
        mouse->CustomButton1 = action;
        break;

    case GLFW_MOUSE_BUTTON_5:
        mouse->CustomButton2 = action;
        break;

    case GLFW_MOUSE_BUTTON_6:
        mouse->CustomButton3 = action;
        break;

    case GLFW_MOUSE_BUTTON_7:
        mouse->CustomButton4 = action;
        break;

    case GLFW_MOUSE_BUTTON_8:
        mouse->CustomButton5 = action;
        break;
    }
}

void OnMousePosition(GLFWwindow* window, double xpos, double ypos)
{
    BF::Window* currentWindow = BF::Window::GetInstance();
    BF::Mouse* mouse = &currentWindow->CurrentPlayer->Input.MouseInput;

    if (mouse->ShoudRegisterInput())
    {
        mouse->InputAxis.X = mouse->Position.X - xpos;
        mouse->InputAxis.Y = mouse->Position.Y - ypos;

        // Clamp
        mouse->InputAxis.X = BF::Interpolate::Liniar(-1, 1, -15, 15, mouse->InputAxis.X);
        mouse->InputAxis.Y = BF::Interpolate::Liniar(-1, 1, -15, 15, mouse->InputAxis.Y);

        mouse->Position.X = xpos;
        mouse->Position.Y = ypos;
    }
}

void OnWindowSizeChanged(GLFWwindow* window, int _width, int _height)
{
    BF::Window* currentWindow = BF::Window::GetInstance();

    currentWindow->Resize(_width, _height);
}

void BF::Window::Resize(const unsigned int width, const unsigned int height)
{
    unsigned int cwidth = CurrentPlayer->Camera.Settings->Width;
    unsigned int cheight = CurrentPlayer->Camera.Settings->Height;

    bool hasChanged = cwidth != width || cheight != height;
     
    if (hasChanged)
    {
        cwidth = (width / 2);
        cheight = (height / 2);

       // *cwidth = width;
       // *cheight = height;

       // glViewport(0, 0, cwidth, cheight); <---- changed the acual size of the render window

       // glfwSetWindowSize(_window, width, height);
    }
}

void BF::Window::SetCursorTexture(Image* image)
{    
    GLFWimage flfwImage
    {
        image->Width,
        image->Height,
        &image->PixelData[0]
    };

    _cursor = glfwCreateCursor(&flfwImage, 0, 0);

    // GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
    glfwSetCursor(_window, _cursor);
    
}

void BF::Window::SetCursorMode(CursorMode mode)
{
    Mouse* mouse = &Window::CurrentPlayer->Input.MouseInput;

    mouse->Mode = mode;

    switch (mode)
    {
    case CursorMode::Show:
    case CursorMode::Ignore:
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);   
        break;

    case CursorMode::Invisible:
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        break;

    case CursorMode::Locked:
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        break;
    }  
}

void BF::Window::SetVideoRefreshRate(RefreshRateMode mode)
{
    int modeID = -1;

    switch (mode)
    {
    case RefreshRateMode::Unlimited:
        modeID = 0;
        break;

    case RefreshRateMode::VSync:
        modeID = 1;
        break;

    case RefreshRateMode::CustomSync:
        modeID = 2;
        break;
    }

    glfwSwapInterval(modeID);
}

void BF::Window::SetPosition(unsigned int x, unsigned int y)
{
    glfwSetWindowPos(_window, x, y);
}

void BF::Window::SetPositionToCenter()
{
    VideoConfig* videoConfig = &CurrentPlayer->Config.Video;
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());  
    int x = mode->width / 2;
    int y = mode->height / 2;

    x -= videoConfig->ScreenResolution.Width / 2;
    y -= videoConfig->ScreenResolution.Height / 2;

    SetPosition(x, y);
}

void BF::Window::SetTitle(std::string title)
{
    glfwSetWindowTitle(_window, title.c_str());
}

void BF::Window::SetIcon(Image* image)
{
    const unsigned int numberOfImages = 1;
    GLFWimage flfwImage 
    {
        image->Width, 
        image->Height, 
        &image->PixelData[0] 
    };

    glfwSetWindowIcon(_window, numberOfImages, &flfwImage);
}

BF::Image* BF::Window::TakeScreenShot()
{
    Image* image = new Image();
    VideoConfig* videoConfig = &CurrentPlayer->Config.Video;
    int width = videoConfig->ScreenResolution.Width;
    int height = videoConfig->ScreenResolution.Height;
    unsigned int size = width * height * 4;
   
    image->Width = width;
    image->Height = height;
    image->PixelData.ReSize(size);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &image->PixelData[0]);

    return image;
}

bool BF::Window::ShouldExit()
{
    return _exitWindow;
}

bool BF::Window::Create()
{
    VideoConfig* videoConfig = &CurrentPlayer->Config.Video;

    /* Initialize the library */
    if (!glfwInit())
    {
        return false;
    }

    /* Create a windowed mode window and its OpenGL context */
    {
        const char* title = "[BFE] <BitFireEngine>";
        int width = videoConfig->ScreenResolution.Width;
        int height = videoConfig->ScreenResolution.Height;

        _window = glfwCreateWindow(width, height, title, NULL, NULL);

        if (!_window)
        {
            glfwTerminate();
            return false;
        }
    }

    glfwMakeContextCurrent(_window);

    if (glewInit() != GLEW_OK)
    {
        return false;
    }

    // SetCallBacks
    {
        glfwSetKeyCallback(_window, OnKeyPressed);
        glfwSetMouseButtonCallback(_window, OnMouseButton);
        glfwSetCursorPosCallback(_window, OnMousePosition);
        glfwSetWindowSizeCallback(_window, OnWindowSizeChanged);    

       // SetCursorTexture("C:/_WorkSpace/C++/Data/Cursor.bmp");
        SetCursorMode(CursorMode::Locked);
    }

    SetPositionToCenter();
    SetVideoRefreshRate(RefreshRateMode::VSync);

    if (false)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    if (true)
    {
        glEnable(GL_DEPTH_TEST);
    }

    if (true)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    glfwSetTime(0);

    return true;
}

void BF::Window::Update()
{
    _exitWindow = glfwWindowShouldClose(_window);

    if (_exitWindow)
    {
        return;
    }

    UpdateInput();

    glfwSwapBuffers(_window);
    glfwPollEvents();

    TimeCollection::SetDeltaTimeStamp();
    TimeCollection::ActiveTime = glfwGetTime();
}