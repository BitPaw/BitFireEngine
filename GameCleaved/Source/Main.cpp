#include "CleavedGameSystem.h"

#if !defined(_DEBUG) && defined(OSWindowsE)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif
{
    Cleaved::CleavedGameSystem cleavedGameSystem;

    cleavedGameSystem.GameSystem.Start();

    while (cleavedGameSystem.GameSystem.IsRunning)
    {
        cleavedGameSystem.GameSystem.Update();
    }

    cleavedGameSystem.GameSystem.Stop();

    return EXIT_SUCCESS;
}