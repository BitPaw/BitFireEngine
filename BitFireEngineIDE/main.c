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

PXUIElement _infoPanel;
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






    PXUIElementConstruct(&_infoPanel, PXUIElementTypePanel);
    _infoPanel.IsHoverable = PXTrue;
    PXUIElementColorSet4F(&_infoPanel, 0.1, 0.1, 0.1, 1);
    PXUIElementPositionSetXYWH(&_infoPanel, -0.9, -0.9, -0.5, 0.8);
    PXGraphicUIElementRegister(graphicContext, &_infoPanel);
    //PXGraphicUIImage

    PXUIElementConstruct(&_infoPanelSpawn, PXUIElementTypeButton);
    _infoPanelSpawn.IsHoverable = PXTrue;
    PXUIElementColorSet4F(&_infoPanelSpawn, 0.2, 0.1, 0.2, 1);
    PXUIElementPositionSetXYWH(&_infoPanelSpawn, -0.85f, -0.85f, -0.55f, -0.7f);

    PXGraphicUIElementRegister(graphicContext, &_infoPanelSpawn);



    {
        PXText pxText;

        //

        PXTextMakeFixedA(&pxText, "Font/A.bmp");

       // PXTextMakeFixedA(&pxText, "Texture/MissingTexture.bmp");

        PXGraphicTextureLoad(graphicContext, &_testImage, &pxText);
    }

	
    PXUIElementConstruct(&_textureTestA, PXUIElementTypeImage);
    _textureTestA.IsHoverable = PXTrue;
    PXUIElementColorSet4F(&_textureTestA, 0.5, 0.5, 0.5, 0.5);
    PXUIElementPositionSetXYWH(&_textureTestA, 0.55f, -0.52f, 0.88f, 0.67f);
    _textureTestA.TextureID = _testImage.ID;

    PXGraphicUIElementRegister(graphicContext, &_textureTestA);



        // TEXT
    PXText pxText;

    PXTextMakeFixedA(&pxText, "Font/A.fnt");

    PXGraphicFontLoad(graphicContext, &DefaultFont, &pxText);


    PXUIElementConstruct(&_infoPanelText, PXUIElementTypeText);
    _infoPanelText.FontID = &DefaultFont;
    PXUIElementColorSet4F(&_infoPanelText, 0.5, 0.5, 0.5, 1);
    //PXUIElementPositionSetXYWH(&_infoPanelText, -0.85f, -0.85f, -0.55f, -0.7f);
    PXUIElementPositionSetXYWH(&_infoPanelText, -0.82f, -0.82f, -0.48f, -0.67f);

    PXUIElementTextSetA(&_infoPanelText, "HeLÖöW");

    PXGraphicUIElementRegister(graphicContext, &_infoPanelText);
 


    PXUIElementConstruct(&_positionText, PXUIElementTypeText);
    _positionText.FontID = &DefaultFont;
    PXUIElementColorSet4F(&_positionText, 0.5, 0.5, 0.5, 1);
    //PXUIElementPositionSetXYWH(&_infoPanelText, -0.85f, -0.85f, -0.55f, -0.7f);
    PXUIElementPositionSetXYWH(&_positionText, -0.82f, -0.52f, 0.38f, -0.67f);

    PXUIElementTextSetA(&_positionText, "Position : ");

    PXGraphicUIElementRegister(graphicContext, &_positionText);


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

    PXTextPrint(&pxText, "[BitFireEngine] Mouse: X:%6.4f, Y:%6.4f", x, y);

    //PXTextPrint(&pxText, "[BitFireEngine] FPS:%5.2f, ms:%4.2f", bitFireEngine->TimeFPS, bitFireEngine->TimeMS);

    PXWindowTitleSet(&bitFireEngine->WindowMain, &pxText);
#endif
}
    
void OnShutDown(const BFEngine* bitFireEngine)
{
    PXWindowDestruct(&bitFireEngine->WindowMain);
}