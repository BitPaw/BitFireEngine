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


void PXAPI BFObjectTreeViewEvent(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent);
void PXAPI BFObjectTreeViewUpdate(BFBitFireIDE* const bfBitFireIDE);
void PXAPI BFInfoSelectUpdate(BFBitFireIDE* const bfBitFireIDE);


void PXAPI BFSceneOnStartup(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);


void PXAPI OnStartUpEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnShutDownEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnUserInputUpdate(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo);
void PXAPI OnNetworkUpdate(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnGameUpdateEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnRenderUpdateEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI PXOnEngineResourceAdded(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, void* const pxEngineResourceCreateInfo);
void PXAPI PXOnUserInputUpdateScene(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo);

#if OSWindows

#include <windows.h>
#include <CommCtrl.h>

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
    PXClear(BFBitFireIDE, &bfBitFireIDE);

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



//---------------------------------------------------------
// Tab
//---------------------------------------------------------
PXUIElement* _tabControlMain = 0;
PXUIElement* _tabPageScene = 0;
PXUIElement* _tabPageSound = 0;
PXUIElement* _tabPageNetwork = 0;
PXUIElement* _tabPageVideo = 0;
PXUIElement* _tabPageDatabase = 0;
PXUIElement* _tabPageInput = 0;
//---------------------------------------------------------

//---------------------------------------------------------
// Scene
//---------------------------------------------------------

//---------------------------------------------------------

//---------------------------------------------------------
// Sound
//---------------------------------------------------------
PXAudioDevice _soundAudioDevice;
PXSound* _musicTest = 0;

PXUIElement* _buttonSoundPlay = 0;
PXUIElement* _buttonSoundStop = 0;


//---------------------------------------------------------
PXUIElement* _textSoundChorusEffect = 0;

PXUIElement* _textSoundChorusWetDryMix = 0;
PXUIElement* _textSoundChorusDepth = 0;
PXUIElement* _textSoundChorusFeedback = 0;
PXUIElement* _textSoundChorusFrequency = 0;
PXUIElement* _textSoundChorusWaveform = 0;
PXUIElement* _textSoundChorusDelay = 0;
PXUIElement* _textSoundChorusPhase = 0;

PXUIElement* _textSoundChorusWetDryMixInput = 0;
PXUIElement* _textSoundChorusDepthInput = 0;
PXUIElement* _textSoundChorusFeedbackInput = 0;
PXUIElement* _textSoundChorusFrequencyInput = 0;
PXUIElement* _textSoundChorusWaveformInput = 0;
PXUIElement* _textSoundChorusDelayInput = 0;
PXUIElement* _textSoundChorusPhaseInput = 0;

PXUIElement* _textSoundChorusEnable = 0;
PXUIElement* _textSoundChorusApply = 0;
//---------------------------------------------------------
PXUIElement* _textSoundCompressor = 0;

PXUIElement* _textSoundCompressorGain = 0;
PXUIElement* _textSoundCompressorAttack = 0;
PXUIElement* _textSoundCompressorRelease = 0;
PXUIElement* _textSoundCompressorThreshold = 0;
PXUIElement* _textSoundCompressorRatio = 0;
PXUIElement* _textSoundCompressorPredelay = 0;

PXUIElement* _textSoundCompressorGainInput = 0;
PXUIElement* _textSoundCompressorAttackInput = 0;
PXUIElement* _textSoundCompressorReleaseInput = 0;
PXUIElement* _textSoundCompressorThresholdInput = 0;
PXUIElement* _textSoundCompressorRatioInput = 0;
PXUIElement* _textSoundCompressorPredelayInput = 0;


PXUIElement* _textSoundCompressorEnable = 0;
PXUIElement* _textSoundCompressorApply = 0;
//---------------------------------------------------------
PXUIElement* _textSoundDistortion = 0;

PXUIElement* _textSoundDistortionGain = 0;
PXUIElement* _textSoundDistortionEdge = 0;
PXUIElement* _textSoundDistortionPostEQCenterFrequency = 0;
PXUIElement* _textSoundDistortionPostEQBandwidth = 0;
PXUIElement* _textSoundDistortionPreLowpassCutoff = 0;

PXUIElement* _textSoundDistortionGainInput = 0;
PXUIElement* _textSoundDistortionEdgeInput = 0;
PXUIElement* _textSoundDistortionPostEQCenterFrequencyInput = 0;
PXUIElement* _textSoundDistortionPostEQBandwidthInput = 0;
PXUIElement* _textSoundDistortionPreLowpassCutoffInput = 0;

PXUIElement* _textSoundDistortionEnable = 0;
PXUIElement* _textSoundDistortionApply = 0;

//---------------------------------------------------------
PXUIElement* _textSoundEchoEffect = 0;


PXUIElement* _textSoundEchoWetDryMix = 0;
PXUIElement* _textSoundEchoFeedback = 0;
PXUIElement* _textSoundEchoLeftDelay = 0;
PXUIElement* _textSoundEchoRightDelay = 0;
PXUIElement* _textSoundEchoPanDelay = 0;

PXUIElement* _textSoundEchoWetDryMixInput = 0;
PXUIElement* _textSoundEchoFeedbackInput = 0;
PXUIElement* _textSoundEchoLeftDelayInput = 0;
PXUIElement* _textSoundEchoRightDelayInput = 0;
PXUIElement* _textSoundEchoPanDelayInput = 0;

PXUIElement* _textSoundEchoEnable = 0;
PXUIElement* _textSoundEchoApply = 0;

//---------------------------------------------------------
PXUIElement* _textSoundFlangerEffect = 0;

PXUIElement* _textSoundFlangerWetDryMix = 0;
PXUIElement* _textSoundFlangerDepth = 0;
PXUIElement* _textSoundFlangerFeedback = 0;
PXUIElement* _textSoundFlangerFrequency = 0;
PXUIElement* _textSoundFlangerWaveform = 0;
PXUIElement* _textSoundFlangerDelay = 0;
PXUIElement* _textSoundFlangerPhase = 0;

PXUIElement* _textSoundFlangerWetDryMixInput = 0;
PXUIElement* _textSoundFlangerDepthInput = 0;
PXUIElement* _textSoundFlangerFeedbackInput = 0;
PXUIElement* _textSoundFlangerFrequencyInput = 0;
PXUIElement* _textSoundFlangerWaveformInput = 0;
PXUIElement* _textSoundFlangerDelayInput = 0;
PXUIElement* _textSoundFlangerPhaseInput = 0;
//---------------------------------------------------------
PXUIElement* _textSoundGargleEffect = 0;

PXUIElement* _textSoundGargleRateHz = 0;
PXUIElement* _textSoundGargleRateHzInput = 0;
PXUIElement* _textSoundGargleWaveShape = 0;
PXUIElement* _textSoundGargleWaveShapeInput = 0;
//---------------------------------------------------------
PXUIElement* _textSoundInteractive3DLevel2ReverbEffect = 0;

PXUIElement* _textSoundInteractive3DLevel2ReverbRoom = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbRoomHF = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbRoomRolloffFactor = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbDecayTime = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbDecayHFRatio = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbReflections = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbReflectionsDelay = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbReverb = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbReverbDelay = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbDiffusion = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbDensity = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbHFReference = 0;

PXUIElement* _textSoundInteractive3DLevel2ReverbRoomInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbRoomHFInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbRoomRolloffFactorInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbDecayTimeInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbDecayHFRatioInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbReflectionsInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbReflectionsDelayInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbReverbInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbReverbDelayInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbDiffusionInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbDensityInput = 0;
PXUIElement* _textSoundInteractive3DLevel2ReverbHFReferenceInput = 0;
//---------------------------------------------------------
PXUIElement* _textSoundParamEqEffect = 0;

PXUIElement* _textSoundParamEqCenter = 0;
PXUIElement* _textSoundParamEqBandwidth = 0;
PXUIElement* _textSoundParamEqGain = 0;
PXUIElement* _textSoundParamEqCenterInput = 0;
PXUIElement* _textSoundParamEqBandwidthInput = 0;
PXUIElement* _textSoundParamEqGainInput = 0;
//---------------------------------------------------------
PXUIElement* _textSoundWavesReverbEffect = 0;

PXUIElement* _textSoundWavesReverbInGain = 0;
PXUIElement* _textSoundWavesReverbReverbMix = 0;
PXUIElement* _textSoundWavesReverbReverbTime = 0;
PXUIElement* _textSoundWavesReverbHighFreqRTRatio = 0;

PXUIElement* _textSoundWavesReverbInGainInput = 0;
PXUIElement* _textSoundWavesReverbReverbMixInput = 0;
PXUIElement* _textSoundWavesReverbReverbTimeInput = 0;
PXUIElement* _textSoundWavesReverbHighFreqRTRatioInput = 0;

PXUIElement* _textSoundWavesReverbApply = 0;
//---------------------------------------------------------

//---------------------------------------------------------
// Network
//---------------------------------------------------------
PXUIElement* _panelNetworkMain = 0;
//---------------------------------------------------------


//---------------------------------------------------------
// Video
//---------------------------------------------------------
PXUIElement* _panelVideoMain = 0;
//---------------------------------------------------------



//---------------------------------------------------------
// Database
//---------------------------------------------------------
PXUIElement* _textDatabaseTitleODBC = 0;

PXUIElement* _textDatabaseDriver = 0;
PXUIElement* _comboBoxDatabaseDriver = 0;

PXUIElement* _textBoxDatabaseIP = 0;
PXUIElement* _comboBoxDatabaseIP = 0;

PXUIElement* _textBoxDatabasePort = 0;
PXUIElement* _comboBoxDatabasePort = 0;

PXUIElement* _buttonDatabaseConnect = 0;
//---------------------------------------------------------




//---------------------------------------------------------
// Frame console
//---------------------------------------------------------
PXUIElement* _panelConsoleMain = 0;
PXUIElement* _panelConsoleTextContent = 0;
PXUIElement* _panelConsoleData = 0;
//---------------------------------------------------------

//---------------------------------------------------------
// Left, Object panel
//---------------------------------------------------------
PXUIElement* _panelLeftSceneElements = 0;
PXUIElement* _textSceneElemenets = 0;
PXUIElement* _treeViewObjects = 0;
//---------------------------------------------------------


// Frame A

PXUIElement* _panelMenuButtonFileText = 0;

PXUIElement* _panelMenuButtonFileDropDownOpen = 0;
PXUIElement* _panelMenuButtonFileDropDownSave = 0;
PXUIElement* _panelMenuButtonEdit = 0;
PXUIElement* _panelMenuButtonEditText = 0;
PXUIElement* _panelMenuButtonView = 0;
PXUIElement* _panelMenuButtonViewText = 0;



PXUIElement* _panelMainContent = 0;




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

void PXAPI PXOnEngineResourceAdded(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, void* const pxEngineResourceCreateInfo)
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

/*
  switch(pxUIElementInteractInfo->Type)
            {
                case PXUIElementInteractTypeSelect:
                {


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

*/


void PXAPI BFObjectTreeViewEvent(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeSelect:
        {  

            PXUIElement* const uiElementSelected = pxWindowEvent->UIElementSender;

            PXLogPrint
            (
                PXLoggingInfo,
                "BF",
                "Event",
                "Select: <%s>",
                ""// uiElementSelected->NameData
            );


           // _uiInfoPanelObjectNameContent->TextInfo.Content = pxUIElementInteractInfo->UIElementSelected->NameData;

            //const char* typeName = PXUIElementTypeToString(uiElementSelected->Type);

           // _uiInfoPanelObjectTypeContent->TextInfo.Content = typeName;

            PXGUIElementUpdateInfo pxUIElementUpdateInfo[2];
            PXClearList(PXGUIElementUpdateInfo, pxUIElementUpdateInfo, 2);

            pxUIElementUpdateInfo[0].UIElement = _uiInfoPanelObjectNameContent;
            pxUIElementUpdateInfo[0].WindowReference = &bfBitFireIDE->EngineEditor.Window;
            pxUIElementUpdateInfo[0].Property = PXUIElementPropertyTextContent;
          //  pxUIElementUpdateInfo[0].Data.Text.Content = _uiInfoPanelObjectNameContent->NameData;

            pxUIElementUpdateInfo[1].UIElement = _uiInfoPanelObjectTypeContent;
            pxUIElementUpdateInfo[1].WindowReference = &bfBitFireIDE->EngineEditor.Window;
            pxUIElementUpdateInfo[1].Property = PXUIElementPropertyTextContent;
         //   pxUIElementUpdateInfo[1].Data.Text.Content = _uiInfoPanelObjectTypeContent->NameData;

             PXGUIElementUpdate(PXNull, pxUIElementUpdateInfo, 2);          

            break;
        }
        default:
            break;
    }  
}

void PXAPI BFObjectTreeViewUpdate(BFBitFireIDE* const bfBitFireIDE)
{
    PXEngine* const pxEngineEditor = &bfBitFireIDE->EngineEditor;
    PXEngine* const pxEngineScene = &bfBitFireIDE->EngineScene;


    PXResourceCreateInfo pxResourceCreateInfo;

    // DOne UI Stuff

    {
        // Load data for UI
        {
            PXDictionary parentList;

            PXDictionaryConstruct(&parentList, sizeof(PXUIElement*), sizeof(PXUIElement*), PXDictionaryValueLocalityInternalEmbedded);


            PXDictionary* const uiElementLookup = &pxEngineEditor->ResourceManager.GUIElementLookup;

            PXUIElement* uiAncer = 0;
            PXUIElement* sceneAncer = 0;

            //  Create UI element, a container for the full UI things
            {
                PXUIElement* uiElementItem = PXNull;
                       
                PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                pxResourceCreateInfo.ObjectReference = &uiElementItem;
                pxResourceCreateInfo.Name = "UI";
                pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeEmpty;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = PXNull;

                PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                PXDictionaryAdd(&parentList, &uiElementItem, &uiElementItem);

                uiAncer = uiElementItem;
            }

            // Create scene UI container elemenents
            {
                PXUIElement* uiElementItem = PXNull;

                PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                pxResourceCreateInfo.ObjectReference = &uiElementItem;
                pxResourceCreateInfo.Name = "Scene";
                pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeEmpty;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = PXNull;

                PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                PXDictionaryAdd(&parentList, &uiElementItem, &uiElementItem);

                // Add multible 
                {
                    PXUIElement* uiTreeViewItemModel = PXNull;
                    PXUIElement* uiTreeViewItemShader = PXNull;
                    PXUIElement* uiTreeViewItemImage = PXNull;


                    PXResourceCreateInfo pxUIElementCreateDataList[8];
                    PXClearList(PXResourceCreateInfo, pxUIElementCreateDataList, 8);
                    pxUIElementCreateDataList[0].Type = PXResourceTypeGUIElement;
                    pxUIElementCreateDataList[0].ObjectReference = &uiTreeViewItemModel;
                    pxUIElementCreateDataList[0].Name = "Model";
                    pxUIElementCreateDataList[0].UIElement.Type = PXUIElementTypeTreeViewItem;
                    pxUIElementCreateDataList[0].UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeEmpty;
                    pxUIElementCreateDataList[0].UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                    pxUIElementCreateDataList[0].UIElement.Data.TreeViewItem.ItemParent = uiElementItem;
                    pxUIElementCreateDataList[0].UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                    pxUIElementCreateDataList[1].Type = PXResourceTypeGUIElement;
                    pxUIElementCreateDataList[1].ObjectReference = &uiTreeViewItemShader;
                    pxUIElementCreateDataList[1].Name = "Shader";
                    pxUIElementCreateDataList[1].UIElement.Type = PXUIElementTypeTreeViewItem;
                    pxUIElementCreateDataList[1].UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeEmpty;
                    pxUIElementCreateDataList[1].UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                    pxUIElementCreateDataList[1].UIElement.Data.TreeViewItem.ItemParent = uiElementItem;
                    pxUIElementCreateDataList[1].UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                    pxUIElementCreateDataList[2].Type = PXResourceTypeGUIElement;
                    pxUIElementCreateDataList[2].ObjectReference = &uiTreeViewItemImage;
                    pxUIElementCreateDataList[2].Name = "Image";
                    pxUIElementCreateDataList[2].UIElement.Type = PXUIElementTypeTreeViewItem;
                    pxUIElementCreateDataList[2].UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeEmpty;
                    pxUIElementCreateDataList[2].UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                    pxUIElementCreateDataList[2].UIElement.Data.TreeViewItem.ItemParent = uiElementItem;
                    pxUIElementCreateDataList[2].UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;


                    for(size_t i = 0; i < 3; i++)
                    {
                        PXResourceCreateInfo* pxEngineResourceCreateInfo = &pxUIElementCreateDataList[i];

                        PXEngineResourceCreate(pxEngineEditor, pxEngineResourceCreateInfo);

                        PXDictionaryAdd(&parentList, &pxEngineResourceCreateInfo->ObjectReference, &pxEngineResourceCreateInfo->ObjectReference);
                    }


                    if(bfBitFireIDE->EngineScene.IsRunning)
                    {
                        for(PXSize i = 0; i < bfBitFireIDE->EngineScene.ResourceManager.ModelLookUp.EntryAmountCurrent; i++)
                        {
                            PXDictionaryEntry pxDictionaryEntry;
                            PXModel* pxModel = PXNull;
                            PXUIElement* uiEE = PXNull;

                            PXDictionaryIndex(&bfBitFireIDE->EngineScene.ResourceManager.ModelLookUp, i, &pxDictionaryEntry);

                            pxModel = *(PXModel**)pxDictionaryEntry.Value;


                            PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                            pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                            pxResourceCreateInfo.ObjectReference = &uiEE;
                            pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObject = pxModel;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeModel;;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = uiTreeViewItemModel;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                            char buffer[256];
                            PXTextPrintA(buffer, 256, "[Model]");
                            pxResourceCreateInfo.Name = buffer;

                            PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                            PXDictionaryAdd(&parentList, &uiEE, &pxModel);
                        }

                        for(PXSize i = 0; i < bfBitFireIDE->EngineScene.ResourceManager.SpritelLookUp.EntryAmountCurrent; i++)
                        {
                            PXDictionaryEntry pxDictionaryEntry;
                            PXShaderProgram* pxShaderProgram = PXNull;
                            PXUIElement* uiEE = PXNull;

                            PXDictionaryIndex(&bfBitFireIDE->EngineScene.ResourceManager.ShaderProgramLookup, i, &pxDictionaryEntry);

                            pxShaderProgram = *(PXShaderProgram**)pxDictionaryEntry.Value;

                            PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                            pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                            pxResourceCreateInfo.ObjectReference = &uiEE;
                            pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObject = pxShaderProgram;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeRenderShader;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = uiTreeViewItemShader;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                            char buffer[256];
                            PXTextPrintA(buffer, 256, "[ShaderProgram]");
                            pxResourceCreateInfo.Name = buffer;

                            PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                            PXDictionaryAdd(&parentList, &uiEE, &pxShaderProgram);
                        }


                        for(PXSize i = 0; i < bfBitFireIDE->EngineScene.ResourceManager.ImageLookUp.EntryAmountCurrent; i++)
                        {
                            PXDictionaryEntry pxDictionaryEntry;
                            PXImage* pxImage = PXNull;
                            PXUIElement* uiEE = PXNull;

                            PXDictionaryIndex(&bfBitFireIDE->EngineScene.ResourceManager.ImageLookUp, i, &pxDictionaryEntry);

                            pxImage = *(PXImage**)pxDictionaryEntry.Value;


                            PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                            pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                            pxResourceCreateInfo.ObjectReference = &uiEE;
                            pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObject = pxImage;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeImage;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = uiTreeViewItemImage;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                            char buffer[256];
                            PXTextPrintA(buffer, 256, "[Image]");
                            pxResourceCreateInfo.Name = buffer;

                            PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                            PXDictionaryAdd(&parentList, &uiEE, &pxImage);
                        }
                    }


                }
            }


            PXSize sixed = uiElementLookup->EntryAmountCurrent;

            for(PXSize i = 0; i < sixed; ++i)
            {
                PXDictionaryEntry pxDictionaryEntry;
                PXUIElement* uiElement = PXNull;

                PXDictionaryIndex(uiElementLookup, i, &pxDictionaryEntry);

                uiElement = *(PXUIElement**)pxDictionaryEntry.Value;

                PXUIElement* uiElementItem = PXNull;

                PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                pxResourceCreateInfo.ObjectReference = &uiElementItem;
                //pxResourceCreateInfo.Name = uiElement->NameData;
                pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObject = uiElement;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeUI;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                // Fetch parrant
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = uiAncer;

                if(uiElement->Parent)
                {
                    PXUIElement* parentElement = PXNull;

                    const PXBool found = PXDictionaryFindEntry(&parentList, &uiElement->Parent, &parentElement);

                    if(found)
                    {
                        pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = parentElement;
                    }
                }

                PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                PXDictionaryAdd(&parentList, &uiElement, &uiElementItem);
            }
        }




        // Add more?
    }


}

void PXAPI BFInfoSelectUpdate(BFBitFireIDE* const bfBitFireIDE)
{
   
}

void PXAPI BFSceneOnStartup(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{
    PXResourceCreateInfo pxUIElementCreateData;

    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeSound;
        pxUIElementCreateData.ObjectReference = &_musicTest;
        pxUIElementCreateData.FilePath = "H:\\[Cache]\\chip.wav";
        pxUIElementCreateData.Sound.SoundLoop = PXTrue;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);


        PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;
        pxAudio->DeviceOpen(pxAudio->SystemReference, &_soundAudioDevice, PXAudioDeviceTypeOutput, 0);
        pxAudio->DeviceLoad(pxAudio->SystemReference, &_soundAudioDevice, _musicTest);
    }


    //-----------------------------------------------------
    // Shader-Object
    //-----------------------------------------------------
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeShaderProgram;
        pxUIElementCreateData.ObjectReference = &_pxObjectShader;
        pxUIElementCreateData.ShaderProgram.ShaderVertexFilePath = "Shader/Object_Vertex.glsl";
        pxUIElementCreateData.ShaderProgram.ShaderPixelFilePath = "Shader/Object_Fragment.glsl";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeShaderProgram;
        pxUIElementCreateData.ObjectReference = &_pxGismoShader;
        pxUIElementCreateData.ShaderProgram.ShaderVertexFilePath = "Shader/Gismo_Vertex.glsl";
        pxUIElementCreateData.ShaderProgram.ShaderPixelFilePath = "Shader/Gismo_Fragment.glsl";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }




    // Load model
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeModel;
        pxUIElementCreateData.ObjectReference = &_pxModelMap;
        pxUIElementCreateData.FilePath = "Model/Dust_II/DustII.obj";
        //pxUIElementCreateData.FilePath = "P:\\_Cache\\N64\\PennyRacer\\Apline\\OBJ\\untitled.obj";// "Model/Dust_II/DustII.obj";
        // "Model/Tiger.obj" 
        // "Model/Dust_II/DustII.obj"
        // "Model/Tiger.obj"
        // "Model/Moze.obj"
        pxUIElementCreateData.Model.ShaderProgramReference = _pxObjectShader;
        pxUIElementCreateData.Model.Scale = 50.0f;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeModel;
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
        PXResourceCreateInfo pxSkyBoxCreateEventData;
        PXClear(PXResourceCreateInfo, &pxSkyBoxCreateEventData);
        pxSkyBoxCreateEventData.Type = PXResourceTypeSkybox;
        pxSkyBoxCreateEventData.SpawnEnabled = PXTrue;
        pxSkyBoxCreateEventData.ObjectReference = &_sceneSkyBox;
        pxSkyBoxCreateEventData.SkyBox.ShaderProgramCreateInfo.ShaderVertexFilePath = "Shader/SkyBox_Vertex.glsl";
        pxSkyBoxCreateEventData.SkyBox.ShaderProgramCreateInfo.ShaderPixelFilePath = "Shader/SkyBox_Fragment.glsl";
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
        _pxModelMapWorldGrid->VertexBuffer.Format = PXVertexBufferFormatXYZFloat;
       // _pxModelMapWorldGrid->VertexBuffer.VertexDataRowSize = 3 * sizeof(float);

       // _pxModelMapWorldGrid->IndexBuffer.IndexTypeSize = 1;
        _pxModelMapWorldGrid->IndexBuffer.IndexData = indexDATA;
        _pxModelMapWorldGrid->IndexBuffer.IndexDataSize = sizeof(indexDATA);
       // _pxModelMapWorldGrid->IndexBuffer.IndexDataAmount = sizeof(indexDATA) / sizeof(PXInt8U);
        _pxModelMapWorldGrid->IndexBuffer.IndexDataType = PXDataTypeInt08U;
        _pxModelMapWorldGrid->IndexBuffer.DrawModeID = PXDrawModeIDTriangle; // PXDrawModeIDPoint | PXDrawModeIDLine;

        PXFunctionInvoke(pxEngine->Graphic.ModelRegister, pxEngine->Graphic.EventOwner, _pxModelMapWorldGrid);

       // _pxModelMapWorldGrid->Enabled = PXTrue;
    }

    //-----------------------------------------------------
    // Worldgrid-Shader
    //-----------------------------------------------------
    {
        PXResourceCreateInfo pxSkyBoxCreateEventData;
        PXClear(PXResourceCreateInfo, &pxSkyBoxCreateEventData);
        pxSkyBoxCreateEventData.Type = PXResourceTypeShaderProgram;
        pxSkyBoxCreateEventData.ObjectReference = &_pxWorldGridShader;
        pxSkyBoxCreateEventData.ShaderProgram.ShaderVertexFilePath = "Shader/WorldGrid_Vertex.glsl";
        pxSkyBoxCreateEventData.ShaderProgram.ShaderPixelFilePath = "Shader/WorldGrid_Fragment.glsl";

        PXEngineResourceCreate(pxEngine, &pxSkyBoxCreateEventData);

        _pxModelMapWorldGrid->ShaderProgramReference = _pxWorldGridShader;
        _pxModelMapWorldGrid->RenderBothSides = PXTrue;

        PXMatrix4x4FScaleBy(&_pxModelMapWorldGrid->ModelMatrix, 1000);
    }

    PXCameraConstruct(&_worldCamera);
}


void PXAPI PXOnSoundButtonPlayEvent(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    PXLogPrint
    (
        PXLoggingInfo,
        "GUI", 
        "Click", 
        "Do music"
    );

    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;   

            pxAudio->PlayCursorSet(pxAudio->SystemReference, &_soundAudioDevice, 0);
            pxAudio->DeviceStart(pxAudio->SystemReference, &_soundAudioDevice);

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundButtonStopEvent(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    PXLogPrint
    (
        PXLoggingInfo,
        "GUI",
        "Click",
        "Do music"
    );

    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;

            pxAudio->DeviceStop(pxAudio->SystemReference, &_soundAudioDevice);

            break;
        }

        default:
            break;
    }
}

void PXMakeUIEnable(PXGUISystem* const pxGgui, PXAudio* pxAudio, PXAudioEffectType effect, int flag, PXUIElement* button)
{
    PXAudioEffect pxAudioEffect;
    PXClear(PXAudioEffect, &pxAudioEffect);
    pxAudioEffect.Type = effect;
    pxAudioEffect.Enable = !(_soundAudioDevice.FXSettingFlagList & flag);

    pxAudio->DeviceEffectUpdate(pxAudio->SystemReference, &_soundAudioDevice, &pxAudioEffect);

    PXGUIElementUpdateInfo pxGUIElementUpdateInfo[3];
    PXClearList(PXGUIElementUpdateInfo, pxGUIElementUpdateInfo, 3);

    pxGUIElementUpdateInfo[0].Property = PXUIElementPropertyTextContent;
    pxGUIElementUpdateInfo[0].UIElement = button;

    pxGUIElementUpdateInfo[1].Property = PXUIElementPropertyBackGroundColor;
    pxGUIElementUpdateInfo[1].UIElement = button;

    if(pxAudioEffect.Enable)
    {
        pxGUIElementUpdateInfo[0].Data.Text.Content = "ON";  
    }
    else
    {
        pxGUIElementUpdateInfo[0].Data.Text.Content = "OFF";
    }

    PXGUIElementUpdate(pxGgui, pxGUIElementUpdateInfo, 2);
}

void PXAPI PXOnSoundEffectUpdate_Chorus_Toggle(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            PXMakeUIEnable
            (
                &bfBitFireIDE->EngineEditor.GUISystem,
                &bfBitFireIDE->EngineEditor.Audio, 
                PXAudioEffectTypeChorus,
                PXAudioFXChorus,
                _textSoundChorusEnable
            );

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundEffectUpdate_Chorus(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            HWND aaa[7] =
            {
                _textSoundChorusWetDryMixInput->Info.WindowID,
                _textSoundChorusDepthInput->Info.WindowID,
                _textSoundChorusFeedbackInput->Info.WindowID,
                _textSoundChorusFrequencyInput->Info.WindowID,
                _textSoundChorusWaveformInput->Info.WindowID,
                _textSoundChorusDelayInput->Info.WindowID,
                _textSoundChorusPhaseInput->Info.WindowID
            };
            float ddd[7] = { 0,0,0,0,0,0,0 };

            for(size_t i = 0; i < 7; i++)
            {
                ddd[i] = SendMessageA(aaa[i], TBM_GETPOS, 0, 0) / 100.f;
            }

            PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;

            PXAudioEffect pxAudioEffectWavesReverb;
            PXClear(PXAudioEffect, &pxAudioEffectWavesReverb);
            pxAudioEffectWavesReverb.Type = PXAudioEffectTypeChorus;
            pxAudioEffectWavesReverb.Enable = PXTrue;
            pxAudioEffectWavesReverb.Fetch = PXFalse;
            pxAudioEffectWavesReverb.Chorus.WetDryMix = ddd[0];
            pxAudioEffectWavesReverb.Chorus.Depth = ddd[1];
            pxAudioEffectWavesReverb.Chorus.Feedback = ddd[2];
            pxAudioEffectWavesReverb.Chorus.Frequency = ddd[3];
            pxAudioEffectWavesReverb.Chorus.Waveform = ddd[4];
            pxAudioEffectWavesReverb.Chorus.Delay = ddd[5];
            pxAudioEffectWavesReverb.Chorus.Phase = ddd[6];

            pxAudio->DeviceEffectUpdate(pxAudio->SystemReference, &_soundAudioDevice, &pxAudioEffectWavesReverb);

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundEffectUpdate_Compressor_Toggle(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            PXMakeUIEnable
            (
                &bfBitFireIDE->EngineEditor.GUISystem,
                &bfBitFireIDE->EngineEditor.Audio,
                PXAudioEffectTypeCompressor,
                PXAudioFXCompressor,
                _textSoundCompressorEnable
            );

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundEffectUpdate_Compressor(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            HWND aaa[6] =
            {
                _textSoundCompressorGainInput->Info.WindowID,
                _textSoundCompressorAttackInput->Info.WindowID,
                _textSoundCompressorReleaseInput->Info.WindowID,
                _textSoundCompressorThresholdInput->Info.WindowID,
                _textSoundCompressorRatioInput->Info.WindowID,
                _textSoundCompressorPredelayInput->Info.WindowID
            };
            float ddd[6] = { 0,0,0,0,0,0 };

            for(size_t i = 0; i < 6; i++)
            {
                ddd[i] = SendMessageA(aaa[i], TBM_GETPOS, 0, 0) / 100.f;
            }

            PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;

            PXAudioEffect pxAudioEffectWavesReverb;
            PXClear(PXAudioEffect, &pxAudioEffectWavesReverb);
            pxAudioEffectWavesReverb.Type = PXAudioEffectTypeCompressor;
            pxAudioEffectWavesReverb.Enable = PXTrue;
            pxAudioEffectWavesReverb.Fetch = PXFalse;
            pxAudioEffectWavesReverb.Compressor.Gain = ddd[0];
            pxAudioEffectWavesReverb.Compressor.Attack = ddd[1];
            pxAudioEffectWavesReverb.Compressor.Release = ddd[2];
            pxAudioEffectWavesReverb.Compressor.Threshold = ddd[3];
            pxAudioEffectWavesReverb.Compressor.Ratio = ddd[4];
            pxAudioEffectWavesReverb.Compressor.Predelay = ddd[5];

            pxAudio->DeviceEffectUpdate(pxAudio->SystemReference, &_soundAudioDevice, &pxAudioEffectWavesReverb);

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundEffectUpdate_Distortion_Toggle(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            PXMakeUIEnable
            (
                &bfBitFireIDE->EngineEditor.GUISystem,
                &bfBitFireIDE->EngineEditor.Audio,
                PXAudioEffectTypeDistortion,
                PXAudioFXDistortion,
                _textSoundDistortionEnable
            );

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundEffectUpdate_Distortion(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            HWND aaa[5] =
            {
                _textSoundDistortionGainInput->Info.WindowID,
                _textSoundDistortionEdgeInput->Info.WindowID,
                _textSoundDistortionPostEQCenterFrequencyInput->Info.WindowID,
                _textSoundDistortionPostEQBandwidthInput->Info.WindowID,
                _textSoundDistortionPreLowpassCutoffInput->Info.WindowID
            };
            float ddd[5] = { 0,0,0,0,0 };

            for(size_t i = 0; i < 5; i++)
            {
                ddd[i] = SendMessageA(aaa[i], TBM_GETPOS, 0, 0) / 100.f;
            }

            PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;

            PXAudioEffect pxAudioEffectWavesReverb;
            PXClear(PXAudioEffect, &pxAudioEffectWavesReverb);
            pxAudioEffectWavesReverb.Type = PXAudioEffectTypeDistortion;
            pxAudioEffectWavesReverb.Enable = PXTrue;
            pxAudioEffectWavesReverb.Fetch = PXFalse;
            pxAudioEffectWavesReverb.Distortion.Gain = ddd[0];
            pxAudioEffectWavesReverb.Distortion.Edge = ddd[1];
            pxAudioEffectWavesReverb.Distortion.PostEQCenterFrequency = ddd[2];
            pxAudioEffectWavesReverb.Distortion.PostEQBandwidth = ddd[3];
            pxAudioEffectWavesReverb.Distortion.PreLowpassCutoff = ddd[4];

            pxAudio->DeviceEffectUpdate(pxAudio->SystemReference, &_soundAudioDevice, &pxAudioEffectWavesReverb);

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundEffectUpdate_Echo_Toggle(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            PXMakeUIEnable
            (
                &bfBitFireIDE->EngineEditor.GUISystem,
                &bfBitFireIDE->EngineEditor.Audio,
                PXAudioEffectTypeEcho,
                PXAudioFXEcho,
                _textSoundEchoEnable
            );

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundEffectUpdate_Echo(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            HWND aaa[5] =
            {
                _textSoundEchoWetDryMixInput->Info.WindowID,
                _textSoundEchoFeedbackInput->Info.WindowID,
                _textSoundEchoLeftDelayInput->Info.WindowID,
                _textSoundEchoRightDelayInput->Info.WindowID,
                _textSoundEchoPanDelayInput->Info.WindowID
            };
            float ddd[5] = { 0,0,0,0,0 };

            for(size_t i = 0; i < 5; i++)
            {
                ddd[i] = SendMessageA(aaa[i], TBM_GETPOS, 0, 0) / 100.f;
            }

            PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;

            PXAudioEffect pxAudioEffectWavesReverb;
            PXClear(PXAudioEffect, &pxAudioEffectWavesReverb);
            pxAudioEffectWavesReverb.Type = PXAudioEffectTypeEcho;
            pxAudioEffectWavesReverb.Enable = PXTrue;
            pxAudioEffectWavesReverb.Fetch = PXFalse;
            pxAudioEffectWavesReverb.Echo.WetDryMix = ddd[0];
            pxAudioEffectWavesReverb.Echo.Feedback = ddd[1];
            pxAudioEffectWavesReverb.Echo.LeftDelay = ddd[2];
            pxAudioEffectWavesReverb.Echo.RightDelay = ddd[3];
            pxAudioEffectWavesReverb.Echo.PanDelay = ddd[4];

            pxAudio->DeviceEffectUpdate(pxAudio->SystemReference, &_soundAudioDevice, &pxAudioEffectWavesReverb);

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundEffectUpdate_Flanger(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            HWND aaa[7] =
            {
                _textSoundFlangerWetDryMixInput->Info.WindowID,
                _textSoundFlangerDepthInput->Info.WindowID,
                _textSoundFlangerFeedbackInput->Info.WindowID,
                _textSoundFlangerFrequencyInput->Info.WindowID,
                _textSoundFlangerWaveformInput->Info.WindowID,
                _textSoundFlangerDelayInput->Info.WindowID,
                _textSoundFlangerPhaseInput->Info.WindowID
            };
            float ddd[7] = { 0,0,0,0,0,0,0 };

            for(size_t i = 0; i < 7; i++)
            {
                ddd[i] = SendMessageA(aaa[i], TBM_GETPOS, 0, 0) / 100.f;
            }

            PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;

            PXAudioEffect pxAudioEffectWavesReverb;
            PXClear(PXAudioEffect, &pxAudioEffectWavesReverb);
            pxAudioEffectWavesReverb.Type = PXAudioEffectTypeFlanger;
            pxAudioEffectWavesReverb.Enable = PXTrue;
            pxAudioEffectWavesReverb.Fetch = PXFalse;
            pxAudioEffectWavesReverb.Flanger.WetDryMix = ddd[0];
            pxAudioEffectWavesReverb.Flanger.Depth = ddd[1];
            pxAudioEffectWavesReverb.Flanger.Feedback = ddd[2];
            pxAudioEffectWavesReverb.Flanger.Frequency = ddd[3];
            pxAudioEffectWavesReverb.Flanger.Waveform = ddd[4];
            pxAudioEffectWavesReverb.Flanger.Delay = ddd[5];
            pxAudioEffectWavesReverb.Flanger.Phase = ddd[6];

            pxAudio->DeviceEffectUpdate(pxAudio->SystemReference, &_soundAudioDevice, &pxAudioEffectWavesReverb);

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundEffectUpdate_Gargle(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            HWND aaa[6] =
            {
                _textSoundGargleRateHzInput->Info.WindowID,
                _textSoundGargleWaveShapeInput->Info.WindowID
            };
            float ddd[6] = { 0,0 };

            for(size_t i = 0; i < 2; i++)
            {
                ddd[i] = SendMessageA(aaa[i], TBM_GETPOS, 0, 0) / 100.f;
            }

            PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;

            PXAudioEffect pxAudioEffectWavesReverb;
            PXClear(PXAudioEffect, &pxAudioEffectWavesReverb);
            pxAudioEffectWavesReverb.Type = PXAudioEffectTypeGargle;
            pxAudioEffectWavesReverb.Enable = PXTrue;
            pxAudioEffectWavesReverb.Fetch = PXFalse;
            pxAudioEffectWavesReverb.Gargle.dwRateHz = ddd[0];
            pxAudioEffectWavesReverb.Gargle.dwWaveShape = ddd[1];

            pxAudio->DeviceEffectUpdate(pxAudio->SystemReference, &_soundAudioDevice, &pxAudioEffectWavesReverb);

            break;
        }

        default:
            break;
    }
}

void PXAPI PXOnSoundEffectUpdate_Interactive3DLevel2Reverb(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{

}

void PXAPI PXOnSoundEffectUpdate_ParamEq(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{

}

void PXAPI PXOnSoundEffectUpdate_WavesReverb(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    PXLogPrint
    (
        PXLoggingInfo,
        "GUI",
        "Click",
        "Do sdads"
    );

    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeClick:
        {
            HWND aaa[4] =
            {
                _textSoundWavesReverbInGainInput->Info.WindowID,
                _textSoundWavesReverbReverbMixInput->Info.WindowID,
                _textSoundWavesReverbReverbTimeInput->Info.WindowID,
                _textSoundWavesReverbHighFreqRTRatioInput->Info.WindowID,
            };
            float ddd[4] = { 0,0,0,0 };


            for(size_t i = 0; i < 4; i++)
            {
                PXText pxText;
                PXTextConstructBufferA(&pxText, 64);

                pxText.SizeUsed += GetWindowTextA(aaa[i], pxText.TextA, pxText.SizeAllocated);


                PXTextToFloat(&pxText, &ddd[i]);

                ddd[i] = SendMessageA(aaa[i], TBM_GETPOS, 0, 0) / 100.f;
            }

            PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;

            PXAudioEffect pxAudioEffectWavesReverb;
            PXClear(PXAudioEffect, &pxAudioEffectWavesReverb);
            pxAudioEffectWavesReverb.Type = PXAudioEffectTypeWavesReverb;
            pxAudioEffectWavesReverb.Enable = PXTrue;
            pxAudioEffectWavesReverb.Fetch = PXFalse;
            pxAudioEffectWavesReverb.WavesReverb.InGain = ddd[0];
            pxAudioEffectWavesReverb.WavesReverb.ReverbMix = ddd[1];
            pxAudioEffectWavesReverb.WavesReverb.ReverbTime = ddd[2];
            pxAudioEffectWavesReverb.WavesReverb.HighFreqRTRatio = ddd[3];

            pxAudio->DeviceEffectUpdate(pxAudio->SystemReference, &_soundAudioDevice, &pxAudioEffectWavesReverb);

            break;
        }

        default:
            break;
    }
}














void PXAPI OnStartUpEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{
    PXResourceCreateInfo pxUIElementCreateData;

    //-----------------------------------------------------
    // Main Font
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeFont;
        pxUIElementCreateData.ObjectReference = &DefaultFont;
        pxUIElementCreateData.FilePath = "Font/A.fnt";
        //pxSkyBoxCreateEventData.Font.ShaderProgramCurrent = _worldShader;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

    }

    //-----------------------------------------------------
    // Panel:Menu
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);       
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_tabControlMain;
        pxUIElementCreateData.Name = "RenderScene";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTabControll;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.UIElementParent = pxEngine->Window;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.41f;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.41f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.54f;



        PXUIElementTabPageSingleInfo pxUIElementTabPageSingleInfo[] = 
        {
            { &_tabPageScene, "Scene", -1},
            { &_tabPageSound, "Sound", -1},
            { &_tabPageVideo, "Video", -1},
            { &_tabPageDatabase, "Database", -1},
            { &_tabPageNetwork, "Network", -1},
            { &_tabPageInput, "Input", -1 }
        };
        const PXSize amount = sizeof(pxUIElementTabPageSingleInfo) / sizeof(PXUIElementTabPageSingleInfo);

        pxUIElementCreateData.UIElement.Data.TabPage.TabPageSingleInfoAmount = amount;
        pxUIElementCreateData.UIElement.Data.TabPage.TabPageSingleInfoList = pxUIElementTabPageSingleInfo;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }




    //-----------------------------------------------------
    // TAB::Scene
    //-----------------------------------------------------
    {
        PXEngineStartInfo pxEngineStartInfo;
        PXClear(PXEngineStartInfo, &pxEngineStartInfo);

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.Name = "SceneRender";
        pxUIElementCreateData.ObjectReference = &_dialogBoxTexture;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeRenderFrame;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageScene;
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

    //-----------------------------------------------------
    // Panel::Scene::Text
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.Name = "RenderScene-Text";
        pxUIElementCreateData.ObjectReference = &_panelMenuButtonFileText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _tabControlMain;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Scene";
        pxUIElementCreateData.UIElement.Data.Text.FontID = DefaultFont;

        //PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

#define SoundHeight 20
#define SoundWidth 400

#define SoundWidthRowA 0.375 * SoundWidth
#define SoundWidthRowB 0.625 * SoundWidth

#define SoundRowOffsetX1 0.211
#define SoundRowOffsetY 0.05

    //-----------------------------------------------------
    // TAB::Sound
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_buttonSoundPlay;
        pxUIElementCreateData.Name = "Sound_Play";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = 35;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.95f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.0;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = ">";
        pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundButtonPlayEvent;
        pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_buttonSoundStop;
        pxUIElementCreateData.Name = "Sound_Pause";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = 35;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 1.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.0;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "||";
        pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundButtonStopEvent;
        pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


    // Chorus
    {

        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusEffect;
            pxUIElementCreateData.Name = "Sound_ChorusEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth-100;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 0;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Chorus";

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusEnable;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Phase";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = 35;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.40;
            pxUIElementCreateData.UIElement.Position.MarginTop = 0;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "[+]";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Chorus_Toggle;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusApply;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Phase";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = 70;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.45;
            pxUIElementCreateData.UIElement.Position.MarginTop = 0;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Apply";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Chorus;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusWetDryMix;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
            pxUIElementCreateData.UIElement.Data.Text.Content = "WetDryMix";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
     
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusDepth;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Depth";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Depth";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusFeedback;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Feedback";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Feedback";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusFrequency;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Frequency";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Frequency";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusWaveform;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Waveform";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Waveform";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusDelay;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Delay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Delay";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusPhase;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Phase";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 7;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Phase";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusWetDryMixInput;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
            pxUIElementCreateData.UIElement.Data.Text.Content = "WetDryMix";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusDepthInput;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Depth";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Depth";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusFeedbackInput;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Feedback";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Feedback";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusFrequencyInput;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Frequency";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Frequency";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusWaveformInput;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Waveform";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Waveform";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusDelayInput;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Delay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Delay";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusPhaseInput;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Phase";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 7;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Phase";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }

    // Compressor
    {
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressor;
            pxUIElementCreateData.Name = "Sound_Compressor";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 8.25;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Compressor";

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }   
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorEnable;
            pxUIElementCreateData.Name = "Compressor_Toggle";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = 35;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.40;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 8.25;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "[+]";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Compressor_Toggle;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorApply;
            pxUIElementCreateData.Name = "Compressor_Apply";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = 70;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.45;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 8.25;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Apply";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Compressor;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorGain;
            pxUIElementCreateData.Name = "Sound_CompressorEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Gain";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorAttack;
            pxUIElementCreateData.Name = "Sound_CompressorEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Attack";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorRelease;
            pxUIElementCreateData.Name = "Sound_CompressorEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Release";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorThreshold;
            pxUIElementCreateData.Name = "Sound_CompressorEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Threshold";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorRatio;
            pxUIElementCreateData.Name = "Sound_Compressor";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Ratio";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorPredelay;
            pxUIElementCreateData.Name = "Sound_Compressor_Predelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Predelay";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorGainInput;
            pxUIElementCreateData.Name = "Sound_CompressorEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Gain";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorAttackInput;
            pxUIElementCreateData.Name = "Sound_CompressorEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Attack";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorReleaseInput;
            pxUIElementCreateData.Name = "Sound_CompressorEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Release";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorThresholdInput;
            pxUIElementCreateData.Name = "Sound_CompressorEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Threshold";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorRatioInput;
            pxUIElementCreateData.Name = "Sound_Compressor";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Ratio";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorPredelayInput;
            pxUIElementCreateData.Name = "Sound_Compressor_Predelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Predelay";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }

    // Distortion
    {
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortion;
            pxUIElementCreateData.Name = "Sound_Distortion";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.6f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 0;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Distortion";

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionEnable;
            pxUIElementCreateData.Name = "Compressor_Toggle";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = 35;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.6 + 0.40;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 0;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "[+]";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Distortion_Toggle;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionApply;
            pxUIElementCreateData.Name = "Compressor_Apply";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = 70;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.6 + 0.45;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 0;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Apply";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Distortion;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {      
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionGain;
            pxUIElementCreateData.Name = "Sound_Distortion_Gain";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Gain";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionEdge;
            pxUIElementCreateData.Name = "Sound_Distortion_Edge";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Edge";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPostEQCenterFrequency;
            pxUIElementCreateData.Name = "Sound_Distortion_PostEQCenterFrequency";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
            pxUIElementCreateData.UIElement.Data.Text.Content = "PostEQCenterFrequency";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPostEQBandwidth;
            pxUIElementCreateData.Name = "Sound_Distortion_PostEQBandwidth";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;
            pxUIElementCreateData.UIElement.Data.Text.Content = "PostEQBandwidth";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPreLowpassCutoff;
            pxUIElementCreateData.Name = "Sound_Distortion_PreLowpassCutoff";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "PreLowpassCutoff";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionGainInput;
            pxUIElementCreateData.Name = "Sound_Distortion_Gain";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionEdgeInput;
            pxUIElementCreateData.Name = "Sound_Distortion_Edge";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPostEQCenterFrequencyInput;
            pxUIElementCreateData.Name = "Sound_Distortion_PostEQCenterFrequency";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPostEQBandwidthInput;
            pxUIElementCreateData.Name = "Sound_Distortion_PostEQBandwidth";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPreLowpassCutoffInput;
            pxUIElementCreateData.Name = "Sound_Distortion_PreLowpassCutoff";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }







    // Sound_Echo
    {
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoEffect;
            pxUIElementCreateData.Name = "Sound_Echo";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.6f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6.5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Echo";

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoEnable;
            pxUIElementCreateData.Name = "Echo_Toggle";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = 35;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.6 + 0.40;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6.5;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "[+]";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Echo_Toggle;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoApply;
            pxUIElementCreateData.Name = "Echo_Apply";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = 70;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.6 + 0.45;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6.5;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Apply";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Echo;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoWetDryMix;
            pxUIElementCreateData.Name = "Sound_Echo_WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
            pxUIElementCreateData.UIElement.Data.Text.Content = "WetDryMix";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoFeedback;
            pxUIElementCreateData.Name = "Sound_Echo_Feedback";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Feedback";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoLeftDelay;
            pxUIElementCreateData.Name = "Sound_EchoEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
            pxUIElementCreateData.UIElement.Data.Text.Content = "LeftDelay";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoRightDelay;
            pxUIElementCreateData.Name = "Sound_Echo_RightDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;
            pxUIElementCreateData.UIElement.Data.Text.Content = "RightDelay";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoPanDelay;
            pxUIElementCreateData.Name = "Sound_Echo_PanDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "PanDelay";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoWetDryMixInput;
            pxUIElementCreateData.Name = "Sound_Echo_WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoFeedbackInput;
            pxUIElementCreateData.Name = "Sound_Echo_Feedback";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoLeftDelayInput;
            pxUIElementCreateData.Name = "Sound_Echo_LeftDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoRightDelayInput;
            pxUIElementCreateData.Name = "Sound_Echo_RightDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;   

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoPanDelayInput;
            pxUIElementCreateData.Name = "Sound_Echo_PanDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }


    












    // Flange
    {


        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerEffect;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.6f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 13;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Flanger";

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerWetDryMix;
            pxUIElementCreateData.Name = "Sound_Flanger_WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.00f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
            pxUIElementCreateData.UIElement.Data.Text.Content = "WetDryMix";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerDepth;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.00f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Depth";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerFeedback;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.00f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Feedback";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerFrequency;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.00f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Frequency";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerWaveform;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.00f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Waveform";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerDelay;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.00f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Delay";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerPhase;
            pxUIElementCreateData.Name = "Sound_Flanger_Phase";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.00f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 7;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Phase";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerWetDryMixInput;
            pxUIElementCreateData.Name = "Sound_Flanger_WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerDepthInput;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerFeedbackInput;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerFrequencyInput;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerWaveformInput;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerDelayInput;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerPhaseInput;
            pxUIElementCreateData.Name = "Sound_Flanger_Phase";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 7;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }


    // Gargle
    {
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundGargleEffect;
            pxUIElementCreateData.Name = "Sound_Gargle";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 15.5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Gargle";

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundGargleRateHz;
            pxUIElementCreateData.Name = "Sound_Gargle_RateHz";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundGargleEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.00f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
            pxUIElementCreateData.UIElement.Data.Text.Content = "RateHz";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundGargleRateHzInput;
            pxUIElementCreateData.Name = "Sound_Gargle_WaveShape";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundGargleEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.00f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
            pxUIElementCreateData.UIElement.Data.Text.Content = "WaveShape";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundGargleWaveShape;
            pxUIElementCreateData.Name = "Sound_Gargle_RateHz";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundGargleEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundGargleWaveShapeInput;
            pxUIElementCreateData.Name = "Sound_Gargle_WaveShape";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundGargleEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }


    // Interactive3DLevel2Reverb
    {
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.6f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 21.5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Interactive3DLevel2Reverb";

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbRoom;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Room";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbRoomHF;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
            pxUIElementCreateData.UIElement.Data.Text.Content = "RoomHF";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
           
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbRoomRolloffFactor;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
            pxUIElementCreateData.UIElement.Data.Text.Content = "RoomRolloffFactor";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDecayTime;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;
            pxUIElementCreateData.UIElement.Data.Text.Content = "DecayTime";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDecayHFRatio;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "DecayHFRatio";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReflections;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Reflections";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReflectionsDelay;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 7;
            pxUIElementCreateData.UIElement.Data.Text.Content = "ReflectionsDelay";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReverb;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 8;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Reverb";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReverbDelay;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 9;
            pxUIElementCreateData.UIElement.Data.Text.Content = "ReverbDelay";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDiffusion;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 10;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Diffusion";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDensity;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 11;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Density";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbHFReference;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 12;
            pxUIElementCreateData.UIElement.Data.Text.Content = "HFReference";
            pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbRoomInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbRoomHFInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbRoomRolloffFactorInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDecayTimeInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDecayHFRatioInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReflectionsInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 6;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReflectionsDelayInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 7;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReverbInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 8;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReverbDelayInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 9;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDiffusionInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 10;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDensityInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 11;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbHFReferenceInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.UIElementParent = _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 12;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }




    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqEffect;
        pxUIElementCreateData.Name = "Sound_ParamEq";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 18.75;
        pxUIElementCreateData.UIElement.Data.Text.Content = "ParamEq";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqCenter;
        pxUIElementCreateData.Name = "Sound_ParamEq_Center";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Center";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqBandwidth;
        pxUIElementCreateData.Name = "Sound_ParamEq_Bandwidth";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Bandwidth";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqGain;
        pxUIElementCreateData.Name = "Sound_ParamEq_Gain";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Gain";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqCenterInput;
        pxUIElementCreateData.Name = "Sound_ParamEqEffect";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqBandwidthInput;
        pxUIElementCreateData.Name = "Sound_ParamEqEffect";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqGainInput;
        pxUIElementCreateData.Name = "Sound_ParamEqEffect";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


















    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbEffect;
        pxUIElementCreateData.Name = "Sound_WavesReverb";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 23;
        pxUIElementCreateData.UIElement.Data.Text.Content = "WavesReverb";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbInGain;
        pxUIElementCreateData.Name = "Sound_WavesReverbEffect_InGain";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
        pxUIElementCreateData.UIElement.Data.Text.Content = "InGain";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbReverbMix;
        pxUIElementCreateData.Name = "Sound_WavesReverbEffect_ReverbMix";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
        pxUIElementCreateData.UIElement.Data.Text.Content = "ReverbMix";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbReverbTime;
        pxUIElementCreateData.Name = "Sound_WavesReverbEffect_ReverbTime";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
        pxUIElementCreateData.UIElement.Data.Text.Content = "ReverbTime";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbHighFreqRTRatio;
        pxUIElementCreateData.Name = "Sound_WavesReverbEffect_HighFreqRTRatio";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;
        pxUIElementCreateData.UIElement.Data.Text.Content = "HighFreqRTRatio";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbInGainInput;
        pxUIElementCreateData.Name = "Sound_WavesReverbEffect_InGain";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 1;
        pxUIElementCreateData.UIElement.Data.Text.Content = "0";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbReverbMixInput;
        pxUIElementCreateData.Name = "Sound_WavesReverbEffect_ReverbMix";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 2;
        pxUIElementCreateData.UIElement.Data.Text.Content = "0";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {    
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbReverbTimeInput;
        pxUIElementCreateData.Name = "Sound_WavesReverbEffect_ReverbTime";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 3;
        pxUIElementCreateData.UIElement.Data.Text.Content = "1000";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbHighFreqRTRatioInput;
        pxUIElementCreateData.Name = "Sound_WavesReverbEffect_HighFreqRTRatio";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 4;
        pxUIElementCreateData.UIElement.Data.Text.Content = "0.1";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbApply;
        pxUIElementCreateData.Name = "Sound_WavesReverbEffect_OK";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.UIElementParent = _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = 55;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.60f;
        pxUIElementCreateData.UIElement.Position.MarginTop = SoundRowOffsetY * 5;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Apply";
        pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Chorus;
        pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //FLOAT   fInGain;                // [-96.0,0.0]            default: 0.0 dB
    //FLOAT   fReverbMix;             // [-96.0,0.0]            default: 0.0 db
    //FLOAT   fReverbTime;            // [0.001,3000.0]         default: 1000.0 ms
    //FLOAT   fHighFreqRTRatio;       // [0.001,0.999]          default: 0.001



    //-----------------------------------------------------
    // TAB::Database
    //-----------------------------------------------------
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbEffect;
        pxUIElementCreateData.Name = "Button_Database";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = 100;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.4;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.8f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.6f;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Connect";

       // PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

    }


#define DatabaseRowAWidth 135
#define DatabaseRowBWidth 250

    //-----------------------------------------------------
    // TAB::Database::
    //-----------------------------------------------------
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textDatabaseTitleODBC;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowAWidth;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.0;
        pxUIElementCreateData.UIElement.Data.Text.Content = "ODBC";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignCenter;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textDatabaseDriver;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowAWidth;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.1;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Driver";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_comboBoxDatabaseDriver;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeDropDown;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowBWidth;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.2f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.1;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);


        PXDataBaseInitialize(&pxEngine->DataBase);

        PXDataBaseScanForDrivers(&pxEngine->DataBase);

        PXGUIElementUpdateInfo pxGUIElementUpdateInfo;        
        
        PXClear(PXGUIElementUpdateInfo, &pxGUIElementUpdateInfo);

        pxGUIElementUpdateInfo.Property = PXUIElementPropertyComboBoxAdd;
        pxGUIElementUpdateInfo.UIElement = _comboBoxDatabaseDriver;
        pxGUIElementUpdateInfo.Data.ComboBox.DataList = pxEngine->DataBase.DriverList;
        pxGUIElementUpdateInfo.Data.ComboBox.DataListAmount = pxEngine->DataBase.DriverListAmount;

        PXGUIElementUpdate(&pxEngine->GUISystem, &pxGUIElementUpdateInfo, 1);
    }
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textBoxDatabaseIP;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowAWidth;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.2;
        pxUIElementCreateData.UIElement.Data.Text.Content = "IP";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_comboBoxDatabaseIP;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTextEdit;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowBWidth;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.2f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.2;
        pxUIElementCreateData.UIElement.Data.Text.Content = "127.0.0.1";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignLeft;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textBoxDatabasePort;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowAWidth;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.3;
        pxUIElementCreateData.UIElement.Data.Text.Content = "Port";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignRight;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_comboBoxDatabasePort;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTextEdit;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowBWidth;
        pxUIElementCreateData.UIElement.Position.Height = 35;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.2f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.3;
        pxUIElementCreateData.UIElement.Data.Text.Content = "25565";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignLeft;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }





    //-----------------------------------------------------
    // TAB::Network
    //-----------------------------------------------------
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_panelNetworkMain;
        pxUIElementCreateData.Name = "Button_Network";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageNetwork;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.0f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.6;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.8f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.2f;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Network";

    //    PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

    }













    //-----------------------------------------------------
    // Panel:Console
    //-----------------------------------------------------
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
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
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
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
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
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







#if 0
    //-----------------------------------------------------
    // ???
    //-----------------------------------------------------
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
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
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_panelLeftSceneElements;
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
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.Name = "Objects";
        pxUIElementCreateData.ObjectReference = &_textSceneElemenets;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.ColorTintReference = &textColor;
        pxUIElementCreateData.UIElement.UIElementParent = _panelLeftSceneElements;
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
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.Name = "Loaded Objects";
        pxUIElementCreateData.ObjectReference = &_treeViewObjects;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTreeView;
        pxUIElementCreateData.UIElement.UIElementParent = _panelLeftSceneElements;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementText;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft;
        pxUIElementCreateData.UIElement.Position.MarginLeft = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.1;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.305;
        pxUIElementCreateData.UIElement.InteractCallBack = BFObjectTreeViewEvent;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }

    //-----------------------------------------------------
    // Button
    //-----------------------------------------------------
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_infoPanelTextSpawn;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.ColorTintReference = &buttonColor;
        pxUIElementCreateData.UIElement.UIElementParent = _panelLeftSceneElements;
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
      //  pxUIElementCreateData.UIElement.InteractCallBack = PXOnUIElementInteract;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }




    //-----------------------------------------------------
    // Panel::Info::Bar
    //-----------------------------------------------------
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
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
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
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


#if 1
    //-----------------------------------------------------
    // Panel::Info::Bar
    //-----------------------------------------------------
    {
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelObjectText;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _uiInfoPanelTitleBar;
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
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelObjectName;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _uiInfoPanelTitleBar;
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
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelObjectNameContent;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _uiInfoPanelTitleBar;
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
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelObjectType;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _uiInfoPanelTitleBar;
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
       
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_uiInfoPanelObjectTypeContent;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.UIElementParent = _uiInfoPanelTitleBar;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.15f;
        pxUIElementCreateData.UIElement.Position.MarginTop = PXDefaultOffset + 0.3f;
        pxUIElementCreateData.UIElement.Position.MarginRight = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.MarginBottom = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Height = PXDefaultTitleBar;
        pxUIElementCreateData.UIElement.Data.Text.Content = "XXXXX";
        pxUIElementCreateData.UIElement.Data.Text.Allign = PXUIElementTextAllignLeft;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
#endif

    BFObjectTreeViewUpdate(bfBitFireIDE);   

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