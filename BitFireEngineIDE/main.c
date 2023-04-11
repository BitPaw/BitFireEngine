#include <BFEngine.h>

void OnStartUp(BFEngine* const bitFireEngine);
void OnShutDown(const BFEngine* bitFireEngine);

#if !defined(_DEBUG) && defined(OSWindows)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* name, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif
{
    BFEngine bfEngine;
    BFEngineConstruct(&bfEngine);

    bfEngine.StartUpCallBack = OnStartUp; 
    bfEngine.ShutDownCallBack = OnShutDown;

    BFEngineStart(&bfEngine);

    while(BFEngineIsRunning(&bfEngine))
    {
        BFEngineUpdate(&bfEngine);
    }

    BFEngineStop(&bfEngine);

    return 0;
}

PXTexture _dialogBoxTexture;



// Frame A

PXUIElement _infoPanel;
PXUIElement _infoPanelImage;
PXUIElement _infoPanelSpawn;

void OnStartUp(BFEngine* const bitFireEngine)
{
    PXGraphicContext* const graphicContext = &bitFireEngine->WindowMain.GraphicInstance;
    

    PXUIElementConstruct(&_infoPanelSpawn);
    PXUIElementColorSet4F(&_infoPanelSpawn, 0.2, 0.1, 0.2, 1);
    PXUIElementPositionSetXYWH(&_infoPanelSpawn, -0.85f, -0.85f, -0.55f, -0.7f);

    PXGraphicUIElementRegister(graphicContext, &_infoPanelSpawn);


    PXUIElementConstruct(&_infoPanel);
    PXUIElementColorSet4F(&_infoPanel, 0.1, 0.1, 0.1, 1);
    PXUIElementPositionSetXYWH(&_infoPanel, -0.9, -0.9, -0.5, 0.8);
    PXGraphicUIElementRegister(graphicContext, &_infoPanel);
    //PXGraphicUIImage


 



  



    //PXGraphicTextureLoadA(graphicContext, &_dialogBoxTexture, (char*)"C:\\Users\\BitPaw\\Videos\\SquareBlue.png");
}
    
void OnShutDown(const BFEngine* bitFireEngine)
{

}