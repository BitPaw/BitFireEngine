#include <Window/Window.h>

#include <stdio.h>

void OnMouseScroll(const BF::MouseScrollDirection mouseScrollDirection)
{
    const char* directionName = nullptr;

    switch(mouseScrollDirection)
    {
        default:
        case BF::MouseScrollDirection::Invalid:
            directionName = "Invalid";
            break;

		case BF::MouseScrollDirection::Up:
            directionName = "Up";
            break;

		case BF::MouseScrollDirection::Down:
            directionName = "Down";
            break;

		case BF::MouseScrollDirection::Left:
            directionName = "Left";
            break;

		case BF::MouseScrollDirection::Right:
            directionName = "Right";
            break;
    }

    printf("[#][Window] Mouse scroll <%s>\n", directionName);
}

void OnMouseClick(const BF::MouseButton mouseButton, const BF::ButtonState buttonState)
{
    const char* mouseButtonText = nullptr;
    const char* buttonStateText = nullptr;

    switch(mouseButton)
    {
        case BF::MouseButton::Invalid:
            mouseButtonText = "Invalid";
            break;

        case BF::MouseButton::Left:
            mouseButtonText = "Left";
            break;

		case BF::MouseButton::Middle:
            mouseButtonText = "Middle";
            break;

		case BF::MouseButton::Right:
            mouseButtonText = "Right";
            break;
    }


    switch(buttonState)
    {
        case BF::ButtonState::Invalid:
            buttonStateText = "Invalid";
            break;

		case BF::ButtonState::Down:
            buttonStateText = "Down";
            break;

		case BF::ButtonState::Hold:
            buttonStateText = "Hold";
            break;

		case BF::ButtonState::Release:
            buttonStateText = "Release";
            break;

    }

    printf("[#][Window] Mouse click <%s:%s>\n", mouseButtonText, buttonStateText);
}

void OnMouseClickDouble(const BF::MouseButton mouseButton)
{
    const char* mouseButtonText = nullptr;

    switch(mouseButton)
    {
        case BF::MouseButton::Invalid:
            mouseButtonText = "Invalid";
            break;

        case BF::MouseButton::Left:
            mouseButtonText = "Left";
            break;

		case BF::MouseButton::Middle:
            mouseButtonText = "Middle";
            break;

		case BF::MouseButton::Right:
            mouseButtonText = "Right";
            break;
    }


    printf("[#][Window] Mouse double click <%s>\n", mouseButtonText);
}

void OnMouseMove(const short x, const short y)
{
      printf("[#][Window] Mouse move x:%iu y:%i5\n", x, y);
}

// Keyboard
void OnKeyBoardKey(const BF::KeyBoardKeyInfo keyBoardKeyInfo)
{
      printf("[#][Window] OnKeyBoardKey\n");
}

// Window
void OnWindowMouseEnter()
{
    printf("[#][Window] Mouse enter\n");
}

void OnWindowMouseLeave()
{
    printf("[#][Window] Mouse leave\n");
}

void OnWindowFocusEnter()
{
    printf("[#][Window] Focus in\n");
}

void OnWindowFocusLeave()
{
    printf("[#][Window] Focus out\n");
}

void OnWindowCreated(BF::Window& window)
{
    printf("[#][Window] Created\n");
}

void OnWindowSizeChanged(const size_t width, const size_t height)
{
    printf("[#][Window] Resize %i x %i\n", width, height);
}

void OnWindowClosing(bool& allowClosing)
{
     printf("[#][Window] Closing...\n");
}

void OnWindowClosed()
{
     printf("[#][Window] Closed\n");
}

void DrawAQuad()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
    glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
    glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
    glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
    glEnd();
}

int main()
{
    BF::Window window;

    window.MouseClickCallBack = OnMouseClick;
	window.MouseClickDoubleCallBack = OnMouseClickDouble;

	window.MouseMoveCallBack = OnMouseMove;
	window.KeyBoardKeyCallBack = OnKeyBoardKey;

    window.MouseScrollCallBack = OnMouseScroll;
	window.WindowMouseEnterCallBack = OnWindowMouseEnter;
    window.WindowMouseLeaveCallBack = OnWindowMouseLeave;

	window.WindowFocusEnterCallBack = OnWindowFocusEnter;
	window.WindowFocusLeaveCallBack = OnWindowFocusLeave;

	window.WindowCreatedCallBack = OnWindowCreated;
	window.WindowSizeChangedCallBack = OnWindowSizeChanged;
	window.WindowClosingCallBack = OnWindowClosing;
	window.WindowClosedCallBack = OnWindowClosed;

    window.Create(600,400, "Hello i bims");

    while(!window.IsRunning);

    window.FrameBufferContextRegister();

    while(1)
    {
        DrawAQuad();

        window.FrameBufferSwap();
    }

    return 0;
}
