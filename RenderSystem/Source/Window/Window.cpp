#include "Window.h"
#include "../VideoConfig.h"
#include "../../../MathSystem/Source/Interpolate.h"
#include "../../Dependencies/include/GL/glew.h"
#include "../../Dependencies/include/GLFW/glfw3.h"
#include <stdio.h>

BF::Dictionary<GLFWwindow*, BF::InputContainer> BF::Window::WindowsInput;


BF::Window::Window()
{
    bool successful = Create();

    ShouldCloseWindow = false;

    if (!successful)
    {
        printf("Error loading window\n");
    }
}

BF::Window::~Window()
{
    glfwTerminate();
}

void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    BF::KeyBoard* keyBoard = &BF::Window::WindowsInput.GetValue(window)->KeyBoardInput;

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

    // Ignore calls that tell that a key is 'hold', because its shitty implemented. 
    if (action == GLFW_REPEAT)
    {
        return;
    }

    switch (key)
    {
        case GLFW_KEY_A: keyBoard->A.Value = action; break;
        case GLFW_KEY_B: keyBoard->B.Value = action; break;
        case GLFW_KEY_C: keyBoard->C.Value = action; break;
        case GLFW_KEY_D: keyBoard->D.Value = action; break;
        case GLFW_KEY_E: keyBoard->E.Value = action; break;
        case GLFW_KEY_F: keyBoard->F.Value = action; break;
        case GLFW_KEY_G: keyBoard->G.Value = action; break;
        case GLFW_KEY_H: keyBoard->H.Value = action; break;
        case GLFW_KEY_I: keyBoard->I.Value = action; break;
        case GLFW_KEY_J: keyBoard->J.Value = action; break;
        case GLFW_KEY_K: keyBoard->K.Value = action; break;
        case GLFW_KEY_L: keyBoard->L.Value = action; break;
        case GLFW_KEY_M: keyBoard->M.Value = action; break;
        case GLFW_KEY_N: keyBoard->N.Value = action; break;
        case GLFW_KEY_O: keyBoard->O.Value = action; break;
        case GLFW_KEY_P: keyBoard->P.Value = action; break;
        case GLFW_KEY_Q: keyBoard->Q.Value = action; break;
        case GLFW_KEY_R: keyBoard->R.Value = action; break;
        case GLFW_KEY_S: keyBoard->S.Value = action; break;
        case GLFW_KEY_T: keyBoard->T.Value = action; break;
        case GLFW_KEY_U: keyBoard->U.Value = action; break;
        case GLFW_KEY_V: keyBoard->V.Value = action; break;
        case GLFW_KEY_W: keyBoard->W.Value = action; break;
        case GLFW_KEY_X: keyBoard->X.Value = action; break;
        case GLFW_KEY_Y: keyBoard->Y.Value = action; break;
        case GLFW_KEY_Z: keyBoard->Z.Value = action; break;


            // Fuction Keys
        case GLFW_KEY_LEFT_SHIFT: keyBoard->ShitftLeft.Value = action; break;
        case GLFW_KEY_SPACE: keyBoard->SpaceBar.Value = action; break;

    }

}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    BF::Mouse* mouse = &BF::Window::WindowsInput.GetValue(window)->MouseInput;
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
            mouse->LeftButton.Value = action;
            break;

        case GLFW_MOUSE_BUTTON_2:
            mouse->RightButton.Value = action;
            break;

        case GLFW_MOUSE_BUTTON_3:
            mouse->ScrollButton.Value = action;
            break;

        case GLFW_MOUSE_BUTTON_4:
            mouse->CustomButton1.Value = action;
            break;

        case GLFW_MOUSE_BUTTON_5:
            mouse->CustomButton2.Value = action;
            break;

        case GLFW_MOUSE_BUTTON_6:
            mouse->CustomButton3.Value = action;
            break;

        case GLFW_MOUSE_BUTTON_7:
            mouse->CustomButton4.Value = action;
            break;

        case GLFW_MOUSE_BUTTON_8:
            mouse->CustomButton5.Value = action;
            break;
    }
}

void OnMousePosition(GLFWwindow* window, double xpos, double ypos)
{
    BF::Mouse* mouse = &BF::Window::WindowsInput.GetValue(window)->MouseInput;

    if (mouse->ShoudRegisterInput())
    {
        float xPosition = static_cast<float>(xpos);
        float yPosition = static_cast<float>(ypos);

        mouse->InputAxis[0] = mouse->Position[0] - xPosition;
        mouse->InputAxis[1] = mouse->Position[1] - yPosition;

        // Clamp
        mouse->InputAxis[0] = BF::Interpolate::Liniar(-1, 1, -15, 15, mouse->InputAxis[0]);
        mouse->InputAxis[1] = BF::Interpolate::Liniar(-1, 1, -15, 15, mouse->InputAxis[1]);

        mouse->Position[0] = xPosition;
        mouse->Position[1] = yPosition;
    }
}

void OnWindowSizeChanged(GLFWwindow* window, int _width, int _height)
{

    glViewport(0, 0, _width, _height);
      

    

   //currentWindow->Resize(_width, _height);
}

double BF::Window::GetTime()
{
    return glfwGetTime();
}

void BF::Window::Resize(const unsigned int width, const unsigned int height)
{

    unsigned int cwidth = width;
    unsigned int cheight = height;

    bool hasChanged = cwidth != width || cheight != height;

    if (hasChanged)
    {
        cwidth = (width / 2);
        cheight = (height / 2);

        //CurrentPlayer->Camera.Settings->Width = cwidth;
        //CurrentPlayer->Camera.Settings->Height = cheight;


        // *cwidth = width;
        // *cheight = height;

        glViewport(0, 0, width, height);// <---- changed the acual size of the render window, can be used for splittscreen?

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
    BF::Mouse* mouse = &BF::Window::WindowsInput.GetValue(_window)->MouseInput;

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
    /*
    VideoConfig* videoConfig = &BF::System.Config.Video;
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int x = mode->width / 2;
    int y = mode->height / 2;

    x -= videoConfig->ScreenResolution.X / 2;
    y -= videoConfig->ScreenResolution.Y / 2;

    SetPosition(x, y);*/
}

void BF::Window::SetTitle(AsciiString& title)
{
    glfwSetWindowTitle(_window, &title[0]);
}

void BF::Window::SetIcon(Image* image)
{
    const unsigned int numberOfImages = 1;

    //image->FlipHorizontal();

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
    /*
    Image* image = new Image();
    VideoConfig* videoConfig = &BF::System.Config.Video;
    int width = videoConfig->ScreenResolution.X;
    int height = videoConfig->ScreenResolution.Y;
    unsigned int size = width * height * 4;

   image->Width = width;
    image->Height = height;
    image->PixelData.ReSize(size);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &image->PixelData[0]);
    */

    return nullptr;// image;
}

bool BF::Window::Create()
{
    VideoConfig* videoConfig = new VideoConfig();//&BF::System.Config.Video;

    videoConfig->FullScreen = false;
    videoConfig->ScreenResolution[0] = 1000;
    videoConfig->ScreenResolution[1] = 1000;
    videoConfig->WindowRefreshRateMode == RefreshRateMode::Unlimited;

    /* Initialize the library */
    if (!glfwInit())
    {
        return false;
    }

    /* Create a windowed mode window and its OpenGL context */
    {
        const char* title = "[BFE] <BitFireEngine>";
        int width = videoConfig->ScreenResolution[0];
        int height = videoConfig->ScreenResolution[1];

        
     
        _window = glfwCreateWindow(width, height, title, NULL, NULL);
       

        if (!_window)
        {
            glfwTerminate();
            return false;
        }

        

        BF::Window::WindowsInput.Add(_window);

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
    SetVideoRefreshRate(videoConfig->WindowRefreshRateMode);

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

    glfwSetTime(0);

    return true;
}

void BF::Window::Update()
{
    ShouldCloseWindow = glfwWindowShouldClose(_window);

    /*
    if (false)
    {
        OnWindowClose.Trigger();
    }*/

    glfwSwapBuffers(_window);
    glfwPollEvents();

    ActiveTime = glfwGetTime();
}