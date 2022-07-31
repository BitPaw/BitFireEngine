#include <iostream>

#include <Window/Window.h>
#include "../BitFireEngine/Source/System/BitFireEngine.h"

#if !defined(_DEBUG) && defined(OSWindows)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif
{
    BF::BitFireEngine gameSystem;

    gameSystem.Start();

    BF::Window window;

    window.Create(WindowSizeDefault, WindowSizeDefault, "BFE-IDE", false);

    while(gameSystem.IsRunning)
    {
        gameSystem.Update();
    }

    gameSystem.Stop();

    return EXIT_SUCCESS;
}