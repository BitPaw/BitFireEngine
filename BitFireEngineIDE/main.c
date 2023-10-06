#include <BFEngine.h>

#include <Math/PXMath.h>

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

PXTexture2D _dialogBoxTexture;



// Frame A

PXUIElement* _uiSceneElements;
PXUIElement* _uiSceneElementsTitleBar;
PXUIElement* _uiSceneElementsTitleBarText;
PXUIElement* _uiPanelScene;
PXUIElement* _uiSceneTexturePanel;
PXTexture2D _uiSceneTexture;

PXUIElement* _uiInfoPanel;
PXUIElement* _uiInfoPanelTitleBar;
PXUIElement* _uiInfoPanelTitleBarText;
PXUIElement* _uiInfoPositionText;

PXUIElement* _infoPanelImage;
PXUIElement* _infoPanelTextSpawn;
PXUIElement* _infoPanelButtonText;
PXUIElement* _infoPanelText;
PXUIElement* _positionText;
PXFont DefaultFont;

PXUIElement* _textureTestA;
PXTexture2D _testImage;
PXRenderable _pxRenderableModel;

const PXColorRGBAF buttonColor = { 0.1, 0.3, 0.5, 1 }; //  0.40f, 0.15f, 0.15f, 1
const PXColorRGBAF panelReference = { 0.0, 0.1, 0.2, 1 };
PXColorRGBAF titleColor = { 0.1, 0.2, 0.6, 1 };
const PXColorRGBAF textColor = { 0.6, 0.6, 1.0, 1 };
float animation = 0;

void OnStartUp(BFEngine* const bitFireEngine)
{
    PXGraphic* const pxGraphic = &bitFireEngine->Graphic;
    
#if 1

    {
        PXText pxText;

        //

      //  PXTextMakeFixedA(&pxText, "C:\\Users\\BitPaw\\Downloads\\2023-05-02 01_32_39-Window.png");

      //  PXTextMakeFixedA(&pxText, "Texture/Scene.png");

        // PXGraphicTexture2DLoad(pxGraphic, &_testImage, &pxText);
    }



    PXText pxText;
    PXTextMakeFixedA(&pxText, "Font/A.fnt");
    PXGraphicFontLoad(pxGraphic, &DefaultFont, &pxText); 


    // Rectangle: Assets
    PXGraphicUIElementCreate(pxGraphic, &_uiSceneElements, 1, PXNull);
    PXGraphicUIElementTypeSet(pxGraphic, _uiSceneElements, PXUIElementTypePanel);
    PXGraphicUIElementFlagSet(_uiSceneElements, PXUIElementNormal | PXUIElementIsHoverable);
    _uiSceneElements->ColorTintReference = &panelReference;
    PXUIElementSizeSet(_uiSceneElements, 0.02, 0.02, 1.65, 0.02, PXUIElementPositionRelative);
    // TitleBar:Panel
    PXGraphicUIElementCreate(pxGraphic, &_uiSceneElementsTitleBar, 1, _uiSceneElements);
    PXGraphicUIElementTypeSet(pxGraphic, _uiSceneElementsTitleBar, PXUIElementTypePanel);
    PXGraphicUIElementFlagSet(_uiSceneElementsTitleBar, PXUIElementNormal | PXUIElementIsHoverable);
    _uiSceneElementsTitleBar->ColorTintReference = &titleColor;
    PXUIElementSizeSet(_uiSceneElementsTitleBar, 0.00, 1.90, 0.0, 0.00, PXUIElementPositionRelative);
   // Titlebar:Text
    PXGraphicUIElementCreate(pxGraphic, &_uiSceneElementsTitleBarText, 1, _uiSceneElementsTitleBar);
    PXGraphicUIElementTypeSet(pxGraphic, _uiSceneElementsTitleBarText, PXUIElementTypeText);
    PXGraphicUIElementFlagSet(_uiSceneElementsTitleBarText, PXUIElementNormal | PXUIElementIsHoverable);
    _uiSceneElementsTitleBarText->ColorTintReference = &textColor;
    PXUIElementSizeSet(_uiSceneElementsTitleBarText, 0.005, 0.005, 0.005, 0.005, PXUIElementPositionRelative);
    PXGraphicPXUIElementTextSetA(_uiSceneElementsTitleBarText, "Scene");
    _uiSceneElementsTitleBarText->TextInfo.FontID = &DefaultFont;

    //PXUIElementTextSetA(&_uiSceneElements, "Assets");
    //PXUIElementFontSet(&_uiSceneElements, &DefaultFont);
    //PXGraphicUIElementRegister(pxGraphic, &_uiSceneElements);

    // Button
    PXGraphicUIElementCreate(pxGraphic, &_infoPanelTextSpawn, 1, _uiSceneElements);
    PXGraphicUIElementTypeSet(pxGraphic, _infoPanelTextSpawn, PXUIElementTypeButton);
    PXGraphicUIElementFlagSet(_infoPanelTextSpawn, PXUIElementNormal | PXUIElementIsHoverable);
    PXUIElementColorSet4F(&_infoPanelTextSpawn, 0.40f, 0.15f, 0.15f, 1);
    PXUIElementSizeSet(_infoPanelTextSpawn, 0.025, 0.05, 0.025, 1.8, PXUIElementPositionRelative);
    _infoPanelTextSpawn->ColorTintReference = &buttonColor;
    // Button Text
    PXGraphicUIElementCreate(pxGraphic, &_infoPanelButtonText, 1, _infoPanelTextSpawn);
    PXGraphicUIElementTypeSet(pxGraphic, _infoPanelButtonText, PXUIElementTypeText);
    PXGraphicUIElementFlagSet(_infoPanelButtonText, PXUIElementNormal | PXUIElementIsHoverable);
    PXUIElementSizeSet(_infoPanelButtonText, 0.005, 0.005, 0.005, 0.005, PXUIElementPositionRelative);
    PXGraphicPXUIElementTextSetA(_infoPanelButtonText, "Button");
    _infoPanelButtonText->TextInfo.FontID = &DefaultFont;
    _infoPanelButtonText->ColorTintReference = &textColor;


#if 1
    PXGraphicUIElementCreate(pxGraphic, &_infoPanelText, 1, _infoPanelTextSpawn);
    PXGraphicUIElementTypeSet(pxGraphic, _infoPanelText, PXUIElementTypeText);
   // PXUIElementFontSet(&_infoPanelText, &DefaultFont);
    PXUIElementColorSet4F(_infoPanelText, 0.5, 0.5, 0.5, 1);
    PXUIElementSizeSet(_infoPanelText, 0.02, 0.02, 0.02, 0.02, PXUIElementPositionRelative);
    //PXUIElementTextSetA(&_infoPanelText, "Button");
  //  PXGraphicUIElementRegister(pxGraphic, &_infoPanelText);


    // Panel: Scene
    PXGraphicUIElementCreate(pxGraphic, &_uiPanelScene, 1, PXNull);
    PXGraphicUIElementTypeSet(pxGraphic, _uiPanelScene, PXUIElementTypePanel);
    PXGraphicUIElementFlagSet(_uiPanelScene, PXUIElementNormal | PXUIElementIsHoverable);
    _uiPanelScene->ColorTintReference = &panelReference;
      PXUIElementSizeSet(_uiPanelScene, 0.36, 0.02, 0.36, 0.02, PXUIElementPositionRelative);
    //  PXUIElementTextSetA(&_uiPanelScene, "Scene");
    // PXUIElementFontSet(&_uiPanelScene, &DefaultFont);
   // PXGraphicUIElementRegister(pxGraphic, &_uiPanelScene);

    // RenderFrame: Scene
    PXGraphicUIElementCreate(pxGraphic, &_uiSceneTexturePanel, 1, _uiPanelScene);
    PXGraphicUIElementTypeSet(pxGraphic, _uiSceneTexturePanel, PXUIElementTypeRenderFrame);
    PXGraphicUIElementFlagSet(_uiSceneTexturePanel, PXUIElementNormal | PXUIElementIsHoverable);
     PXUIElementSizeSet(_uiSceneTexturePanel, 0.05, 0.05, 0.05, 0.05, PXUIElementPositionRelative);
    //  PXUIElementFontSet(&_uiSceneTexturePanel, &DefaultFont);
   // _uiSceneTexturePanel.TextureReference = &_testImage;
   // _uiSceneTexturePanel.FrameRenderTextureReference = &_uiSceneTexture;
   // PXGraphicUIElementRegister(pxGraphic, &_uiSceneTexturePanel);
    //_textureTestA.TextureID = _testImage.ID;


     // Panel:Info
    PXGraphicUIElementCreate(pxGraphic, &_uiInfoPanel, 1, PXNull);
    PXGraphicUIElementTypeSet(pxGraphic, _uiInfoPanel, PXUIElementTypePanel);
    PXGraphicUIElementFlagSet(_uiInfoPanel, PXUIElementNormal | PXUIElementIsHoverable);
    _uiInfoPanel->ColorTintReference = &panelReference;
     PXUIElementSizeSet(_uiInfoPanel, 1.65, 0.02, 0.02, 0.02, PXUIElementPositionRelative);
    //  PXUIElementTextSetA(&_uiInfoPanel, "Info");
    //  PXUIElementFontSet(&_uiInfoPanel, &DefaultFont);
 //   PXGraphicUIElementRegister(pxGraphic, &_uiInfoPanel);

         // TitleBar:Infol
     PXGraphicUIElementCreate(pxGraphic, &_uiInfoPanelTitleBar, 1, _uiInfoPanel);
     PXGraphicUIElementTypeSet(pxGraphic, _uiInfoPanelTitleBar, PXUIElementTypePanel);
     PXGraphicUIElementFlagSet(_uiInfoPanelTitleBar, PXUIElementNormal | PXUIElementIsHoverable);
     _uiInfoPanelTitleBar->ColorTintReference = &titleColor;
     PXUIElementSizeSet(_uiInfoPanelTitleBar, 0.00, 1.90, 0.0, 0.00, PXUIElementPositionRelative);

    PXGraphicUIElementCreate(pxGraphic, &_uiInfoPanelTitleBarText, 1, _uiInfoPanelTitleBar);
    PXGraphicUIElementTypeSet(pxGraphic, _uiInfoPanelTitleBarText, PXUIElementTypeText);
    PXGraphicUIElementFlagSet(_uiInfoPanelTitleBarText, PXUIElementNormal | PXUIElementIsHoverable);
    PXUIElementColorSet4F(_uiInfoPanelTitleBarText, 1, 1, 1, 1);
     PXUIElementSizeSet(_uiInfoPanelTitleBarText, 0.005, 0.005, 0.005, 0.005, PXUIElementPositionRelative);
     PXGraphicPXUIElementTextSetA(_uiInfoPanelTitleBarText, "Info");
     _uiInfoPanelTitleBarText->TextInfo.FontID = &DefaultFont;
     _uiInfoPanelTitleBarText->ColorTintReference = &textColor;


    //  PXUIElementTextSetA(&_uiInfoPositionText, "Position");
    //  PXUIElementFontSet(&_uiInfoPositionText, &DefaultFont);
   // PXGraphicUIElementRegister(pxGraphic, &_uiInfoPositionText);


    // Load model
    {
     //   PXModel pxModel;

        PXText modelFilePath;
        PXTextMakeFixedA(&modelFilePath, "Model/Tiger.obj");
        //PXModelLoad(&bitFireEngine->pxModelTEST, &modelFilePath);

       // PXGraphicModelLoad(pxGraphic, &_pxRenderableModel, &modelFilePath);
    }

    PXGraphicUIElementPrint(pxGraphic);
#endif


#if 0
	
    PXUIElementConstruct(&_textureTestA, PXUIElementTypeImage);
    _textureTestA.IsHoverable = PXTrue;
    PXUIElementColorSet4F(&_textureTestA, 0.5, 0.5, 0.5, 0.5);
    PXUIElementPositionSetXYWH(&_textureTestA, 0.55f, -0.52f, 0.88f, 0.67f, PXUIElementPositionRelative);
    _textureTestA.TextureID = _testImage.ID;

    PXGraphicUIElementRegister(pxGraphic, &_textureTestA);
#endif


        // TEXT



 
 

    /*
    PXUIElementConstruct(&_positionText, PXUIElementTypeText);
    _positionText.FontID = &DefaultFont;    
    PXUIElementColorSet4F(&_positionText, 1, 1, 1, 1);
    PXUIElementPositionSetXYWH(&_positionText, -0.9, 0.75, -0.8, 0.9);
    //PXUIElementPositionSetXYWH(&_positionText, -0.82f, -0.52f, 0.38f, -0.67f);

    PXUIElementTextSetA(&_positionText, "Assets");

    PXGraphicUIElementRegister(pxGraphic, &_positionText);*/


#endif // 0


    //PXGraphicTextureLoadA(pxGraphic, &_dialogBoxTexture, (char*)"C:\\Users\\BitPaw\\Videos\\SquareBlue.png");

}

void OnUpdateGameLogicEvent(BFEngine* const bitFireEngine, const float deltaTime)
{
    float xx = PXMathSinus(animation);

    titleColor.Red = (0.2);
    titleColor.Green = (-xx) * 0.4;
    titleColor.Blue = (xx);

    animation += 0.03;

#if 1
    PXMouse* const mouse = &bitFireEngine->WindowMain.MouseCurrentInput;


    PXGraphicPXUIElementTextSetAV(&_positionText, "Position : %3.2f", bitFireEngine->TimeFPS);

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