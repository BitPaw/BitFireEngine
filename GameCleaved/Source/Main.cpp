//-----------------------------------------------------------------------------
#include <stdio.h>
#include <signal.h>

#include <OS/OSDefine.h>
#include <Async/Thread.h>
#include <Window/Window.h>

#include <System/BitFireEngine.h>
#include <Hardware/Memory/Memory.h>

#include "CleavedGameSystem.h"
//-----------------------------------------------------------------------------

void OnMouseButtonEvent(const BF::MouseButton mouseButton, const BF::ButtonState buttonState)
{
    const char* mouseButtonText = 0;
    const char* buttonStateText = 0;

    switch (mouseButton)
    {
        case BF::MouseButton::Left:
        {
            mouseButtonText = "Left";
            break;
        }
        case BF::MouseButton::Middle:
        {
            mouseButtonText = "Middle";
            break;
        }
        case BF::MouseButton::Right:
        {
            mouseButtonText = "Right";
            break;
        }
    }

    switch (buttonState)
    {
        case BF::ButtonState::Down:
        {
            buttonStateText = "Down";
            break;
        }
        case BF::ButtonState::Hold:
        {
            buttonStateText = "Hold";
            break;
        }
        case BF::ButtonState::Release:
        {
            buttonStateText = "Release";
            break;
        }
    }

    printf("[Mouse] %s:%s\n", mouseButtonText, buttonStateText);
}

void OnMouseMoveEvent(const unsigned short x, const unsigned short y)
{
    printf("[Mouse] X:%5i Y:%5i\n", x, y);
}

void OnKeyBoardKey(const BF::KeyBoardKeyInfo keyBoardKeyInfo)
{
    printf
    (
        "[KEY][%c] %wc %i %i %i %i %i %i\n",
        keyBoardKeyInfo.Mode,
        keyBoardKeyInfo.Key,
        keyBoardKeyInfo.Repeat,
        keyBoardKeyInfo.ScanCode,
        keyBoardKeyInfo.SpecialKey,
        keyBoardKeyInfo.KontextCode,
        keyBoardKeyInfo.PreState,
        keyBoardKeyInfo.GapState
    );
}

void CallBackErrorOnError(int errorID)
{
    printf("\n\nKilled Process!\n\n");
}

ThreadFunctionReturnType RenderLoop(void* windowAdress)
{
    BF::Window* window = (BF::Window*)windowAdress;

    while (true)
    {
         #if defined(OSUnix)

        #elif defined(OSWindows)
   if (!window->HandleDeviceContext)
        {
            continue;
        }
        #endif


        // Set every pixel in the frame buffer to the current clear color.
       //glClear(GL_COLOR_BUFFER_BIT);

       // Drawing is done by specifying a sequence of vertices.  The way these
       // vertices are connected (or not connected) depends on the argument to
       // glBegin.  GL_POLYGON constructs a filled polygon.
        glBegin(GL_POLYGON);
        glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
        glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
        glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
        glEnd();

        // Flush drawing command buffer to make drawing happen as soon as possible.
        glFlush();

        #if defined(OSUnix)

        #elif defined(OSWindows)
           SwapBuffers(window->HandleDeviceContext);
        #endif

        //  BFFF::Window::Update();
         // UpdateWindow(winow);
    }
}

void TakeScreenShot(BF::Window& window, BF::Image& image)
{
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int width = 0;
    unsigned int height = 0;

    window.Size(x,y,width, height);

    unsigned int size = width * height * 3;

    if (image.PixelDataSize != size)
    {
        BF::Memory::Release(image.PixelData, size);
        image.PixelData = BF::Memory::Allocate<unsigned char>(size);
        image.PixelDataSize = size;
    }

    image.Width = width;
    image.Height = height;
    image.Format = BF::ImageDataFormat::BGR;

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, image.PixelData);
}

#if !defined(_DEBUG) && defined(OSWindowsE)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif
{
    //---<Error Callback>-----
    auto functionPointer = signal(SIGABRT, CallBackErrorOnError);
    bool validLinkage = functionPointer != SIG_ERR;

    if (!validLinkage)
    {
        fputs("An error occurred while setting a signal handler.\n", stderr);
        return EXIT_FAILURE;
    }
    //---------------------------

    Cleaved::CleavedGameSystem cleavedGameSystem;

    cleavedGameSystem.GameSystem.Start();

    while (cleavedGameSystem.GameSystem.IsRunning)
    {
        cleavedGameSystem.GameSystem.Update();
    }

    cleavedGameSystem.GameSystem.Stop();

    return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------
