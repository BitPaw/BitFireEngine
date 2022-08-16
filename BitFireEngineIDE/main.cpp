#include <iostream>

#include <Window/Window.h>
//#include <System/BitFireEngine.h>
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

    window.Create(600, 400, "BFE-IDE", false);

    while(gameSystem.IsRunning)
    {
        gameSystem.Update();
    }

    gameSystem.Stop();

    return EXIT_SUCCESS;
}