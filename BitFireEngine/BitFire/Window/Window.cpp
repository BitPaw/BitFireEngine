#include "Window.h"


KeyBoard* Window::KeyBoardInput;
Mouse* Window::MouseInput;

std::chrono::steady_clock::time_point Window::_lastTimeStamp;

std::chrono::steady_clock::time_point Window::GetCurrentTimeStamp()
{
    return std::chrono::high_resolution_clock::now();
}

void Window::UpdateDeltaTime()
{
    _lastTimeStamp = GetCurrentTimeStamp();
}

float Window::GetDeltaTime()
{
    auto currentTimeStamp = GetCurrentTimeStamp();
    std::chrono::duration<double> elapsed = currentTimeStamp - _lastTimeStamp;

    float deltaTime = elapsed.count();

    //printf("DT %f\n", deltaTime);

    return deltaTime;
}

float Window::GetRunnedTime()
{
    return glfwGetTime();
}

Window::Window()
{
    Exit = false;

    KeyBoardInput = new KeyBoard();
    MouseInput = new Mouse();

    glfwSetTime(0);
}

Window::Window(const int width, const int height, const char* title) : Window()
{
    Create(width, height, title);
}

Window::~Window()
{  
    float cx = GetRunnedTime();

    if (cx >= 60)
    {
        printf("Window was active for : %.2fm\n", cx / 60.0f);
    }
    else
    {
        printf("Window was active for : %.2fs\n", cx);
    }

    glfwTerminate();

    delete KeyBoardInput;
    delete MouseInput;
}

void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    KeyBoard* keyBoard = Window::KeyBoardInput;

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
    Mouse* mouse = Window::MouseInput;

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

    switch(button)
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

static void OnMousePosition(GLFWwindow* window, double xpos, double ypos)
{
    Mouse* mouse = Window::MouseInput;

    mouse->InputAxis.X = mouse->Position.X - xpos;
    mouse->InputAxis.Y = mouse->Position.Y - ypos;

    // Clamp
    mouse->InputAxis.X = Interpolate::Liniar(-1, 1, -15, 15, mouse->InputAxis.X);
    mouse->InputAxis.Y = Interpolate::Liniar(-1, 1, -15, 15, mouse->InputAxis.Y);

    mouse->Position.X = xpos;
    mouse->Position.Y = ypos;
}

bool Window::Create(const int width, const int height, const char* title)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        return false;
    }

    /* Create a windowed mode window and its OpenGL context */
    {
        _window = glfwCreateWindow(width, height, title, NULL, NULL);
    }

    if (!_window)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
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
    }

    /*
    GLFW_CURSOR_NORMAL
    GLFW_CURSOR_HIDDEN
    GLFW_CURSOR_DISABLED
    */

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Do not load a cursor
    if(false)
    {
        // Hardcoded. There is not texture, this cant work now.
        Texture* text = TextureLoader::LoadTexture("Cursor.hex");
        
        unsigned char height = 166 / 2;
        unsigned char width = 160 / 2;
        unsigned char* icon = new  unsigned char[height * width * 4]
        {
            0xFF, 0x00, 0x00, 0xFF,
                0x00, 0x00, 0xFF, 0xFF,
                0x00, 0x00, 0xFF, 0xFF,
                0xFF, 0x00, 0x00, 0xFF

        };



        GLFWimage image;
        image.width = width;
        image.height = height;
        image.pixels = text->Data;

        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);


         // GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
        glfwSetCursor(_window, cursor);
    }


    if (true)
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


    glfwSwapInterval(1);
}

void Window::Update()
{
    Exit = glfwWindowShouldClose(_window);
    UpdateDeltaTime();

    // Input Reset
    //Window::KeyBoardInput->Reset();
    MouseInput->InputAxis.X = 0;
    MouseInput->InputAxis.Y = 0;

    glClear(GL_DEPTH_BUFFER_BIT);
    /* Render here */
    //glClear(GL_COLOR_BUFFER_BIT);

    /*
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.0f,  0.5f);
    glVertex2f( 0.5f, -0.5f);
    glEnd();
    */

   // glDrawArrays(GL_TRIANGLES, 0, 3); // Draw all
    
    //glDrawElements(GL_TRIANGLES, 1, NULL); Draw Spacific 

   //glDrawElements(GL_TRIANGLES, 8631, GL_UNSIGNED_INT, nullptr);

    /* Swap front and back buffers */
    glfwSwapBuffers(_window);

    /* Poll for and process events */
    glfwPollEvents();
}
