#include "Window.h"

#include <stdio.h>

#include "../VideoConfig.h"

#include "../../../SystemResource/Source/Math/Interpolate.h"
#include "../../../Dependencies/include/GL/glew.h"
#include "../../../Dependencies/include/GLFW/glfw3.h"

BF::Dictionary<GLFWwindow*, BF::InputContainer> BF::Window::WindowsInput;

int BF::Window::Width = 0;
int BF::Window::Height = 0;

BF::Window::Window()
{
    _window = nullptr;
    _cursor = nullptr;
    _montor = nullptr;

    ActiveTime = 0;
    ShouldCloseWindow = false;
}

BF::Window::~Window()
{
    glfwTerminate();
}

void BF::Window::OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
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

void BF::Window::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
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

void BF::Window::OnMousePosition(GLFWwindow* window, double xpos, double ypos)
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

void BF::Window::OnWindowSizeChanged(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); // Change rendering Image to size of screen

    Width = width;
    Height = height;
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
        (int)image->Width,
        (int)image->Height,
        image->PixelData 
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
        (int)image->Width,
        (int)image->Height,
        image->PixelData 
    };

    glfwSetWindowIcon(_window, numberOfImages, &flfwImage);
}

void BF::Window::TakeScreenShot(Image& image)
{
    int width = 0;
    int height = 0;

    glfwGetWindowSize(_window, &width, &height);

    unsigned int size = width * height * 3;

    if (image.PixelDataSize != size)
    {
        free(image.PixelData);
        image.PixelData = (unsigned char*)malloc(size);
        image.PixelDataSize = size;
    } 

    image.Width = width;
    image.Height = height;
    image.Format = ImageDataFormat::BGR;  

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, image.PixelData);   
}

void BF::Window::OnGLFWError(int errorCode, const char* description)
{
    printf("[Error][GLFW] <%i> %s\n", errorCode, description);
}

bool BF::Window::Create(int width, int height, const char* title)
{
    VideoConfig* videoConfig = new VideoConfig();//&BF::System.Config.Video;

    Width = width;
    Height = height;

    videoConfig->FullScreen = false;
    videoConfig->ScreenResolution[0] = width;
    videoConfig->ScreenResolution[1] = height;
    videoConfig->WindowRefreshRateMode == RefreshRateMode::Unlimited;

    printf("[i][GLFW] Initialize libary... ");

    int glfwErrorCode = glfwInit(); // Initialize the library
    const char* message = nullptr;

    switch (glfwErrorCode)
    {
        case GLFW_TRUE:
            message = "OK";
            break;
    
        case GLFW_FALSE:
            message = "Failed";
            break;

        case GLFW_PLATFORM_ERROR:
            message = "Platfrom Error";
            break;

        default:
            message = "Unkown";
            break;
    }

    printf("[%s]\n", message);

    glfwSetErrorCallback(OnGLFWError);

    /* Create a windowed mode window and its OpenGL context */
    {
        int width = videoConfig->ScreenResolution[0];
        int height = videoConfig->ScreenResolution[1];

        printf("[i][GLFW] Create Window... ");
     
        _window = glfwCreateWindow(width, height, title, NULL, NULL);
       
        if (!_window)
        {
            glfwTerminate();
            printf("[Failed]\n");         
            return false;
        }        

        printf("[OK]\n");

        BF::Window::WindowsInput.Add(_window);
    }

    glfwMakeContextCurrent(_window);

    printf("[i][GLEW] Initialize OpenGL context... ");

    if (glewInit() != GLEW_OK)
    {
        printf("[Failed]\n");
        return false;
    }

    printf("[OK]\n");

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

    if (true) // X-RAY
    {
        glEnable(GL_DEPTH_TEST);
    }

    if (true)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
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