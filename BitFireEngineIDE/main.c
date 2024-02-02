#include <BFEngine.h>

#include <Math/PXMath.h>
#include <OS/Dialog/PXDialog.h>
#include <OS/Hardware/PXProcessor.h>

void PXAPI OnStartUpEvent(BFEngine* const bfEngine, PXEngine* const pxEngine);
void PXAPI OnShutDownEvent(BFEngine* const bfEngine, PXEngine* const pxEngine);
void PXAPI OnUserInputUpdate(BFEngine* const bfEngine, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo);
void PXAPI OnNetworkUpdate(BFEngine* const bfEngine, PXEngine* const pxEngine);
void PXAPI OnGameUpdateEvent(BFEngine* const bfEngine, PXEngine* const pxEngine);
void PXAPI OnRenderUpdateEvent(BFEngine* const bfEngine, PXEngine* const pxEngine);

#if defined(_DEBUG) && defined(OSWindows0)
#include <windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* name, int nShowCmd)
#else
int main(int amountOFParameters, char** parameter)
#endif
{
    BFEngine bfEngine;
    BFEngineConstruct(&bfEngine);

    bfEngine.OnStartUp = OnStartUpEvent;
    bfEngine.OnShutDown = OnShutDownEvent;
    bfEngine.Engine.OnUserUpdate = OnUserInputUpdate;
    bfEngine.OnNetworkUpdate = OnNetworkUpdate;
    bfEngine.OnGameUpdate = OnGameUpdateEvent;
    bfEngine.OnRenderUpdate = OnRenderUpdateEvent;

    PXEngineStart(&bfEngine.Engine);

    while (PXEngineIsRunning(&bfEngine.Engine))
        PXEngineUpdate(&bfEngine.Engine);

    PXEngineStop(&bfEngine.Engine);

    return 0;
}

PXTexture2D _dialogBoxTexture;



// Frame A
PXUIElement* _panelMenuMainContainer;
PXUIElement* _panelMenuButtonFile;
PXUIElement* _panelMenuButtonFileText;
PXUIElement* _panelMenuButtonFileDropDownOpen;
PXUIElement* _panelMenuButtonFileDropDownSave;
PXUIElement* _panelMenuButtonEdit;
PXUIElement* _panelMenuButtonEditText;
PXUIElement* _panelMenuButtonView;
PXUIElement* _panelMenuButtonViewText;



PXUIElement* _panelMainContent;


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

// Frame Scene
PXInt32U _matrixModelID;
PXInt32U _matrixViewID;
PXInt32U _matrixProjectionID;
PXInt32U _materialTextureID;

PXShaderProgram _pxWorldGridShader;

PXShaderProgram _pxObjectShader;

PXCamera _worldCamera;
PXModel _worldGrid;
PXModel _vehicle;
PXModel _test;

PXSkyBox _sceneSkyBox;

const PXColorRGBAF titleMenuButtonTextColorReference = { 0.9, 0.9, 0.9, 1 };
const PXColorRGBAF titleMenuButtonReference = { 0.10, 0.10, 0.10, 1 };

const PXColorRGBAF buttonColor = { 0.1, 0.3, 0.5, 1 }; //  0.40f, 0.15f, 0.15f, 1
const PXColorRGBAF panelReference = { 0.0, 0.1, 0.2, 1 };
PXColorRGBAF titleColor = { 0.2, 0.2, 0.2, 1 };
const PXColorRGBAF textColor = { 0.8, 0.8, 0.8, 1 };
float animation = 0;

// Register world grid
const float vertexData[] =
{
    -1, 0,-1,
        1, 0,1,
    1, 0,-1,


     1, 0,1,
       -1, 0,-1,
    -1, 0,1,

};

const PXInt8U indexDATA[] =
{
    0,1,2,3,4,5
};

void PXAPI ButtonThingOnClick(PXUIElement* pxUIElement)
{
    PXText pxText;
    PXTextConstructBufferA(&pxText, 260);
    PXTextClear(&pxText);

    PXActionResult pxActionResult = PXDialogFileOpen(&pxText);

    printf("Path Selected: %s\n", pxText.TextA);
}

void PXAPI OnStartUpEvent(BFEngine* const bfEngine, PXEngine* const pxEngine)
{
    PXGraphic* const pxGraphic = &pxEngine->Graphic;

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


    //-----------------------------------------------------
    // Panel:Menu
    //-----------------------------------------------------
    PXGraphicUIElementCreate(pxGraphic, &_panelMenuMainContainer, 1, PXNull);
    PXGraphicUIElementTypeSet(pxGraphic, _panelMenuMainContainer, PXUIElementTypePanel);
    PXGraphicUIElementFlagSet(_panelMenuMainContainer, PXUIElementDecorative);
    _panelMenuMainContainer->ColorTintReference = &titleColor;
    PXUIElementSizeSet(_panelMenuMainContainer, 0.00, 1.95, 0.0, 0.00, PXUIElementPositionRelative);


    //-----------------------------------------------------
    // Panel:MainContent
    //-----------------------------------------------------
    PXGraphicUIElementCreate(pxGraphic, &_panelMenuButtonFile, 1, _panelMenuMainContainer);
    PXGraphicUIElementTypeSet(pxGraphic, _panelMenuButtonFile, PXUIElementTypeButton);
    PXGraphicUIElementFlagSet(_panelMenuButtonFile, PXUIElementNormal);
    _panelMenuButtonFile->ColorTintReference = &titleMenuButtonReference;
    PXUIElementSizeSet(_panelMenuButtonFile, 0.00, 0.00, 1.85, 0.00, PXUIElementPositionRelative);


    PXGraphicUIElementCreate(pxGraphic, &_panelMenuButtonFileText, 1, _panelMenuButtonFile);
    PXGraphicUIElementTypeSet(pxGraphic, _panelMenuButtonFileText, PXUIElementTypeText);
    PXGraphicUIElementFlagSet(_panelMenuButtonFileText, PXUIElementText);
    _panelMenuButtonFileText->ColorTintReference = &titleMenuButtonTextColorReference;
    PXGraphicPXUIElementTextSetA(_panelMenuButtonFileText, "File");
    PXUIElementSizeSet(_panelMenuButtonFileText, 0.00, 0.00, 0.00, 0.00, PXUIElementPositionRelative);
    _panelMenuButtonFileText->TextInfo.FontID = &DefaultFont;


#if 0
    PXGraphicUIElementCreate(pxGraphic, &_panelMenuButtonFileDropDownOpen, 1, _panelMenuButtonFileText);
    PXGraphicUIElementTypeSet(pxGraphic, _panelMenuButtonFileDropDownOpen, PXUIElementTypeDropDown);
    PXGraphicUIElementFlagSet(_panelMenuButtonFileDropDownOpen, PXUIElementDecorative);
    _panelMenuButtonFileDropDownOpen->ColorTintReference = &titleMenuButtonTextColorReference;
    PXUIElementSizeSet(_panelMenuButtonFileDropDownOpen, 0.00, 0.00, 0.00, 0.00, PXUIElementPositionRelative);
    _panelMenuButtonFileDropDownOpen->TextInfo.FontID = &DefaultFont;


    PXGraphicUIElementCreate(pxGraphic, &_panelMenuButtonFileDropDownSave, 1, _panelMenuButtonFileDropDownOpen);
    PXGraphicUIElementTypeSet(pxGraphic, _panelMenuButtonFileDropDownSave, PXUIElementTypeDropDown);
    PXGraphicUIElementFlagSet(_panelMenuButtonFileDropDownSave, PXUIElementDecorative);
    _panelMenuButtonFileDropDownSave->ColorTintReference = &titleMenuButtonTextColorReference;
    PXUIElementSizeSet(_panelMenuButtonFileDropDownSave, 0.00, 0.00, 0.00, 0.00, PXUIElementPositionRelative);
    _panelMenuButtonFileDropDownSave->TextInfo.FontID = &DefaultFont;
#endif




    PXGraphicUIElementCreate(pxGraphic, &_panelMenuButtonEdit, 1, _panelMenuMainContainer);
    PXGraphicUIElementTypeSet(pxGraphic, _panelMenuButtonEdit, PXUIElementTypeButton);
    PXGraphicUIElementFlagSet(_panelMenuButtonEdit, PXUIElementNormal);
    _panelMenuButtonEdit->ColorTintReference = &titleMenuButtonReference;
    PXUIElementSizeSet(_panelMenuButtonEdit, 0.15, 0.00, 1.65, 0.00, PXUIElementPositionRelative);

    PXGraphicUIElementCreate(pxGraphic, &_panelMenuButtonEditText, 1, _panelMenuButtonEdit);
    PXGraphicUIElementTypeSet(pxGraphic, _panelMenuButtonEditText, PXUIElementTypeText);
    PXGraphicUIElementFlagSet(_panelMenuButtonEditText, PXUIElementText);
    _panelMenuButtonEditText->ColorTintReference = &titleMenuButtonTextColorReference;
    PXGraphicPXUIElementTextSetA(_panelMenuButtonEditText, "Edit");
    PXUIElementSizeSet(_panelMenuButtonEditText, 0.00, 0.00, 0.00, 0.00, PXUIElementPositionRelative);
    _panelMenuButtonEditText->TextInfo.FontID = &DefaultFont;



    PXGraphicUIElementCreate(pxGraphic, &_panelMenuButtonView, 1, _panelMenuMainContainer);
    PXGraphicUIElementTypeSet(pxGraphic, _panelMenuButtonView, PXUIElementTypeButton);
    PXGraphicUIElementFlagSet(_panelMenuButtonView, PXUIElementNormal);
    _panelMenuButtonView->ColorTintReference = &titleMenuButtonReference;
    PXUIElementSizeSet(_panelMenuButtonView, 0.35, 0.00, 1.45, 0.00, PXUIElementPositionRelative);

    PXGraphicUIElementCreate(pxGraphic, &_panelMenuButtonViewText, 1, _panelMenuButtonView);
    PXGraphicUIElementTypeSet(pxGraphic, _panelMenuButtonViewText, PXUIElementTypeText);
    PXGraphicUIElementFlagSet(_panelMenuButtonViewText, PXUIElementText);
    _panelMenuButtonViewText->ColorTintReference = &titleMenuButtonTextColorReference;
    PXGraphicPXUIElementTextSetA(_panelMenuButtonViewText, "View");
    PXUIElementSizeSet(_panelMenuButtonViewText, 0, 0, 0, 0, PXUIElementPositionRelative);
    _panelMenuButtonViewText->TextInfo.FontID = &DefaultFont;





    //-----------------------------------------------------
    // Panel:MainContent
    //-----------------------------------------------------
    PXGraphicUIElementCreate(pxGraphic, &_panelMainContent, 1, PXNull);
    PXGraphicUIElementTypeSet(pxGraphic, _panelMainContent, PXUIElementTypePanel);
    PXGraphicUIElementFlagSet(_panelMainContent, PXUIElementDecorative);
    _panelMainContent->ColorTintReference = &panelReference;
    PXUIElementSizeSet(_panelMainContent, 0.00, 0, 0.0, 0.05, PXUIElementPositionRelative);

    //-----------------------------------------------------
    // Panel:Assets
    //-----------------------------------------------------
    PXGraphicUIElementCreate(pxGraphic, &_uiSceneElements, 1, _panelMainContent);
    PXGraphicUIElementTypeSet(pxGraphic, _uiSceneElements, PXUIElementTypePanel);
    PXGraphicUIElementFlagSet(_uiSceneElements, PXUIElementDecorative);
    _uiSceneElements->ColorTintReference = &panelReference;
    PXUIElementSizeSet(_uiSceneElements, 0.02, 0.02, 1.65, 0.02, PXUIElementPositionRelative);
    //-----------------------------------------------------
    // Panel:Assets:TitleBar
    //-----------------------------------------------------
    PXGraphicUIElementCreate(pxGraphic, &_uiSceneElementsTitleBar, 1, _uiSceneElements);
    PXGraphicUIElementTypeSet(pxGraphic, _uiSceneElementsTitleBar, PXUIElementTypePanel);
    PXGraphicUIElementFlagSet(_uiSceneElementsTitleBar, PXUIElementNormal);
    _uiSceneElementsTitleBar->ColorTintReference = &titleColor;
    PXUIElementSizeSet(_uiSceneElementsTitleBar, 0.00, 1.85, 0.0, 0.00, PXUIElementPositionRelative);
    //-----------------------------------------------------
    // Panel:Assets:TitleBar:Text
    //-----------------------------------------------------    
    PXGraphicUIElementCreate(pxGraphic, &_uiSceneElementsTitleBarText, 1, _uiSceneElementsTitleBar);
    PXGraphicUIElementTypeSet(pxGraphic, _uiSceneElementsTitleBarText, PXUIElementTypeText);
    PXGraphicUIElementFlagSet(_uiSceneElementsTitleBarText, PXUIElementText);
    _uiSceneElementsTitleBarText->ColorTintReference = &textColor;
    PXUIElementSizeSet(_uiSceneElementsTitleBarText, 0.005, 0.005, 0.005, 0.005, PXUIElementPositionRelative);
    PXGraphicPXUIElementTextSetA(_uiSceneElementsTitleBarText, "Scene");
    _uiSceneElementsTitleBarText->TextInfo.FontID = &DefaultFont;



    //-----------------------------------------------------
    // Button
    //-----------------------------------------------------
    PXGraphicUIElementCreate(pxGraphic, &_infoPanelTextSpawn, 1, _uiSceneElements);
    PXGraphicUIElementTypeSet(pxGraphic, _infoPanelTextSpawn, PXUIElementTypeButton);
    PXGraphicUIElementFlagSet(_infoPanelTextSpawn, PXUIElementNormal);
    PXUIElementColorSet4F(&_infoPanelTextSpawn, 0.40f, 0.15f, 0.15f, 1);
    PXUIElementSizeSet(_infoPanelTextSpawn, 0.025, 0.05, 0.025, 1.8, PXUIElementPositionRelative);
    _infoPanelTextSpawn->ColorTintReference = &buttonColor;
    _infoPanelTextSpawn->OnClickCallback = ButtonThingOnClick;

    //-----------------------------------------------------
    // Button:Text
    //-----------------------------------------------------
    PXGraphicUIElementCreate(pxGraphic, &_infoPanelButtonText, 1, _infoPanelTextSpawn);
    PXGraphicUIElementTypeSet(pxGraphic, _infoPanelButtonText, PXUIElementTypeText);
    PXGraphicUIElementFlagSet(_infoPanelButtonText, PXUIElementText);
    PXUIElementSizeSet(_infoPanelButtonText, 0.005, 0.005, 0.005, 0.005, PXUIElementPositionRelative);
    PXGraphicPXUIElementTextSetA(_infoPanelButtonText, "Button");
    _infoPanelButtonText->TextInfo.FontID = &DefaultFont;
    _infoPanelButtonText->ColorTintReference = &textColor;


#if 1
    PXGraphicUIElementCreate(pxGraphic, &_infoPanelText, 1, _infoPanelTextSpawn);
    PXGraphicUIElementTypeSet(pxGraphic, _infoPanelText, PXUIElementTypeText);
    PXGraphicUIElementFlagSet(_infoPanelText, PXUIElementText);
    // PXUIElementFontSet(&_infoPanelText, &DefaultFont);
    PXUIElementColorSet4F(_infoPanelText, 0.5, 0.5, 0.5, 1);
    PXUIElementSizeSet(_infoPanelText, 0.02, 0.02, 0.02, 0.02, PXUIElementPositionRelative);
    //PXUIElementTextSetA(&_infoPanelText, "Button");
  //  PXGraphicUIElementRegister(pxGraphic, &_infoPanelText);


    // Panel: Scene
    PXGraphicUIElementCreate(pxGraphic, &_uiPanelScene, 1, _panelMainContent);
    PXGraphicUIElementTypeSet(pxGraphic, _uiPanelScene, PXUIElementTypePanel);
    _uiPanelScene->ColorTintReference = &panelReference;
    PXUIElementSizeSet(_uiPanelScene, 0.36, 0.02, 0.36, 0.02, PXUIElementPositionRelative);
    //  PXUIElementTextSetA(&_uiPanelScene, "Scene");
    // PXUIElementFontSet(&_uiPanelScene, &DefaultFont);
   // PXGraphicUIElementRegister(pxGraphic, &_uiPanelScene);

    // RenderFrame: Scene
    PXGraphicUIElementCreate(pxGraphic, &_uiSceneTexturePanel, 1, _uiPanelScene);
    PXGraphicUIElementTypeSet(pxGraphic, _uiSceneTexturePanel, PXUIElementTypeRenderFrame);
    PXGraphicUIElementFlagSet(_uiSceneTexturePanel, PXUIElementDecorative);
    PXUIElementSizeSet(_uiSceneTexturePanel, 0.05, 0.05, 0.05, 0.05, PXUIElementPositionRelative);
    //  PXUIElementFontSet(&_uiSceneTexturePanel, &DefaultFont);
   // _uiSceneTexturePanel.TextureReference = &_testImage;
   // _uiSceneTexturePanel.FrameRenderTextureReference = &_uiSceneTexture;
   // PXGraphicUIElementRegister(pxGraphic, &_uiSceneTexturePanel);
    //_textureTestA.TextureID = _testImage.ID;


     // Panel:Info
    PXGraphicUIElementCreate(pxGraphic, &_uiInfoPanel, 1, _panelMainContent);
    PXGraphicUIElementTypeSet(pxGraphic, _uiInfoPanel, PXUIElementTypePanel);
    PXGraphicUIElementFlagSet(_uiInfoPanel, PXUIElementDecorative);
    _uiInfoPanel->ColorTintReference = &panelReference;
    PXUIElementSizeSet(_uiInfoPanel, 1.65, 0.02, 0.02, 0.02, PXUIElementPositionRelative);
    //  PXUIElementTextSetA(&_uiInfoPanel, "Info");
    //  PXUIElementFontSet(&_uiInfoPanel, &DefaultFont);
 //   PXGraphicUIElementRegister(pxGraphic, &_uiInfoPanel);

         // TitleBar:Infol
    PXGraphicUIElementCreate(pxGraphic, &_uiInfoPanelTitleBar, 1, _uiInfoPanel);
    PXGraphicUIElementTypeSet(pxGraphic, _uiInfoPanelTitleBar, PXUIElementTypePanel);
    PXGraphicUIElementFlagSet(_uiInfoPanelTitleBar, PXUIElementNormal);
    _uiInfoPanelTitleBar->ColorTintReference = &titleColor;
    PXUIElementSizeSet(_uiInfoPanelTitleBar, 0.00, 1.85, 0.0, 0.00, PXUIElementPositionRelative);

    PXGraphicUIElementCreate(pxGraphic, &_uiInfoPanelTitleBarText, 1, _uiInfoPanelTitleBar);
    PXGraphicUIElementTypeSet(pxGraphic, _uiInfoPanelTitleBarText, PXUIElementTypeText);
    PXGraphicUIElementFlagSet(_uiInfoPanelTitleBarText, PXUIElementText);
    PXUIElementColorSet4F(_uiInfoPanelTitleBarText, 1, 1, 1, 1);
    PXUIElementSizeSet(_uiInfoPanelTitleBarText, 0.005, 0.005, 0.005, 0.005, PXUIElementPositionRelative);
    PXGraphicPXUIElementTextSetA(_uiInfoPanelTitleBarText, "Info");
    _uiInfoPanelTitleBarText->TextInfo.FontID = &DefaultFont;
    _uiInfoPanelTitleBarText->ColorTintReference = &textColor;
#endif

    //  PXUIElementTextSetA(&_uiInfoPositionText, "Position");
    //  PXUIElementFontSet(&_uiInfoPositionText, &DefaultFont);
   // PXGraphicUIElementRegister(pxGraphic, &_uiInfoPositionText);






    // Load model
    {
        pxEngine->Graphic.ShaderProgramCreateFromFileVPA
        (
            pxEngine->Graphic.EventOwner,
            &_pxObjectShader,
            "Shader/Object_Vertex.glsl",
            "Shader/Object_Fragment.glsl"
        );


#if 1
        PXModelConstruct(&_vehicle);

        PXResourceLoadA(&_vehicle, "Model/Dust_II/DustII.obj"); // "Model/Tiger.obj" "Model/Dust_II/DustII.obj", "Model/Tiger.obj", "H:/Daten/Objects/Moze/Moze.obj"

        PXMatrix4x4FScaleBy(&_vehicle.ModelMatrix, 2);

        pxGraphic->ModelRegister(pxGraphic->EventOwner, &_vehicle);

        _vehicle.ShaderProgramReference = &_pxObjectShader;
#endif



#if 0

        PXModelConstruct(&_test);

        PXResourceLoadA(&_test, "Model/dontut.obj");

        PXMatrix4x4FScaleBy(&_test.ModelMatrix, 1);

        pxGraphic->ModelRegister(pxGraphic->EventOwner, &_test);

        _test.ShaderProgramReference = &_pxObjectShader;
#endif
        
       

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



//PXGraphicTextureLoadA(pxGraphic, &_dialogBoxTexture, (char*)"C:\\Users\\BitPaw\\Videos\\SquareBlue.png");

    PXGraphicSkyboxRegisterA
    (
        pxGraphic,
        &_sceneSkyBox,
        "Shader/SkyBox_Vertex.glsl",
        "Shader/SkyBox_Fragment.glsl",
        "Texture/SkyBox_Side.png",
        "Texture/SkyBox_Side.png",
        "Texture/SkyBox_Top.png",
        "Texture/SkyBox_Bottom.png",
        "Texture/SkyBox_Side.png",
        "Texture/SkyBox_Side.png"
    );

    bfEngine->DefaultSkyBox = &_sceneSkyBox;






    PXModelConstruct(&_worldGrid);
    _worldGrid.VertexBuffer.VertexDataSize = sizeof(vertexData);
    _worldGrid.VertexBuffer.VertexData = vertexData;
    _worldGrid.VertexBuffer.Format = PXVertexBufferFormatXYZ;
    _worldGrid.VertexBuffer.VertexDataRowSize = 3 * sizeof(float);

    _worldGrid.IndexBuffer.IndexTypeSize = 1;
    _worldGrid.IndexBuffer.IndexData = indexDATA;
    _worldGrid.IndexBuffer.IndexDataSize = sizeof(indexDATA);
    _worldGrid.IndexBuffer.IndexDataAmount = sizeof(indexDATA) / sizeof(PXInt8U);
    _worldGrid.IndexBuffer.DataType = PXDataTypeInt08U;
    _worldGrid.IndexBuffer.DrawModeID = PXDrawModeIDTriangle; // PXDrawModeIDPoint | PXDrawModeIDLine;


    pxEngine->Graphic.ModelRegister(pxEngine->Graphic.EventOwner, &_worldGrid);


    pxEngine->Graphic.ShaderProgramCreateFromFileVPA
    (
        pxEngine->Graphic.EventOwner,
        &_pxWorldGridShader,
        "Shader/WorldGrid_Vertex.glsl",
        "Shader/WorldGrid_Fragment.glsl"
    );
    _worldGrid.ShaderProgramReference = &_pxWorldGridShader;
    _worldGrid.RenderBothSides = PXTrue;

    PXMatrix4x4FScaleBy(&_worldGrid.ModelMatrix, 1000);

    PXCameraConstruct(&_worldCamera);

}

void PXAPI OnShutDownEvent(BFEngine* const bfEngine, PXEngine* const pxEngine)
{

}

void PXAPI OnUserInputUpdate(BFEngine* const bfEngine, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo)
{
    PXWindow* pxWindow = &pxEngine->Window;
    PXKeyBoard* keyboard = &pxWindow->KeyBoardCurrentInput;
    PXMouse* mouse = &pxWindow->MouseCurrentInput;

#if 0
    if (keyboard.F.IsShortPressed())
    {
        keyboard.F.Value = 0xFF;

        if (_sign.Interactable)
        {
            printf("[Event] Clicked Sign\n");
        }
    }
#endif

    PXControllerDataGet(&bfEngine->Controller);

    //printf("%6i, %6i\n", bitFireEngine->Controller.Axis[0], bitFireEngine->Controller.Axis[1]);

    //_playerCharacterLuna.MatrixModel.Move(movement);


    if (pxPlayerMoveInfo->IsWindowInFocus && (IsPressedButtonLeft(mouse->Buttons) && IsPressedButtonLeft(mouse->ButtonsDelta)))
    {
        if (bfEngine->CollisionCheckInfo.CurrentElement)
        {
            PXFunctionInvoke(bfEngine->CollisionCheckInfo.CurrentElement->OnClickCallback, bfEngine->CollisionCheckInfo.CurrentElement);
        }
    }

    const PXBool isMouseInputWanted = pxPlayerMoveInfo->IsWindowInFocus && IsPressedButtonRight(mouse->Buttons);

    pxPlayerMoveInfo->ActionCommit = isMouseInputWanted;
}

void PXAPI OnNetworkUpdate(BFEngine* const bfEngine, PXEngine* const pxEngine)
{

}

void PXAPI OnGameUpdateEvent(BFEngine* const bfEngine, PXEngine* const pxEngine)
{








    float xx = PXMathSinus(animation);

    titleColor.Red = (0.2);
    titleColor.Green = (-xx) * 0.4;
    titleColor.Blue = (xx);

    animation += 0.01;

#if 1


    // PXGraphicPXUIElementTextSetAV(&_positionText, "Position : %3.2f", pxEngine->FramesPerSecound);

   // float x = mouse->Delta[0];
   // float y = mouse->Delta[1];

    // sprintf_s(_infoPanelText.Name, 32, "Mouse Pos x:%6.3f y:%6.3f", x, y);

    PXText pxText;
    PXTextConstructBufferA(&pxText, 64);

    //PXTextPrint(&pxText, "[BitFireEngine] Mouse: X:%6.4f, Y:%6.4f", x, y);

    const char* date = __DATE__;
    const char* time = __TIME__;

    PXInt32U cpuTemp = 0;

    PXProcessorTemperature(&cpuTemp);

    PXTextPrint(&pxText, "[BitFireEngine] (Build:%s %s) FPS:%-3i CPU:%i°C", date, time, pxEngine->FramesPerSecound, cpuTemp);

    PXWindowTitleSet(&pxEngine->Window, &pxText);




#endif
}

void PXAPI OnRenderUpdateEvent(BFEngine* const bfEngine, PXEngine* const pxEngine)
{
    PXCameraFollow(pxEngine->CameraCurrent, 0.05);

    // Grid
    pxEngine->Graphic.ModelDraw(pxEngine->Graphic.EventOwner, &_worldGrid, pxEngine->CameraCurrent);

    // Tank
    pxEngine->Graphic.ModelDraw(pxEngine->Graphic.EventOwner, &_vehicle, pxEngine->CameraCurrent);
}