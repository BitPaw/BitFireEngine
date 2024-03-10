#include <BFEngine.h>

#include <Math/PXMath.h>
#include <OS/Dialog/PXDialog.h>
#include <OS/Hardware/PXProcessor.h>
#include <OS/Memory/PXMemory.h>
#include <OS/Console/PXConsole.h>
#include <OS/UI/PXUI.h>
#include <OS/Graphic/PXGraphic.h>

#if 1
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#pragma comment(lib, "Comctl32.lib")
#endif



int _fltused = 0;


PXEngine pxEngineScene;

void PXAPI OnStartUpEvent(BFEngine* const bfEngine, PXEngine* const pxEngine);
void PXAPI OnShutDownEvent(BFEngine* const bfEngine, PXEngine* const pxEngine);
void PXAPI OnUserInputUpdate(BFEngine* const bfEngine, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo);
void PXAPI OnNetworkUpdate(BFEngine* const bfEngine, PXEngine* const pxEngine);
void PXAPI OnGameUpdateEvent(BFEngine* const bfEngine, PXEngine* const pxEngine);
void PXAPI OnRenderUpdateEvent(BFEngine* const bfEngine, PXEngine* const pxEngine);
void PXAPI PXOnEngineResourceAdded(void* const owner, PXEngine* const pxEngine, PXEngineResourceCreateInfo* const pxEngineResourceCreateInfo);

#if OSWindows

#include <windows.h>

#if _DEBUG || 1
int main()
#else _DEBUG
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* name, int nShowCmd)
#endif
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




    PXTextCopyA("BitFireEngine", 14, &bfEngine.Engine.ApplicationName, 64);

    bfEngine.Engine.ResourceAdded = PXOnEngineResourceAdded;

    // Start
    {
        PXEngineStartInfo pxEngineStartInfo;
        PXClear(PXEngineStartInfo, &pxEngineStartInfo);
        pxEngineStartInfo.Mode = PXGraphicInitializeModeOSGUI;
        pxEngineStartInfo.System = PXGraphicSystemOpenGL;

        PXEngineStart(&bfEngine.Engine, &pxEngineStartInfo);
    }

    while(PXEngineIsRunning(&bfEngine.Engine))
    {
        PXEngineUpdate(&bfEngine.Engine);
        PXEngineUpdate(&pxEngineScene);
    }      

    PXEngineStop(&bfEngine.Engine);

    return 0;
}

PXTexture2D* _dialogBoxTexture = 0;


// Scene
PXUIElement* _panelSceneViewRender = 0;

// Frame A
PXUIElement* _panelMenuMainContainer = 0;
PXUIElement* _panelMenuButtonFile = 0;
PXUIElement* _panelMenuButtonFileText = 0;
PXUIElement* _panelMenuTreeView = 0;
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

void PXAPI ButtonThingOnClick(PXUIElementOnClickInfo* const pxUIElementOnClickInfo)
{
    PXText pxText;
    PXTextConstructBufferA(&pxText, 260);
    PXTextClear(&pxText);

    PXDialogSystem pxDialogSystem;

    PXDialogSystemInitialize(&pxDialogSystem);

    PXActionResult pxActionResult = PXDialogFileOpen(&pxDialogSystem, &pxText);

    PXLogPrint
    (
        PXLoggingInfo,
        "BF",
        "Event",
        "Click: Path select:%s",
        pxText.TextA
    );

    PXDialogSystemRelease(&pxDialogSystem);

}

 void PXAPI PXOnEngineResourceAdded(void* const owner, PXEngine* const pxEngine, PXEngineResourceCreateInfo* const pxEngineResourceCreateInfo)
{
#if 0
     if(!_panelMenuTreeView)
     {
         return;
     }

     PXUIElementUpdateInfo pxUIElementUpdateInfo;
     pxUIElementUpdateInfo.UIElementReference = _panelMenuTreeView;
     pxUIElementUpdateInfo.WindowReference = &pxEngine->Window;
     pxUIElementUpdateInfo.Property = PXUIElementPropertyItemAdd;

     PXUIElementUpdateOSStyle(&pxUIElementUpdateInfo);

     PXLogPrint
     (
         PXLoggingInfo,
         "BF",
         "ADD",
         "XXXXXXXXXXXXX"
     );
#endif
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
        pxUIElementCreateData.Name = "Menu";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.41f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.02f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.41f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.02f;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Panel:MainContent
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.Name = "Menu";
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonFile;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuMainContainer;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.005;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.005;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.005;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 1.90;
        pxUIElementCreateData.UIElement.Position.Height = 35;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


    //-----------------------------------------------------
    // Panel::Scene::Text
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.Name = "Titel";
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonFileText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuButtonFile;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.TextInfo.Content = "Scene";
        pxUIElementCreateData.UIElement.TextInfo.FontID = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    //-----------------------------------------------------
    // Panel::Scene::Render
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.Name = "SceneRender";
        pxUIElementCreateData.ObjectReference = &_dialogBoxTexture;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeRenderFrame;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuMainContainer;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.005;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.105;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.005;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.005;
        pxUIElementCreateData.UIElement.SceneRender.Engine = &pxEngineScene;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

        pxEngineScene.OnRenderUpdate = OnRenderUpdateEvent;
       // pxEngineScene.OnStartUp = OnStartUpEvent;
       // pxEngineScene.OnShutDown = OnShutDownEvent;
        //pxEngineScene.OnUserUpdate = OnUserInputUpdate;
        pxEngineScene.OnNetworkUpdate = OnNetworkUpdate;
        pxEngineScene.OnGameUpdate = OnGameUpdateEvent;
        pxEngineScene.OnRenderUpdate = OnRenderUpdateEvent;
    }

    //-----------------------------------------------------
    // ???
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.Name = "Button A";
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonEdit;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuMainContainer;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.5f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.5f;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    //-----------------------------------------------------
    // ???
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.Name = "Edit";
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonEditText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.Paranet = _panelMenuButtonEdit;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.TextInfo.Content = "Edit";
        pxUIElementCreateData.UIElement.TextInfo.FontID = DefaultFont;

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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.35f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 1.45f;

       // PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.TextInfo.Content = "View";
        pxUIElementCreateData.UIElement.TextInfo.FontID = DefaultFont;

      //  PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.05f;

       // PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    //-----------------------------------------------------
    // Panel:Assets (Left one)
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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.02f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.02f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 1.60f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.02f;

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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 1.90f;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Panel:Assets:TitleBar:Text
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.Name = "Info";
        pxUIElementCreateData.ObjectReference = &_uiSceneElementsTitleBarText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.ColorTintReference = &textColor;
        pxUIElementCreateData.UIElement.Paranet = _uiSceneElementsTitleBar;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.005f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.005f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.005f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.005f;
        pxUIElementCreateData.UIElement.TextInfo.Content = "Objects";
        pxUIElementCreateData.UIElement.TextInfo.FontID = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    //-----------------------------------------------------
    // Panel::Scene::Render
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.Name = "Loaded Objects";
        pxUIElementCreateData.ObjectReference = &_panelMenuTreeView;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTreeView;
        pxUIElementCreateData.UIElement.Paranet = _uiSceneElements;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.005;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.1;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.005;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.305;

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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.02f;    
        pxUIElementCreateData.UIElement.Position.MarginTop = 1.8f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.02f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.02f;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.ButtonInfo.OnClickCallback = ButtonThingOnClick;

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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.005f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.005f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.005f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.005f;
        pxUIElementCreateData.UIElement.TextInfo.Content = "Load";
        pxUIElementCreateData.UIElement.TextInfo.FontID = DefaultFont;

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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.02f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.02f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.02f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.02f;
        pxUIElementCreateData.UIElement.TextInfo.Content = "Button";
        pxUIElementCreateData.UIElement.TextInfo.FontID = DefaultFont;

       // PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.36f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.02f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.36f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.02f;

      //  PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.05f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.05f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.05f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.05f;

       // PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignRight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 1.6f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.02f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.02f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.02f;

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
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 1.90f;

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
        pxUIElementCreateData.UIElement.ColorTintReference = &textColor;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.Paranet = _uiInfoPanelTitleBar;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.005f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.005f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.005f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.005f;
        pxUIElementCreateData.UIElement.TextInfo.Content = "Info";
        pxUIElementCreateData.UIElement.TextInfo.FontID = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }




    // DOne UI Stuff

    // Load data for UI
    {
        PXDictionary* const uiElementLookup = &pxEngine->UIElementLookUp;

        void* previousItem = 0;

        PXSize sixed = uiElementLookup->EntryAmountCurrent;

        PXUIElement* uiElementLast = PXNull;
        PXUIElement* uiElementItemLast = PXNull;
        PXBool isChild = PXFalse;

        for(PXSize i = 0; i < sixed; ++i)
        {
            PXDictionaryEntry pxDictionaryEntry;
            PXUIElement* uiElement = PXNull;

            PXDictionaryIndex(uiElementLookup, i, &pxDictionaryEntry);

            uiElement = *(PXUIElement**)pxDictionaryEntry.Value;


            // Check
            if(uiElementLast)
            {
                isChild = uiElement->Parent == uiElementLast;
            }
            uiElementLast = uiElement;
            

            PXUIElement* uiElementItem = PXNull;
    

            PXEngineResourceCreateInfo pxUIElementCreateData;
            PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
            pxUIElementCreateData.ObjectReference = &uiElementItem;
            pxUIElementCreateData.Name = uiElement->NameData;
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTreeViewItem;
            pxUIElementCreateData.UIElement.TreeViewItem.TreeView = _panelMenuTreeView;
            pxUIElementCreateData.UIElement.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

            if(isChild)
            {
                pxUIElementCreateData.UIElement.TreeViewItem.ItemParent = uiElementItemLast;
            }    

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

            uiElementItemLast = uiElementItem;

            
          //  PXUIElementUpdateInfo pxUIElementUpdateInfo;
           // pxUIElementUpdateInfo.UIElementReference = _panelMenuTreeView;
           // pxUIElementUpdateInfo.WindowReference = &pxEngine->Window;
           // pxUIElementUpdateInfo.Property = PXUIElementPropertyItemAdd;

           // PXUIElementUpdateOSStyle(&pxUIElementUpdateInfo);

          
        }
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

        PXEngineResourceCreate(&pxEngineScene, &pxUIElementCreateData);
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

       // PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

      


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

        PXEngineResourceCreate(&pxEngineScene, &pxSkyBoxCreateEventData);
        //bfEngine->DefaultSkyBox = _sceneSkyBox;
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
                
        PXFunctionInvoke(pxEngineScene.Graphic.ModelRegister, pxEngineScene.Graphic.EventOwner, _pxModelMapWorldGrid);

        _pxModelMapWorldGrid->Enabled = PXTrue;
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

        PXEngineResourceCreate(&pxEngineScene, &pxSkyBoxCreateEventData);

        _pxModelMapWorldGrid->ShaderProgramReference = _pxWorldGridShader;
        _pxModelMapWorldGrid->RenderBothSides = PXTrue;

        PXMatrix4x4FScaleBy(&_pxModelMapWorldGrid->ModelMatrix, 1000);
    }

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

    PXCameraRotateXYZ(pxEngine->CameraCurrent, 1.0f, 0.3, 0.83);
}

void PXAPI OnRenderUpdateEvent(BFEngine* const bfEngine, PXEngine* const pxEngine)
{
    PXCameraFollow(pxEngine->CameraCurrent, 0.05);


    {
        PXEngineResourceRenderInfo pxEngineResourceRenderInfo;
        pxEngineResourceRenderInfo.Type = PXEngineCreateTypeSkybox;
        pxEngineResourceRenderInfo.CameraReference = pxEngine->CameraCurrent;
        pxEngineResourceRenderInfo.ObjectReference = _sceneSkyBox;

        PXEngineResourceRender(pxEngine, &pxEngineResourceRenderInfo);
    }



    {
        PXEngineResourceRenderInfo pxEngineResourceRenderInfo;
        pxEngineResourceRenderInfo.Type = PXEngineCreateTypeModel;
        pxEngineResourceRenderInfo.CameraReference = pxEngine->CameraCurrent;
        pxEngineResourceRenderInfo.ObjectReference = _pxModelMapWorldGrid;

        PXEngineResourceRender(pxEngine, &pxEngineResourceRenderInfo);
    }



#if 0
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f( 1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex2f( 0.0f,  1.0f);
    glEnd();
#endif



    // Grid
    //pxEngine->Graphic.ModelDraw(pxEngine->Graphic.EventOwner, _pxModelMapWorldGrid, pxEngine->CameraCurrent);

    // Tank
    //pxEngine->Graphic.ModelDraw(pxEngine->Graphic.EventOwner, _pxModelMap, pxEngine->CameraCurrent);
}