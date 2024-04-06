
#include <Engine/PXEngine.h>
#include <Math/PXMath.h>
#include <OS/Dialog/PXDialog.h>
#include <OS/Hardware/PXProcessor.h>
#include <OS/Memory/PXMemory.h>
#include <OS/Console/PXConsole.h>
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



typedef struct BFBitFireIDE_
{
    PXEngine EngineScene;
    PXEngine EngineEditor;
}
BFBitFireIDE;


#define PXDefaultOffset 0.005f
#define PXDefaultTitleBar 28.0f


void PXAPI BFSceneOnStartup(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);


void PXAPI OnStartUpEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnShutDownEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnUserInputUpdate(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo);
void PXAPI OnNetworkUpdate(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnGameUpdateEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnRenderUpdateEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI PXOnEngineResourceAdded(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXEngineResourceCreateInfo* const pxEngineResourceCreateInfo);
void PXAPI PXOnUserInputUpdateScene(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo);

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
    BFBitFireIDE bfBitFireIDE;

    // Start
    {
        PXEngineStartInfo pxEngineStartInfo;
        PXClear(PXEngineStartInfo, &pxEngineStartInfo);
        pxEngineStartInfo.Mode = PXGraphicInitializeModeOSGUI;
        pxEngineStartInfo.System = PXGraphicSystemOpenGL;
        pxEngineStartInfo.OnStartUp = OnStartUpEvent;
        pxEngineStartInfo.OnShutDown = OnShutDownEvent;
        pxEngineStartInfo.OnUserUpdate = OnUserInputUpdate; // PXOnUserInputUpdateScene
        pxEngineStartInfo.OnNetworkUpdate = OnNetworkUpdate;
        pxEngineStartInfo.OnGameUpdate = OnGameUpdateEvent;
        pxEngineStartInfo.Name = "BitFireEngine";
        pxEngineStartInfo.Owner = &bfBitFireIDE;
        pxEngineStartInfo.UseMouseInput = PXTrue;

        PXEngineStart(&bfBitFireIDE.EngineEditor, &pxEngineStartInfo);
    }

    while(PXEngineIsRunning(&bfBitFireIDE.EngineEditor))
    {
        PXEngineUpdate(&bfBitFireIDE.EngineEditor);
        PXEngineUpdate(&bfBitFireIDE.EngineScene);
    }      

    PXEngineStop(&bfBitFireIDE.EngineEditor);

    return 0;
}

PXTexture2D* _dialogBoxTexture = 0;


// Scene
PXUIElement* _panelSceneViewRender = 0;

// Frame console
PXUIElement* _panelConsoleMain = 0;
PXUIElement* _panelConsoleTextContent = 0;
PXUIElement* _panelConsoleData = 0;

// Frame A
PXUIElement* _panelMenuMainContainer = 0;
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
PXUIElement* _uiSceneElementsTitleBarText = 0;
PXUIElement* _uiPanelScene = 0;
PXUIElement* _uiSceneTexturePanel = 0;
PXTexture2D* _uiSceneTexture = 0;

PXUIElement* _uiInfoPanelTitleBar = 0;
PXUIElement* _uiInfoPanelTitleBarText = 0;
PXUIElement* _uiInfoPositionText = 0;

PXUIElement* _uiInfoPanelObjectText = 0;
PXUIElement* _uiInfoPanelObjectName = 0;
PXUIElement* _uiInfoPanelObjectNameContent = 0;
PXUIElement* _uiInfoPanelObjectType = 0;
PXUIElement* _uiInfoPanelObjectTypeContent = 0;

PXUIElement* _infoPanelImage = 0;
PXUIElement* _infoPanelTextSpawn = 0;
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
PXShaderProgram* _pxGismoShader = 0;

PXCamera _worldCamera;
PXModel _pxModelMapWorldGridTrue;

PXModel* _pxModelMapWorldGrid = &_pxModelMapWorldGridTrue;
PXModel* _pxModelMap = 0;
PXModel* _pxGismo = 0;

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

#if 0
void PXAPI PXOnUIElementInteract(PXUIElementInteractInfo* const pxUIElementInteractInfo)
{
    switch(pxUIElementInteractInfo->Type)
    {
        case PXUIElementInteractTypeSelect:
        {
            PXUIElement* const uiElementSelected = pxUIElementInteractInfo->UIElementSelected;

            PXLogPrint
            (
                PXLoggingInfo,
                "BF",
                "Event",
                "Select: <%s>",
                pxUIElementInteractInfo->UIElementSelected->NameData
            );
            

            _uiInfoPanelObjectNameContent->TextInfo.Content = pxUIElementInteractInfo->UIElementSelected->NameData;

            const char* typeName = PXUIElementTypeToString(uiElementSelected->Type);

            _uiInfoPanelObjectTypeContent->TextInfo.Content = typeName;

            PXGUIElementUpdateInfo pxUIElementUpdateInfo[2];
            PXClearList(PXGUIElementUpdateInfo, pxUIElementUpdateInfo, 2);

            pxUIElementUpdateInfo[0].UIElement = _uiInfoPanelObjectNameContent;
            pxUIElementUpdateInfo[0].WindowReference = &pxEngineBF->Window;
            pxUIElementUpdateInfo[0].Property = PXUIElementPropertyTextContent;

            pxUIElementUpdateInfo[1].UIElement = _uiInfoPanelObjectTypeContent;
            pxUIElementUpdateInfo[1].WindowReference = &pxEngineBF->Window;
            pxUIElementUpdateInfo[1].Property = PXUIElementPropertyTextContent;

           // PXGUIElementUpdate(PXNull, pxUIElementUpdateInfo, 2);

            break;
        }
        case PXUIElementInteractTypeClick:
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

            break;
        }
    }
}
#endif

void PXAPI PXOnUserInputUpdateScene(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo)
{
    PXLogPrint
    (
        PXLoggingInfo,
        "BF-IDE",
        "Add",
        "Input"
    );


    PXCameraRotateXYZ(pxEngine->CameraCurrent, pxPlayerMoveInfo->MovementView.X, pxPlayerMoveInfo->MovementView.Y, 0.0);
    PXCameraMove(pxEngine->CameraCurrent, &pxPlayerMoveInfo->MovementWalk);
    PXCameraUpdate(pxEngine->CameraCurrent, 1);

    /*

    PXLogPrint
    (
        PXLoggingInfo,
        "Math",
        "Matrix",
        "%",
    );*/


   //

  // PXCameraRotateXYZ(pxEngine->CameraCurrent, pxPlayerMoveInfo->MovementView.X, pxPlayerMoveInfo->MovementView.Y, 0);
  //  PXCameraMove(pxEngine->CameraCurrent, &pxPlayerMoveInfo->MovementWalk);
}

void PXAPI PXOnEngineResourceAdded(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXEngineResourceCreateInfo* const pxEngineResourceCreateInfo)
{
    PXLogPrint
    (
        PXLoggingInfo,
        "BF-IDE",
        "Add",
        "XXXXXXXXXXXXX"
    );

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

   
#endif
}

void PXAPI BFSceneOnStartup(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{
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
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeShaderProgram;
        pxUIElementCreateData.ObjectReference = &_pxGismoShader;
        pxUIElementCreateData.ShaderProgram.VertexShaderFilePath = "Shader/Gismo_Vertex.glsl";
        pxUIElementCreateData.ShaderProgram.PixelShaderFilePath = "Shader/Gismo_Fragment.glsl";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }




    // Load model
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeModel;
        pxUIElementCreateData.ObjectReference = &_pxModelMap;
       // pxUIElementCreateData.FilePath = "Model/Dust_II/DustII.obj";
       pxUIElementCreateData.FilePath = "Model/Dust_II/DustII.obj";
        // "Model/Tiger.obj" 
        // "Model/Dust_II/DustII.obj"
        // "Model/Tiger.obj"
        // "Model/Moze.obj"
        pxUIElementCreateData.Model.ShaderProgramReference = _pxObjectShader;
        pxUIElementCreateData.Model.Scale = 50.0f;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeModel;
        pxUIElementCreateData.ObjectReference = &_pxGismo;
        pxUIElementCreateData.FilePath = "Model/GismoTreeD.obj";
        pxUIElementCreateData.Model.ShaderProgramReference = _pxGismoShader;
        pxUIElementCreateData.Model.Scale = 3.0f;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
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

        PXEngineResourceCreate(pxEngine, &pxSkyBoxCreateEventData);
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

        PXFunctionInvoke(pxEngine->Graphic.ModelRegister, pxEngine->Graphic.EventOwner, _pxModelMapWorldGrid);

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

        PXEngineResourceCreate(pxEngine, &pxSkyBoxCreateEventData);

        _pxModelMapWorldGrid->ShaderProgramReference = _pxWorldGridShader;
        _pxModelMapWorldGrid->RenderBothSides = PXTrue;

        PXMatrix4x4FScaleBy(&_pxModelMapWorldGrid->ModelMatrix, 1000);
    }

    PXCameraConstruct(&_worldCamera);
}

void PXAPI OnStartUpEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
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
        pxUIElementCreateData.Name = "RenderScene";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.41f;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.41f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.54f;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


    //-----------------------------------------------------
    // Panel:Console
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelConsoleMain;
        pxUIElementCreateData.Name = "ConsoleLog";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.41f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 1.48f;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelConsoleTextContent;
        pxUIElementCreateData.Name = "Console-Text";
        pxUIElementCreateData.UIElement.UIElementParent = _panelConsoleMain;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Console";
        pxUIElementCreateData.UIElement.Data.Text.FontID = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
#if 1

#if 1
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelConsoleData;
        pxUIElementCreateData.Name = "Console Data";
        pxUIElementCreateData.UIElement.UIElementParent = _panelConsoleMain;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTextEdit;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.1f;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
#endif


    //-----------------------------------------------------
    // Panel::Scene::Text
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.Name = "RenderScene-Text";
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonFileText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _panelMenuMainContainer;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Scene";
        pxUIElementCreateData.UIElement.Data.Text.FontID = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    //-----------------------------------------------------
    // Panel::Scene::Render
    //-----------------------------------------------------
    {
        PXEngineStartInfo pxEngineStartInfo;
        PXClear(PXEngineStartInfo, &pxEngineStartInfo);

        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.Name = "SceneRender";
        pxUIElementCreateData.ObjectReference = &_dialogBoxTexture;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeRenderFrame;
        pxUIElementCreateData.UIElement.UIElementParent = _panelMenuMainContainer;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.105;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Data.SceneRender.Engine = &bfBitFireIDE->EngineScene;
        pxUIElementCreateData.UIElement.Data.SceneRender.StartInfo = &pxEngineStartInfo;
        pxUIElementCreateData.UIElement.Data.SceneRender.StartInfo->Owner = bfBitFireIDE;
        pxUIElementCreateData.UIElement.Data.SceneRender.StartInfo->System = PXGraphicSystemOpenGL;
        pxUIElementCreateData.UIElement.Data.SceneRender.StartInfo->OnStartUp = BFSceneOnStartup;
        pxUIElementCreateData.UIElement.Data.SceneRender.StartInfo->OnUserUpdate = PXOnUserInputUpdateScene;
        pxUIElementCreateData.UIElement.Data.SceneRender.StartInfo->OnRenderUpdate = OnRenderUpdateEvent;
        pxUIElementCreateData.UIElement.Data.SceneRender.StartInfo->OnGameUpdate = OnGameUpdateEvent;
        //pxUIElementCreateData.UIElement.Data.SceneRender.StartInfo->UseMouseInput = PXTrue;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

        // pxEngineScene.OnRenderUpdate = OnRenderUpdateEvent;
       // pxEngineScene.OnStartUp = OnStartUpEvent;
       // pxEngineScene.OnShutDown = OnShutDownEvent;
        //pxEngineScene.OnUserUpdate = OnUserInputUpdate;
       // pxEngineScene.OnNetworkUpdate = OnNetworkUpdate;
       // pxEngineScene.OnGameUpdate = OnGameUpdateEvent;
        // pxEngineScene.OnRenderUpdate = OnRenderUpdateEvent;
    }



#if 0
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
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.5f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.5f;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Edit";
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.FontID = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
#endif


    //-----------------------------------------------------
    // Panel:Objects (Left one)
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiSceneElements;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.ColorTintReference = &panelReference;
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;
       // pxUIElementCreateData.UIElement.UIElementParent = _panelMainContent;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginRight = 1.60f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }






    //-----------------------------------------------------
    // Panel:Objects:TitleBar:Text
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.Name = "Objects";
        pxUIElementCreateData.ObjectReference = &_uiSceneElementsTitleBarText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.ColorTintReference = &textColor;
        pxUIElementCreateData.UIElement.UIElementParent = _uiSceneElements;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Objects";
        pxUIElementCreateData.UIElement.Data.Text.FontID = DefaultFont;

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
        pxUIElementCreateData.UIElement.UIElementParent = _uiSceneElements;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.1;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.305;
       // pxUIElementCreateData.UIElement.InteractCallBack = PXOnUIElementInteract;

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
        pxUIElementCreateData.UIElement.UIElementParent = _uiSceneElements;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Color.Red = 0.40f;
        pxUIElementCreateData.UIElement.Color.Green = 0.15f;
        pxUIElementCreateData.UIElement.Color.Blue = 0.15f;
        pxUIElementCreateData.UIElement.Color.Alpha = 1.0f;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = 1.8f;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Load";
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.FontID = DefaultFont;

       // pxUIElementCreateData.UIElement.InteractCallBack = PXOnUIElementInteract;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }




    //-----------------------------------------------------
    // Panel::Info::Bar
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelTitleBar;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignRight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 1.6f;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.54f;
        pxUIElementCreateData.UIElement.Position.Height = 30.0f;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //-----------------------------------------------------
    // Panel::Info::Bar::Text
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelTitleBarText;
        pxUIElementCreateData.UIElement.ColorTintReference = &textColor;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _uiInfoPanelTitleBar;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Info";
        pxUIElementCreateData.UIElement.Data.Text.FontID = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


#if 0
    //-----------------------------------------------------
    // Panel::Info::Bar
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelObjectText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset + 0.1f;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Selected:";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelObjectName;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset + 0.2f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.25f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Name:";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelObjectNameContent;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.15f;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset + 0.2f;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Data.Text.Content = "XXXXX";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignLeft;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelObjectType;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset + 0.3f;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.25f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Type:";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelObjectTypeContent;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.55f;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset + 0.3f;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Data.Text.Content = "XXXXX";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignLeft;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
#endif





    // DOne UI Stuff

    {
        // Load data for UI
        {
            PXDictionary parentList;

            PXDictionaryConstruct(&parentList, sizeof(PXUIElement*), sizeof(PXUIElement*), PXDictionaryValueLocalityInternalEmbedded);

  
            PXDictionary* const uiElementLookup = &pxEngine->GUISystem.UIElementLookUp;

            void* previousItem = 0;

            PXSize sixed = uiElementLookup->EntryAmountCurrent;
        
            for(PXSize i = 0; i < sixed; ++i)
            {
                PXDictionaryEntry pxDictionaryEntry;
                PXUIElement* uiElement = PXNull;

                PXDictionaryIndex(uiElementLookup, i, &pxDictionaryEntry);

                uiElement = *(PXUIElement**)pxDictionaryEntry.Value;


                PXUIElement* uiElementItem = PXNull;

                PXEngineResourceCreateInfo pxUIElementCreateData;
                PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
                pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
                pxUIElementCreateData.ObjectReference = &uiElementItem;
                pxUIElementCreateData.Name = uiElement->NameData;
                pxUIElementCreateData.UIElement.Type = PXUIElementTypeTreeViewItem;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.ElementSource = uiElement;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.TreeView = _panelMenuTreeView;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                // Fetch parrant
                pxUIElementCreateData.UIElement.Data.TreeViewItem.ItemParent = PXNull;

                if(uiElement->Parent)
                {
                    PXUIElement* parentElement = PXNull;

                    const PXBool found = PXDictionaryFindEntry(&parentList, &uiElement->Parent, &parentElement);

                    if(found)
                    {
                        pxUIElementCreateData.UIElement.Data.TreeViewItem.ItemParent = parentElement;
                    }              
                }

                PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

                PXDictionaryAdd(&parentList, &uiElement, &uiElementItem);



                //  PXUIElementUpdateInfo pxUIElementUpdateInfo;
                 // pxUIElementUpdateInfo.UIElementReference = _panelMenuTreeView;
                 // pxUIElementUpdateInfo.WindowReference = &pxEngine->Window;
                 // pxUIElementUpdateInfo.Property = PXUIElementPropertyItemAdd;

                 // PXUIElementUpdateOSStyle(&pxUIElementUpdateInfo);


            }
        }


       

        // Add more?
    }


  



   

#endif
}

void PXAPI OnShutDownEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{

}

void PXAPI OnUserInputUpdate(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo)
{


#if 0
    PXWindow* pxWindow = &pxEngine->Window;
    PXKeyBoard* keyboard = &pxEngine->KeyBoardCurrentInput;
    PXMouse* mouse = &pxEngine->MouseCurrentInput;

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

    // PXControllerDataGet(&bfEngine->Controller);

    //printf("%6i, %6i\n", bitFireEngine->Controller.Axis[0], bitFireEngine->Controller.Axis[1]);

    //_playerCharacterLuna.MatrixModel.Move(movement);


    if (pxPlayerMoveInfo->IsWindowInFocus && (IsPressedButtonLeft(mouse->Buttons) && IsPressedButtonLeft(mouse->ButtonsDelta)))
    {
        if (bfEngine->CollisionCheckInfo.CurrentElement)
        {
#if 0
            PXUIElementInteractInfo pxUIElementInteractInfo;
            PXClear(PXUIElementInteractInfo, &pxUIElementInteractInfo);
            pxUIElementInteractInfo.UIElementSender = bfEngine->CollisionCheckInfo.CurrentElement;
            pxUIElementInteractInfo.Type = PXUIElementInteractTypeSelect;

            PXFunctionInvoke(bfEngine->CollisionCheckInfo.CurrentElement->InteractCallBack, &pxUIElementInteractInfo);
#endif
        }
    }

    const PXBool isMouseInputWanted = pxPlayerMoveInfo->IsWindowInFocus && IsPressedButtonRight(mouse->Buttons);

    pxPlayerMoveInfo->ActionCommit = isMouseInputWanted;
#endif
}

void PXAPI OnNetworkUpdate(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{

}

void PXAPI OnGameUpdateEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{
    float xx = PXMathSinus(animation);

    titleColor.Red = (0.2);
    titleColor.Green = (-xx) * 0.4;
    titleColor.Blue = (xx);

    animation += 0.01;

   // PXCameraRotateXYZ(bfBitFireIDE->EngineScene.CameraCurrent, 0.01, 0.5, 0.2);
  //  PXCameraUpdate(bfBitFireIDE->EngineScene.CameraCurrent, 1);
}

void PXAPI OnRenderUpdateEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{
#if 0
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f( 1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex2f( 0.0f,  1.0f);
    glEnd();
#endif
}