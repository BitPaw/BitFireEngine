#include <BFEngine.h>

void OnStartUp(BFEngine* const bitFireEngine);
void OnShutDown(const BFEngine* bitFireEngine);
void OnUpdateGameLogicEvent(BFEngine* const bitFireEngine, const float deltaTime);

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
    bfEngine.UpdateGameLogicCallBack = OnUpdateGameLogicEvent;

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
PXUIElement _infoPanelText;
PXFont DefaultFont;

void OnStartUp(BFEngine* const bitFireEngine)
{
    PXGraphicContext* const graphicContext = &bitFireEngine->WindowMain.GraphicInstance;
    
    PXGraphicFontLoadA(graphicContext, &DefaultFont, "Font/segoe.fnt");

#if 1
    PXUIElementConstruct(&_infoPanel);
    _infoPanel.Type = PXUIElementTypePanel;
    PXUIElementColorSet4F(&_infoPanel, 0.1, 0.1, 0.1, 1);
    PXUIElementPositionSetXYWH(&_infoPanel, -0.9, -0.9, -0.5, 0.8);
    PXGraphicUIElementRegister(graphicContext, &_infoPanel);
    //PXGraphicUIImage



    PXUIElementConstruct(&_infoPanelSpawn);
    _infoPanelSpawn.Type = PXUIElementTypeButton;
    PXUIElementColorSet4F(&_infoPanelSpawn, 0.2, 0.1, 0.2, 1);
    PXUIElementPositionSetXYWH(&_infoPanelSpawn, -0.85f, -0.85f, -0.55f, -0.7f);

    PXGraphicUIElementRegister(graphicContext, &_infoPanelSpawn);
#endif




    PXUIElementConstruct(&_infoPanelText);
    _infoPanelText.Type = PXUIElementTypeText;
    _infoPanelText.FontID = &DefaultFont;
    PXUIElementColorSet4F(&_infoPanelText, 1, 0.5, 0.5, 1);
    //PXUIElementPositionSetXYWH(&_infoPanelText, -0.85f, -0.85f, -0.55f, -0.7f);
    PXUIElementPositionSetXYWH(&_infoPanelText, -0.95, -0.95, 0.55f, 0.7f);


    PXGraphicUIElementRegister(graphicContext, &_infoPanelText);

    //PXGraphicTextureLoadA(graphicContext, &_dialogBoxTexture, (char*)"C:\\Users\\BitPaw\\Videos\\SquareBlue.png");
}

void OnUpdateGameLogicEvent(BFEngine* const bitFireEngine, const float deltaTime)
{
    float x = bitFireEngine->InputContainer.MouseInput.PositionNormalisized[0];
    float y = bitFireEngine->InputContainer.MouseInput.PositionNormalisized[1];

    sprintf_s(_infoPanelText.Name, 32, "Mouse Pos x:%6.3f y:%6.3f", x, y);
}
    
void OnShutDown(const BFEngine* bitFireEngine)
{

}