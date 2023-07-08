#include <BFEngine.h>

void OnStartUp(BFEngine* const bitFireEngine);
void OnShutDown(const BFEngine* bitFireEngine);
void OnUpdateGameLogicEvent(BFEngine* const bitFireEngine, const float deltaTime);

#if !defined(_DEBUG) && defined(OSWindows) && 0
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

PXUIElement _uiSceneElements;
PXUIElement _uiPanelScene;
PXUIElement _uiSceneTexture;
PXUIElement _uiInfoPanel;

PXUIElement _infoPanelImage;
PXUIElement _infoPanelSpawn;
PXUIElement _infoPanelText;
PXUIElement _positionText;
PXFont DefaultFont;

PXUIElement _textureTestA;
PXTexture _testImage;

void OnStartUp(BFEngine* const bitFireEngine)
{
    PXGraphicContext* const graphicContext = &bitFireEngine->WindowMain.GraphicInstance;
    
#if 1

    {
        PXText pxText;

        //

      //  PXTextMakeFixedA(&pxText, "C:\\Users\\BitPaw\\Downloads\\2023-05-02 01_32_39-Window.png");

        PXTextMakeFixedA(&pxText, "Texture/Scene.png");

        PXGraphicTextureLoad(graphicContext, &_testImage, &pxText);
    }

    PXText pxText;
    PXTextMakeFixedA(&pxText, "Font/A.fnt");
    PXGraphicFontLoad(graphicContext, &DefaultFont, &pxText);




    PXUIElementConstruct(&_uiSceneElements, PXUIElementTypePanel);
    PXUIElementHoverable(&_uiSceneElements, PXTrue);
    PXUIElementColorSet4F(&_uiSceneElements, 0.1, 0.1, 0.1, 1);
    PXUIElementPositionSetXYWH(&_uiSceneElements, -0.98, -0.95, -0.60, 0.95, PXUIElementPositionRelative);
    PXUIElementTextSetA(&_uiSceneElements, "Assets");
    PXUIElementFontSet(&_uiSceneElements, &DefaultFont);
    PXGraphicUIElementRegister(graphicContext, &_uiSceneElements);

    PXUIElementConstruct(&_infoPanelSpawn, PXUIElementTypeButton);
    PXUIElementParentSet(&_infoPanelSpawn, &_uiSceneElements);
    PXUIElementHoverable(&_infoPanelSpawn, PXTrue);
    PXUIElementColorSet4F(&_infoPanelSpawn, 0.40f, 0.15f, 0.15f, 1);
    PXUIElementPositionSetXYWH(&_infoPanelSpawn, 0.02, 0.05, -0.02, -1.65, PXUIElementPositionRelative);
    PXGraphicUIElementRegister(graphicContext, &_infoPanelSpawn);

    PXUIElementConstruct(&_infoPanelText, PXUIElementTypeText);
    PXUIElementParentSet(&_infoPanelText, &_uiSceneElements);
    PXUIElementFontSet(&_infoPanelText, &DefaultFont);
    PXUIElementColorSet4F(&_infoPanelText, 0.5, 0.5, 0.5, 1);
    PXUIElementPositionSetXYWH(&_infoPanelText, 0.06, 0.1, -0.025, -0.025, PXUIElementPositionRelative);
    PXUIElementTextSetA(&_infoPanelText, "Button");
    PXGraphicUIElementRegister(graphicContext, &_infoPanelText);


    PXUIElementConstruct(&_uiPanelScene, PXUIElementTypePanel);
    PXUIElementHoverable(&_uiPanelScene, PXTrue);
    PXUIElementColorSet4F(&_uiPanelScene, 0.1, 0.1, 0.1, 1);
    PXUIElementPositionSetXYWH(&_uiPanelScene, -0.59, -0.95, 0.6, 0.95, PXUIElementPositionRelative);
    PXUIElementTextSetA(&_uiPanelScene, "Scene");
    PXUIElementFontSet(&_uiPanelScene, &DefaultFont);
    PXGraphicUIElementRegister(graphicContext, &_uiPanelScene);


    PXUIElementConstruct(&_uiSceneTexture, PXUIElementTypeRenderFrame);
    PXUIElementParentSet(&_uiSceneTexture, &_uiPanelScene);
    PXUIElementHoverable(&_uiSceneTexture, PXTrue);
    PXUIElementPositionSetXYWH(&_uiSceneTexture, 0.02, 0.05, -0.02, -0.1, PXUIElementPositionRelative);
    PXUIElementFontSet(&_uiSceneTexture, &DefaultFont);
    _uiSceneTexture.TextureID = _testImage.ID;
    PXGraphicUIElementRegister(graphicContext, &_uiSceneTexture);
    //_textureTestA.TextureID = _testImage.ID;

    PXUIElementConstruct(&_uiInfoPanel, PXUIElementTypePanel);
    PXUIElementHoverable(&_uiInfoPanel, PXTrue);
    PXUIElementColorSet4F(&_uiInfoPanel, 0.1, 0.1, 0.1, 1);
    PXUIElementPositionSetXYWH(&_uiInfoPanel, 0.62, -0.95, 0.98, 0.95, PXUIElementPositionRelative);
    PXUIElementTextSetA(&_uiInfoPanel, "Info");
    PXUIElementFontSet(&_uiInfoPanel, &DefaultFont);
    PXGraphicUIElementRegister(graphicContext, &_uiInfoPanel);







#if 0
	
    PXUIElementConstruct(&_textureTestA, PXUIElementTypeImage);
    _textureTestA.IsHoverable = PXTrue;
    PXUIElementColorSet4F(&_textureTestA, 0.5, 0.5, 0.5, 0.5);
    PXUIElementPositionSetXYWH(&_textureTestA, 0.55f, -0.52f, 0.88f, 0.67f, PXUIElementPositionRelative);
    _textureTestA.TextureID = _testImage.ID;

    PXGraphicUIElementRegister(graphicContext, &_textureTestA);
#endif


        // TEXT



 
 

    /*
    PXUIElementConstruct(&_positionText, PXUIElementTypeText);
    _positionText.FontID = &DefaultFont;    
    PXUIElementColorSet4F(&_positionText, 1, 1, 1, 1);
    PXUIElementPositionSetXYWH(&_positionText, -0.9, 0.75, -0.8, 0.9);
    //PXUIElementPositionSetXYWH(&_positionText, -0.82f, -0.52f, 0.38f, -0.67f);

    PXUIElementTextSetA(&_positionText, "Assets");

    PXGraphicUIElementRegister(graphicContext, &_positionText);*/


#endif // 0


    //PXGraphicTextureLoadA(graphicContext, &_dialogBoxTexture, (char*)"C:\\Users\\BitPaw\\Videos\\SquareBlue.png");

}

void OnUpdateGameLogicEvent(BFEngine* const bitFireEngine, const float deltaTime)
{
#if 1
    PXMouse* const mouse = &bitFireEngine->WindowMain.MouseCurrentInput;


    PXUIElementTextSetAV(&_positionText, "Position : %3.2f", bitFireEngine->TimeFPS);

    float x = mouse->Delta[0];
    float y = mouse->Delta[1];

   // sprintf_s(_infoPanelText.Name, 32, "Mouse Pos x:%6.3f y:%6.3f", x, y);

    PXText pxText;
    PXTextConstructBufferA(&pxText, 64);

    //PXTextPrint(&pxText, "[BitFireEngine] Mouse: X:%6.4f, Y:%6.4f", x, y);

    PXTextPrint(&pxText, "[BitFireEngine] FPS:%5.2f, ms:%4.2f", bitFireEngine->TimeFPS, bitFireEngine->TimeMS);

    PXWindowTitleSet(&bitFireEngine->WindowMain, &pxText);
#endif
}
    
void OnShutDown(const BFEngine* bitFireEngine)
{
    PXWindowDestruct(&bitFireEngine->WindowMain);
}