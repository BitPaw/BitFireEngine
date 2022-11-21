#include <iostream>

//#include <System/BitFireEngine.h>
#include "../BitFireEngine/Source/System/BitFireEngine.h"

void OnStartUp(BF::BitFireEngine* const bitFireEngine);
void OnShutDown(const BF::BitFireEngine* bitFireEngine);

#if !defined(_DEBUG) && defined(OSWindows)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif
{
    BF::BitFireEngine bitFireEngine;

    bitFireEngine.StartUpCallBack = OnStartUp; 
    bitFireEngine.ShutDownCallBack = OnShutDown;

    bitFireEngine.Start();

    while(bitFireEngine.IsRunning)
    {
        bitFireEngine.Update();
    }

    bitFireEngine.Stop();

    return EXIT_SUCCESS;
}



void OnStartUp(BF::BitFireEngine* const bitFireEngine)
{
    
}
    
void OnShutDown(const BF::BitFireEngine* bitFireEngine)
{

}