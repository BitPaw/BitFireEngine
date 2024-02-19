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

PXTexture2D* _dialogBoxTexture = 0;



// Frame A
PXUIElement* _panelMenuMainContainer = 0;
PXUIElement* _panelMenuButtonFile = 0;
PXUIElement* _panelMenuButtonFileText = 0;
PXUIElement* _panelMenuButtonFileDropDownOpen = 0;
PXUIElement* _panelMenuButtonFileDropDownSave = 0;
PXUIElement* _panelMenuButtonEdit = 0;
PXUIElement* _panelMenuButtonEditText = 0;
PXUIElement* _panelMenuButtonView = 0;
PXUIElement* _panelMenuButtonViewText = 0;



PXUIElement* _panelMainContent = 0;


PXUIElement* _uiSceneElements = 0;
PXUIElement* _uiSceneElementsTitleBar = 0;
PXUIElement* _uiSceneElementsTitleBarText = 0;
PXUIElement* _uiPanelScene = 0;
PXUIElement* _uiSceneTexturePanel = 0;
PXTexture2D* _uiSceneTexture = 0;

PXUIElement* _uiInfoPanel = 0;
PXUIElement* _uiInfoPanelTitleBar = 0;
PXUIElement* _uiInfoPanelTitleBarText = 0;
PXUIElement* _uiInfoPositionText = 0;

PXUIElement* _infoPanelImage = 0;
PXUIElement* _infoPanelTextSpawn = 0;
PXUIElement* _infoPanelButtonText = 0;
PXUIElement* _infoPanelText = 0;
PXUIElement* _positionText = 0;
PXFont* DefaultFont;

PXUIElement* _textureTestA = 0;
PXTexture2D* _testImage = 0;
PXRenderable _pxRenderableModel;

// Frame Scene
PXInt32U _matrixModelID = 0;
PXInt32U _matrixViewID = 0;
PXInt32U _matrixProjectionID = 0;
PXInt32U _materialTextureID = 0;

PXShaderProgram* _pxWorldGridShader = 0;
PXShaderProgram* _pxObjectShader = 0;

PXCamera _worldCamera;
PXModel _pxModelMapWorldGridTrue;

PXModel* _pxModelMapWorldGrid = &_pxModelMapWorldGridTrue;
PXModel* _pxModelMap = 0;

PXSkyBox* _sceneSkyBox = 0;

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
    //-----------------------------------------------------
    // Main Font
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSkyBoxCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSkyBoxCreateEventData);
        pxSkyBoxCreateEventData.CreateType = PXEngineCreateTypeFont;
        pxSkyBoxCreateEventData.ObjectReference = &DefaultFont;
        pxSkyBoxCreateEventData.FilePath = "Font/A.fnt";
        //pxSkyBoxCreateEventData.Font.ShaderProgramCurrent = _worldShader;

        PXEngineResourceCreate(pxEngine, &pxSkyBoxCreateEventData);
    }


    //-----------------------------------------------------
    // Panel:Menu
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelMenuMainContainer;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.Y = 1.95f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Panel:MainContent
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonFile;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuMainContainer;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.Width = 1.85f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    //-----------------------------------------------------
    // Panel:MainContent
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonFileText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuButtonFile;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;
        pxUIElementCreateData.UIElement.Text = "File";
        pxUIElementCreateData.UIElement.FontReference = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

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



    //-----------------------------------------------------
    // ???
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonEdit;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuMainContainer;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.X = 0.15f;
        pxUIElementCreateData.UIElement.Width = 1.65f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    //-----------------------------------------------------
    // ???
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonEditText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuButtonEdit;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;
        pxUIElementCreateData.UIElement.Text = "Edit";
        pxUIElementCreateData.UIElement.FontReference = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // ???
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonView;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuMainContainer;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.X = 0.35f;
        pxUIElementCreateData.UIElement.Width = 1.45f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // ???
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonViewText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuButtonView;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;
        pxUIElementCreateData.UIElement.Text = "View";
        pxUIElementCreateData.UIElement.FontReference = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }




    //-----------------------------------------------------
    // Panel:MainContent
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelMainContent;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.ColorTintReference = &panelReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.Height = 0.05f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    //-----------------------------------------------------
    // Panel:Assets
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiSceneElements;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.ColorTintReference = &panelReference;
        pxUIElementCreateData.UIElement.Paranet = _panelMainContent;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.X = 0.02f;
        pxUIElementCreateData.UIElement.Y = 0.02f;
        pxUIElementCreateData.UIElement.Width = 1.65f;
        pxUIElementCreateData.UIElement.Height = 0.02f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Panel:Assets:TitleBar
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiSceneElementsTitleBar;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.ColorTintReference = &panelReference;
        pxUIElementCreateData.UIElement.Paranet = _uiSceneElements;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.Y = 1.85f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Panel:Assets:TitleBar:Text
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiSceneElementsTitleBarText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.ColorTintReference = &textColor;
        pxUIElementCreateData.UIElement.Paranet = _uiSceneElementsTitleBar;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.X = 0.005f;
        pxUIElementCreateData.UIElement.Y = 0.005f;
        pxUIElementCreateData.UIElement.Width = 0.005f;
        pxUIElementCreateData.UIElement.Height = 0.005f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;
        pxUIElementCreateData.UIElement.Text = "Scene";
        pxUIElementCreateData.UIElement.FontReference = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Button
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_infoPanelTextSpawn;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.ColorTintReference = &buttonColor;
        pxUIElementCreateData.UIElement.Paranet = _uiSceneElements;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.Color.Red = 0.40f;
        pxUIElementCreateData.UIElement.Color.Green = 0.15f;
        pxUIElementCreateData.UIElement.Color.Blue = 0.15f;
        pxUIElementCreateData.UIElement.Color.Alpha = 1.0f;
        pxUIElementCreateData.UIElement.X = 0.025f;
        pxUIElementCreateData.UIElement.Y = 0.05f;
        pxUIElementCreateData.UIElement.Width = 0.025f;
        pxUIElementCreateData.UIElement.Height = 1.8f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;
        pxUIElementCreateData.UIElement.OnClickCallback = ButtonThingOnClick;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Button:Text
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_infoPanelButtonText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.ColorTintReference = &textColor;
        pxUIElementCreateData.UIElement.Paranet = _infoPanelTextSpawn;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.X = 0.005f;
        pxUIElementCreateData.UIElement.Y = 0.005f;
        pxUIElementCreateData.UIElement.Width = 0.005f;
        pxUIElementCreateData.UIElement.Height = 0.005f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;
        pxUIElementCreateData.UIElement.Text = "Button";
        pxUIElementCreateData.UIElement.FontReference = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // ???
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_infoPanelText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.Paranet = _infoPanelTextSpawn;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.Color.Red = 0.5f;
        pxUIElementCreateData.UIElement.Color.Green = 0.5f;
        pxUIElementCreateData.UIElement.Color.Blue = 0.5f;
        pxUIElementCreateData.UIElement.Color.Alpha = 1.0f;
        pxUIElementCreateData.UIElement.X = 0.02f;
        pxUIElementCreateData.UIElement.Y = 0.02f;
        pxUIElementCreateData.UIElement.Width = 0.02f;
        pxUIElementCreateData.UIElement.Height = 0.02f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;
        pxUIElementCreateData.UIElement.Text = "Button";
        pxUIElementCreateData.UIElement.FontReference = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Panel: Scene
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiPanelScene;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.Paranet = _panelMainContent;
        pxUIElementCreateData.UIElement.ColorTintReference = &panelReference;
        pxUIElementCreateData.UIElement.X = 0.36f;
        pxUIElementCreateData.UIElement.Y = 0.02f;
        pxUIElementCreateData.UIElement.Width = 0.36f;
        pxUIElementCreateData.UIElement.Height = 0.02f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // RenderFrame: Scene
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiSceneTexturePanel;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeRenderFrame;
        pxUIElementCreateData.UIElement.Paranet = _uiPanelScene;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.X = 0.05f;
        pxUIElementCreateData.UIElement.Y = 0.05f;
        pxUIElementCreateData.UIElement.Width = 0.05f;
        pxUIElementCreateData.UIElement.Height = 0.05f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Panel:Info
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanel;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.Paranet = _panelMainContent;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.ColorTintReference = &panelReference;
        pxUIElementCreateData.UIElement.X = 1.65f;
        pxUIElementCreateData.UIElement.Y = 0.02f;
        pxUIElementCreateData.UIElement.Width = 0.02f;
        pxUIElementCreateData.UIElement.Height = 0.02f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // TitleBar:Infol
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelTitleBar;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.Paranet = _uiInfoPanel;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.X = 0.00f;
        pxUIElementCreateData.UIElement.Y = 1.85f;
        pxUIElementCreateData.UIElement.Width = 0.0f;
        pxUIElementCreateData.UIElement.Height = 0.0f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // _uiInfoPanelTitleBarText
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelTitleBarText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.Paranet = _uiInfoPanelTitleBar;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.ColorTintReference = &textColor;
        pxUIElementCreateData.UIElement.X = 0.005f;
        pxUIElementCreateData.UIElement.Y = 0.005f;
        pxUIElementCreateData.UIElement.Width = 0.005f;
        pxUIElementCreateData.UIElement.Height = 0.005f;
        pxUIElementCreateData.UIElement.PositionMode = PXUIElementPositionRelative;
        pxUIElementCreateData.UIElement.Text = "Info";
        pxUIElementCreateData.UIElement.FontReference = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Shader-Object
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeShaderProgram;
        pxUIElementCreateData.ObjectReference = &_pxObjectShader;
        pxUIElementCreateData.ShaderProgram.VertexShaderFilePath = "Shader/Object_Vertex.glsl";
        pxUIElementCreateData.ShaderProgram.PixelShaderFilePath = "Shader/Object_Fragment.glsl";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


    // Load model
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeModel;
        pxUIElementCreateData.ObjectReference = &_pxModelMap;
        pxUIElementCreateData.FilePath = "Model/Dust_II/DustII.obj";
        // "Model/Tiger.obj" 
        // "Model/Dust_II/DustII.obj"
        // "Model/Tiger.obj"
        // "Model/Moze.obj"
        pxUIElementCreateData.Model.ShaderProgramReference = _pxObjectShader;
        pxUIElementCreateData.Model.Scale = 2.0f;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

      


#if 0

        PXModelConstruct(&_test);

        PXResourceLoadA(&_test, "Model/dontut.obj");

        PXMatrix4x4FScaleBy(&_test.ModelMatrix, 1);

        pxGraphic->ModelRegister(pxGraphic->EventOwner, &_test);

        _test.ShaderProgramReference = &_pxObjectShader;
#endif
        
       

    }

   


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

    //-----------------------------------------------------
    // Skybox
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSkyBoxCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSkyBoxCreateEventData);
        pxSkyBoxCreateEventData.CreateType = PXEngineCreateTypeSkybox;
        pxSkyBoxCreateEventData.SpawnEnabled = PXTrue;
        pxSkyBoxCreateEventData.ObjectReference = &_sceneSkyBox;
        pxSkyBoxCreateEventData.SkyBox.SkyBoxShaderVertex = "Shader/SkyBox_Vertex.glsl";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxShaderPixel = "Shader/SkyBox_Fragment.glsl";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureA = "Texture/SkyBox_Side.png";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureB = "Texture/SkyBox_Side.png";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureC = "Texture/SkyBox_Top.png";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureD = "Texture/SkyBox_Bottom.png";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureE = "Texture/SkyBox_Side.png";
        pxSkyBoxCreateEventData.SkyBox.SkyBoxTextureF = "Texture/SkyBox_Side.png";

        PXEngineResourceCreate(&bfEngine->Engine, &pxSkyBoxCreateEventData);
        bfEngine->DefaultSkyBox = _sceneSkyBox;
    }

    //-----------------------------------------------------
    // Worldgrid-Model
    //-----------------------------------------------------
    {
        PXModelConstruct(_pxModelMapWorldGrid);
        _pxModelMapWorldGrid->VertexBuffer.VertexDataSize = sizeof(vertexData);
        _pxModelMapWorldGrid->VertexBuffer.VertexData = vertexData;
        _pxModelMapWorldGrid->VertexBuffer.Format = PXVertexBufferFormatXYZ;
        _pxModelMapWorldGrid->VertexBuffer.VertexDataRowSize = 3 * sizeof(float);

        _pxModelMapWorldGrid->IndexBuffer.IndexTypeSize = 1;
        _pxModelMapWorldGrid->IndexBuffer.IndexData = indexDATA;
        _pxModelMapWorldGrid->IndexBuffer.IndexDataSize = sizeof(indexDATA);
        _pxModelMapWorldGrid->IndexBuffer.IndexDataAmount = sizeof(indexDATA) / sizeof(PXInt8U);
        _pxModelMapWorldGrid->IndexBuffer.DataType = PXDataTypeInt08U;
        _pxModelMapWorldGrid->IndexBuffer.DrawModeID = PXDrawModeIDTriangle; // PXDrawModeIDPoint | PXDrawModeIDLine;

        pxEngine->Graphic.ModelRegister(pxEngine->Graphic.EventOwner, _pxModelMapWorldGrid);
    }

    //-----------------------------------------------------
    // Worldgrid-Shader
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxSkyBoxCreateEventData;
        PXClear(PXEngineResourceCreateInfo, &pxSkyBoxCreateEventData);
        pxSkyBoxCreateEventData.CreateType = PXEngineCreateTypeShaderProgram;
        pxSkyBoxCreateEventData.ObjectReference = &_pxWorldGridShader;
        pxSkyBoxCreateEventData.ShaderProgram.VertexShaderFilePath = "Shader/WorldGrid_Vertex.glsl";
        pxSkyBoxCreateEventData.ShaderProgram.PixelShaderFilePath = "Shader/WorldGrid_Fragment.glsl";

        PXEngineResourceCreate(pxEngine, &pxSkyBoxCreateEventData);

        _pxModelMapWorldGrid->ShaderProgramReference = _pxWorldGridShader;
        _pxModelMapWorldGrid->RenderBothSides = PXTrue;

        PXMatrix4x4FScaleBy(&_pxModelMapWorldGrid->ModelMatrix, 1000);
    }

    PXCameraConstruct(&_worldCamera);

    PXGraphicUIElementPrint(&pxEngine->Graphic);
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
    pxEngine->Graphic.ModelDraw(pxEngine->Graphic.EventOwner, _pxModelMapWorldGrid, pxEngine->CameraCurrent);

    // Tank
    pxEngine->Graphic.ModelDraw(pxEngine->Graphic.EventOwner, _pxModelMap, pxEngine->CameraCurrent);
}