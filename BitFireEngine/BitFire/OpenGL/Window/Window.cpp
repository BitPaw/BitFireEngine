#include "Window.h"
#include "../../Mathematic/Interpolate.h"
#include "../../Resources/Image/PixelArray/PixelArrayLoader.h"

Window* Window::_instance;

void Window::UpdateInput()
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

Window* Window::GetInstance()
{
    return _instance;
}

Window::Window(Player* player)
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

Window::~Window()
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
    Window* currentWindow = Window::GetInstance();
    KeyBoard* keyBoard = &currentWindow->CurrentPlayer->Input.KeyBoardInput;

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
    Window* currentWindow = Window::GetInstance();
    Mouse* mouse = &currentWindow->CurrentPlayer->Input.MouseInput;

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
    Window* currentWindow = Window::GetInstance();
    Mouse* mouse = &currentWindow->CurrentPlayer->Input.MouseInput;

    if (mouse->ShoudRegisterInput())
    {
        mouse->InputAxis.X = mouse->Position.X - xpos;
        mouse->InputAxis.Y = mouse->Position.Y - ypos;

        // Clamp
        mouse->InputAxis.X = Interpolate::Liniar(-1, 1, -15, 15, mouse->InputAxis.X);
        mouse->InputAxis.Y = Interpolate::Liniar(-1, 1, -15, 15, mouse->InputAxis.Y);

        mouse->Position.X = xpos;
        mouse->Position.Y = ypos;
    }
}

void OnWindowSizeChanged(GLFWwindow* window, int _width, int _height)
{
    Window* currentWindow = Window::GetInstance();    

    currentWindow->ResizeWindow(_width, _height);
}

void Window::ResizeWindow(const int width, const int height)
{
    float* cwidth = &CurrentPlayer->Camera.Settings->Width;
    float* cheight = &CurrentPlayer->Camera.Settings->Height;

    bool hasChanged = *cwidth != width || *cheight != height;

    if (hasChanged)
    {
        *cwidth = width;
        *cheight = height;

        glViewport(0, 0, width, height);

        //glfwSetWindowSize(_window, width, height);
    }
}

void Window::SetCursorTexture(std::string filePath)
{
    /*
    BitMap bitMap = BitMapLoader::LoadFromFile(filePath);
    PixelArray pixelArray = BitMapLoader::GeneratePixelArray(bitMap);

    GLFWimage image;
    image.width = bitMap.InformationHeader->Width;
    image.height = bitMap.InformationHeader->Height;
    image.pixels = pixelArray.PixelData;

    _cursor = glfwCreateCursor(&image, 0, 0);

    // GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
    glfwSetCursor(_window, _cursor);*/
}

void Window::SetCursorMode(CursorMode mode)
{
    /*
    GLFW_CURSOR_NORMAL
    GLFW_CURSOR_HIDDEN
    GLFW_CURSOR_DISABLED
    */
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

void Window::SetVideoRefreshRate(RefreshRateMode mode)
{
    switch (mode)
    {
    case RefreshRateMode::Unlimited:
        glfwSwapInterval(0);
        break;

    case RefreshRateMode::VSync:
        glfwSwapInterval(1);
        break;

    case RefreshRateMode::CustomSync:
        glfwSwapInterval(2);
        break;

    }
}

void Window::SetWindowPosition(unsigned int x, unsigned int y)
{
    glfwSetWindowPos(_window, x, y);
}

void Window::SetWindowPositionToCenter()
{
    VideoConfig* videoConfig = &CurrentPlayer->Config.Video;
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());  
    int x = mode->width / 2;
    int y = mode->height / 2;

    x -= videoConfig->ScreenResolution.Width / 2;
    y -= videoConfig->ScreenResolution.Height / 2;

    SetWindowPosition(x, y);
}

PixelArray Window::TakeScreenShot()
{
    VideoConfig* videoConfig = &CurrentPlayer->Config.Video;   
    int width = videoConfig->ScreenResolution.Width;
    int height = videoConfig->ScreenResolution.Height;
    PixelArray pixelArray;

    pixelArray.Size = width * height * 3;
    pixelArray.PixelData = new unsigned char[pixelArray.Size];

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelArray.PixelData);

    return pixelArray;
}

bool Window::ShouldExit()
{
    return _exitWindow;
}

bool Window::Create()
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

        _window = glfwCreateWindow(width, height, title, _montor, NULL);

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

    SetWindowPositionToCenter();
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

void Window::Update()
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


     /*
     //model = glm::rotate(model, 0.002f, glm::vec3(0, 1, 0));      

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::scale(model, glm::vec3(1,1.2,0));

    modelView = _camera._view * model;
    invModelView = glm::transpose(glm::inverse(modelView));

    std::string text = "Who_is_sample_text?";

    for (size_t i = 0; i < text.size(); i++)
    {
        Mesh* mesh = &_renderModel.VertexMeshList.at(0);        
        BitMapFontCharacter bitMapFontCharacter = font.GetCharacterPosition(text.at(i));
                
        float p00 = bitMapFontCharacter.StartPosition.X;
        float p10 = bitMapFontCharacter.StartPosition.X + bitMapFontCharacter.Size.X;
        float p01 = bitMapFontCharacter.StartPosition.Y;
        float p11 = bitMapFontCharacter.StartPosition.Y + bitMapFontCharacter.Size.Y;

        if (true)
        {
            p00 = Interpolate::Liniar(0, 1, 0, 512, p00);
            p10 = Interpolate::Liniar(0, 1, 0, 512, p10);
            p01 = Interpolate::Liniar(0, 1, 0, 512, p01);
            p11 = Interpolate::Liniar(0, 1, 0, 512, p11);
        }

        Rectangle rectangle = Rectangle(Point(p00, p10), Point(), Point(), Point());

       // printf("\n\n%c => %.2f | %.2f | %.2f | %.2f \n", bitMapFontCharacter.ID, p00, p10, p01, p11);
                
       // mesh->Vertices.at(0).CurrentPosition = Position(p00,0, 0);
       // mesh->Vertices.at(1).CurrentPosition = Position(p10,0,0);
       // mesh->Vertices.at(2).CurrentPosition = Position(p10,0,0);
        //mesh->Vertices.at(3).CurrentPosition = Position(p00,0, 0);

       // mesh->Vertices.at(1).Color = RGBA(1,0,0);
        mesh->Vertices.at(0).TexturePoint = Point(p00, p01); // RightUpper 00
        mesh->Vertices.at(1).TexturePoint = Point(p10, p01); // Left upper 10

       // mesh->Vertices.at(3).Color = RGBA(0, 1, 0);
        mesh->Vertices.at(2).TexturePoint = Point(p10, p11); // Left Under 11 
        mesh->Vertices.at(3).TexturePoint = Point(p00, p11); //Right under 01
           
        mesh->GenerateArrayData();
        
        buffer.ChangeMesh(mesh);
        buffer.BindBuffer();
        

        unsigned int indsize = mesh->GetIndiceData()->Lengh;

        //buffer.ChangeMesh(mesh);

        int off = 6;
        int xOFF = 0;
        int yOFF = 0;


       // glfwGetWindowPos(_window, &xOFF, &yOFF);

        x += 0.01f;

        xOFF += sin(x) * 100 * TimeCollection::DeltaTime;
        //yOFF += cos(i) * TimeCollection::DeltaTime;

       // glfwSetWindowPos(_window, xOFF, yOFF);

        */