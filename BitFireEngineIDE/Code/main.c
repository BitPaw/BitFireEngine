#include <PX/Engine/PXEngine.h>
#include <PX/Math/PXMath.h>
#include <PX/OS/Dialog/PXDialog.h>
#include <PX/OS/Hardware/PXProcessor.h>
#include <PX/OS/Memory/PXMemory.h>
#include <PX/OS/Console/PXConsole.h>
#include <PX/OS/Graphic/PXGraphic.h>
#include <PX/OS/File/PXDirectory.h>
#include <PX/OS/GUI/PXGUI.h>

#include "UI/BFEUIBehaviourTree.h"
#include "UI/BFEUIConsole.h"
#include "UI/BFEUIDataBase.h"
#include "UI/BFEUIFileView.h"
#include "UI/BFEUIFooter.h"
#include "UI/BFEUIHardware.h"
#include "UI/BFEUIHeader.h"
#include "UI/BFEUIInput.h"
#include "UI/BFEUINetwork.h"
#include "UI/BFEUIResourceInfo.h"
#include "UI/BFEUIResourceList.h"
#include "UI/BFEUIScene.h"
#include "UI/BFEUISound.h"
#include "UI/BFEUITab.h"
#include "UI/BFEUITimeline.h"
#include "UI/BFEUIVideo.h"




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








void PXAPI BFObjectTreeViewUpdate(BFBitFireIDE* const bfBitFireIDE);
void PXAPI BFInfoSelectUpdate(BFBitFireIDE* const bfBitFireIDE);




void PXAPI OnStartUpEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);
void PXAPI OnShutDownEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine);


void PXAPI PXOnEngineResourceAdded(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, void* const pxEngineResourceCreateInfo);

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
        //pxEngineStartInfo.OnUserUpdate = OnUserInputUpdate; // PXOnUserInputUpdateScene
        //pxEngineStartInfo.OnNetworkUpdate = OnNetworkUpdate;
        //pxEngineStartInfo.OnGameUpdate = OnGameUpdateEvent;
        pxEngineStartInfo.Name = "BitFireEngine";
        pxEngineStartInfo.Owner = &bfBitFireIDE;
        pxEngineStartInfo.UseMouseInput = 0;

        PXEngineStart(&bfBitFireIDE.EngineEditor, &pxEngineStartInfo);
    }

    while(PXEngineIsRunning(&bfBitFireIDE.EngineEditor))
    {
        PXEngineUpdate(&bfBitFireIDE.EngineEditor);
        PXEngineUpdate(&bfBitFireIDE.EngineScene);

#if OSWindows
        Sleep(10); // Temp solution
#endif
    }

    PXEngineStop(&bfBitFireIDE.EngineEditor);

    return 0;
}


/*

PXWindow* _windowScene = 0;


PXWindow* _statusbarMain = 0;
PXWindow* _menuMain = 0;


//---------------------------------------------------------
// Tab
//---------------------------------------------------------

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

PXWindow* _buttonSoundPlay = 0;
PXWindow* _buttonSoundStop = 0;


//---------------------------------------------------------
PXWindow* _textSoundChorusEffect = 0;

PXWindow* _textSoundChorusWetDryMix = 0;
PXWindow* _textSoundChorusDepth = 0;
PXWindow* _textSoundChorusFeedback = 0;
PXWindow* _textSoundChorusFrequency = 0;
PXWindow* _textSoundChorusWaveform = 0;
PXWindow* _textSoundChorusDelay = 0;
PXWindow* _textSoundChorusPhase = 0;

PXWindow* _textSoundChorusWetDryMixInput = 0;
PXWindow* _textSoundChorusDepthInput = 0;
PXWindow* _textSoundChorusFeedbackInput = 0;
PXWindow* _textSoundChorusFrequencyInput = 0;
PXWindow* _textSoundChorusWaveformInput = 0;
PXWindow* _textSoundChorusDelayInput = 0;
PXWindow* _textSoundChorusPhaseInput = 0;

PXWindow* _textSoundChorusEnable = 0;
PXWindow* _textSoundChorusApply = 0;
//---------------------------------------------------------
PXWindow* _textSoundCompressor = 0;

PXWindow* _textSoundCompressorGain = 0;
PXWindow* _textSoundCompressorAttack = 0;
PXWindow* _textSoundCompressorRelease = 0;
PXWindow* _textSoundCompressorThreshold = 0;
PXWindow* _textSoundCompressorRatio = 0;
PXWindow* _textSoundCompressorPredelay = 0;

PXWindow* _textSoundCompressorGainInput = 0;
PXWindow* _textSoundCompressorAttackInput = 0;
PXWindow* _textSoundCompressorReleaseInput = 0;
PXWindow* _textSoundCompressorThresholdInput = 0;
PXWindow* _textSoundCompressorRatioInput = 0;
PXWindow* _textSoundCompressorPredelayInput = 0;


PXWindow* _textSoundCompressorEnable = 0;
PXWindow* _textSoundCompressorApply = 0;
//---------------------------------------------------------
PXWindow* _textSoundDistortion = 0;

PXWindow* _textSoundDistortionGain = 0;
PXWindow* _textSoundDistortionEdge = 0;
PXWindow* _textSoundDistortionPostEQCenterFrequency = 0;
PXWindow* _textSoundDistortionPostEQBandwidth = 0;
PXWindow* _textSoundDistortionPreLowpassCutoff = 0;

PXWindow* _textSoundDistortionGainInput = 0;
PXWindow* _textSoundDistortionEdgeInput = 0;
PXWindow* _textSoundDistortionPostEQCenterFrequencyInput = 0;
PXWindow* _textSoundDistortionPostEQBandwidthInput = 0;
PXWindow* _textSoundDistortionPreLowpassCutoffInput = 0;

PXWindow* _textSoundDistortionEnable = 0;
PXWindow* _textSoundDistortionApply = 0;

//---------------------------------------------------------
PXWindow* _textSoundEchoEffect = 0;


PXWindow* _textSoundEchoWetDryMix = 0;
PXWindow* _textSoundEchoFeedback = 0;
PXWindow* _textSoundEchoLeftDelay = 0;
PXWindow* _textSoundEchoRightDelay = 0;
PXWindow* _textSoundEchoPanDelay = 0;

PXWindow* _textSoundEchoWetDryMixInput = 0;
PXWindow* _textSoundEchoFeedbackInput = 0;
PXWindow* _textSoundEchoLeftDelayInput = 0;
PXWindow* _textSoundEchoRightDelayInput = 0;
PXWindow* _textSoundEchoPanDelayInput = 0;

PXWindow* _textSoundEchoEnable = 0;
PXWindow* _textSoundEchoApply = 0;

//---------------------------------------------------------
PXWindow* _textSoundFlangerEffect = 0;

PXWindow* _textSoundFlangerWetDryMix = 0;
PXWindow* _textSoundFlangerDepth = 0;
PXWindow* _textSoundFlangerFeedback = 0;
PXWindow* _textSoundFlangerFrequency = 0;
PXWindow* _textSoundFlangerWaveform = 0;
PXWindow* _textSoundFlangerDelay = 0;
PXWindow* _textSoundFlangerPhase = 0;

PXWindow* _textSoundFlangerWetDryMixInput = 0;
PXWindow* _textSoundFlangerDepthInput = 0;
PXWindow* _textSoundFlangerFeedbackInput = 0;
PXWindow* _textSoundFlangerFrequencyInput = 0;
PXWindow* _textSoundFlangerWaveformInput = 0;
PXWindow* _textSoundFlangerDelayInput = 0;
PXWindow* _textSoundFlangerPhaseInput = 0;
//---------------------------------------------------------
PXWindow* _textSoundGargleEffect = 0;

PXWindow* _textSoundGargleRateHz = 0;
PXWindow* _textSoundGargleRateHzInput = 0;
PXWindow* _textSoundGargleWaveShape = 0;
PXWindow* _textSoundGargleWaveShapeInput = 0;
//---------------------------------------------------------
PXWindow* _textSoundInteractive3DLevel2ReverbEffect = 0;

PXWindow* _textSoundInteractive3DLevel2ReverbRoom = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbRoomHF = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbRoomRolloffFactor = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbDecayTime = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbDecayHFRatio = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbReflections = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbReflectionsDelay = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbReverb = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbReverbDelay = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbDiffusion = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbDensity = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbHFReference = 0;

PXWindow* _textSoundInteractive3DLevel2ReverbRoomInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbRoomHFInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbRoomRolloffFactorInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbDecayTimeInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbDecayHFRatioInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbReflectionsInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbReflectionsDelayInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbReverbInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbReverbDelayInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbDiffusionInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbDensityInput = 0;
PXWindow* _textSoundInteractive3DLevel2ReverbHFReferenceInput = 0;
//---------------------------------------------------------
PXWindow* _textSoundParamEqEffect = 0;

PXWindow* _textSoundParamEqCenter = 0;
PXWindow* _textSoundParamEqBandwidth = 0;
PXWindow* _textSoundParamEqGain = 0;
PXWindow* _textSoundParamEqCenterInput = 0;
PXWindow* _textSoundParamEqBandwidthInput = 0;
PXWindow* _textSoundParamEqGainInput = 0;
//---------------------------------------------------------
PXWindow* _textSoundWavesReverbEffect = 0;

PXWindow* _textSoundWavesReverbInGain = 0;
PXWindow* _textSoundWavesReverbReverbMix = 0;
PXWindow* _textSoundWavesReverbReverbTime = 0;
PXWindow* _textSoundWavesReverbHighFreqRTRatio = 0;

PXWindow* _textSoundWavesReverbInGainInput = 0;
PXWindow* _textSoundWavesReverbReverbMixInput = 0;
PXWindow* _textSoundWavesReverbReverbTimeInput = 0;
PXWindow* _textSoundWavesReverbHighFreqRTRatioInput = 0;

PXWindow* _textSoundWavesReverbApply = 0;
//---------------------------------------------------------

//---------------------------------------------------------
// Network
//---------------------------------------------------------
PXWindow* _panelNetworkMain = 0;
//---------------------------------------------------------


//---------------------------------------------------------
// Video
//---------------------------------------------------------
PXWindow* _panelVideoMain = 0;
//---------------------------------------------------------



//---------------------------------------------------------
// Database
//---------------------------------------------------------
PXWindow* _textDatabaseTitleODBC = 0;

PXWindow* _textDatabaseDriver = 0;
PXWindow* _comboBoxDatabaseDriver = 0;

PXWindow* _textBoxDatabaseIP = 0;
PXWindow* _comboBoxDatabaseIP = 0;

PXWindow* _textBoxDatabasePort = 0;
PXWindow* _comboBoxDatabasePort = 0;

PXWindow* _buttonDatabaseConnect = 0;
//---------------------------------------------------------



//---------------------------------------------------------
// Color picker
//---------------------------------------------------------
PXWindow* _colorPickerTest = 0;


//---------------------------------------------------------
// Frame console
//---------------------------------------------------------
PXWindow* _panelConsoleMain = 0;
PXWindow* _panelConsoleTextContent = 0;
PXWindow* _panelConsoleData = 0;
//---------------------------------------------------------

//---------------------------------------------------------
// Left, Object panel
//---------------------------------------------------------


PXWindow* _treeViewButtonSelect = 0;
PXWindow* _treeViewFileManager = 0;

PXWindow* _textFileData = 0;



PXWindow* _textSceneElemenets = 0;
PXWindow* _treeViewObjects = 0;
//---------------------------------------------------------


// Frame A

PXWindow* _panelMenuButtonFileText = 0;

PXWindow* _panelMenuButtonFileDropDownOpen = 0;
PXWindow* _panelMenuButtonFileDropDownSave = 0;
PXWindow* _panelMenuButtonEdit = 0;
PXWindow* _panelMenuButtonEditText = 0;
PXWindow* _panelMenuButtonView = 0;
PXWindow* _panelMenuButtonViewText = 0;



PXWindow* _panelMainContent = 0;




PXWindow* _uiPanelScene = 0;
PXWindow* _uiSceneTexturePanel = 0;
PXTexture2D* _uiSceneTexture = 0;

PXWindow* _uiInfoPanelTitleBar = 0;
PXWindow* _uiInfoPanelTitleBarText = 0;
PXWindow* _uiInfoPanelInfo = 0;
PXWindow* _uiInfoPositionText = 0;

PXWindow* _infoPanelImage = 0;
PXWindow* _infoPanelTextSpawn = 0;
PXWindow* _infoPanelText = 0;
PXWindow* _positionText = 0;


*/


PXFont* DefaultFont;



PXWindow* _textureTestA = 0;
PXTexture2D* _testImage = 0;
PXRenderable _pxRenderableModel;

// Frame Scene
PXInt32U _matrixModelID = 0;
PXInt32U _matrixViewID = 0;
PXInt32U _matrixProjectionID = 0;
PXInt32U _materialTextureID = 0;








const PXColorRGBAF titleMenuButtonTextColorReference = { 0.9, 0.9, 0.9, 1 };
const PXColorRGBAF titleMenuButtonReference = { 0.10, 0.10, 0.10, 1 };

const PXColorRGBAF buttonColor = { 0.1, 0.1, 0.1, 1 }; //  0.40f, 0.15f, 0.15f, 1
const PXColorRGBAF panelReference = { 0.0, 0.1, 0.2, 1 };
PXColorRGBAF titleColor = { 0.6, 0.6, 0.2, 1 };
const PXColorRGBAF textColor = { 0.8, 0.8, 0.8, 1 };
float animation = 0;


void PXAPI PXOnUserInputUpdateScene(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine, PXPlayerMoveInfo* const pxPlayerMoveInfo)
{
#if 0
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

#endif




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



void PXAPI FileTreeViewUpdate(BFBitFireIDE* const bfBitFireIDE)
{

}


void PXAPI BFObjectTreeViewUpdate(BFBitFireIDE* const bfBitFireIDE)
{
    PXEngine* const pxEngineEditor = &bfBitFireIDE->EngineEditor;
    PXEngine* const pxEngineScene = &bfBitFireIDE->EngineScene;

#if 0
    PXResourceCreateInfo pxResourceCreateInfo;

    // DOne UI Stuff

    {
        // Load data for UI
        {
            PXDictionary parentList;

            PXDictionaryConstruct(&parentList, sizeof(PXWindow*), sizeof(PXWindow*), PXDictionaryValueLocalityInternalEmbedded);


            PXDictionary* const uiElementLookup = &pxEngineEditor->ResourceManager->GUIElementLookup;

            PXWindow* uiAncer = 0;
            PXWindow* sceneAncer = 0;

            //  Create UI element, a container for the full UI things
            {
                PXWindow* uiElementItem = PXNull;

                PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                pxResourceCreateInfo.ObjectReference = &uiElementItem;
                pxResourceCreateInfo.Name = "UI";
                pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXResourceTypeCustom;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = PXNull;

                PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                PXDictionaryAdd(&parentList, &uiElementItem, &uiElementItem);

                uiAncer = uiElementItem;
            }

            // Create scene UI container elemenents
            {
                PXWindow* uiElementItem = PXNull;

                PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                pxResourceCreateInfo.ObjectReference = &uiElementItem;
                pxResourceCreateInfo.Name = "Scene";
                pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXResourceTypeCustom;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = PXNull;

                PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                PXDictionaryAdd(&parentList, &uiElementItem, &uiElementItem);

                // Add multible
                {
                    PXWindow* uiTreeViewItemModel = PXNull;
                    PXWindow* uiTreeViewItemShader = PXNull;
                    PXWindow* uiTreeViewItemImage = PXNull;


                    PXResourceCreateInfo pxUIElementCreateDataList[8];
                    PXClearList(PXResourceCreateInfo, pxUIElementCreateDataList, 8);
                    pxUIElementCreateDataList[0].Type = PXResourceTypeGUIElement;
                    pxUIElementCreateDataList[0].ObjectReference = &uiTreeViewItemModel;
                    pxUIElementCreateDataList[0].Name = "Model";
                    pxUIElementCreateDataList[0].UIElement.Type = PXUIElementTypeTreeViewItem;
                    pxUIElementCreateDataList[0].UIElement.Data.TreeViewItem.OwningObjectType = PXResourceTypeCustom;
                    pxUIElementCreateDataList[0].UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                    pxUIElementCreateDataList[0].UIElement.Data.TreeViewItem.ItemParent = uiElementItem;
                    pxUIElementCreateDataList[0].UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                    pxUIElementCreateDataList[1].Type = PXResourceTypeGUIElement;
                    pxUIElementCreateDataList[1].ObjectReference = &uiTreeViewItemShader;
                    pxUIElementCreateDataList[1].Name = "Shader";
                    pxUIElementCreateDataList[1].UIElement.Type = PXUIElementTypeTreeViewItem;
                    pxUIElementCreateDataList[1].UIElement.Data.TreeViewItem.OwningObjectType = PXResourceTypeCustom;
                    pxUIElementCreateDataList[1].UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                    pxUIElementCreateDataList[1].UIElement.Data.TreeViewItem.ItemParent = uiElementItem;
                    pxUIElementCreateDataList[1].UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                    pxUIElementCreateDataList[2].Type = PXResourceTypeGUIElement;
                    pxUIElementCreateDataList[2].ObjectReference = &uiTreeViewItemImage;
                    pxUIElementCreateDataList[2].Name = "Image";
                    pxUIElementCreateDataList[2].UIElement.Type = PXUIElementTypeTreeViewItem;
                    pxUIElementCreateDataList[2].UIElement.Data.TreeViewItem.OwningObjectType = PXResourceTypeCustom;
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
                        for(PXSize i = 0; i < bfBitFireIDE->EngineScene.ResourceManager->ModelLookUp.EntryAmountCurrent; i++)
                        {
                            PXDictionaryEntry pxDictionaryEntry;
                            PXModel* pxModel = PXNull;
                            PXWindow* uiEE = PXNull;

                            PXDictionaryIndex(&bfBitFireIDE->EngineScene.ResourceManager->ModelLookUp, i, &pxDictionaryEntry);

                            pxModel = *(PXModel**)pxDictionaryEntry.Value;


                            PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                            pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                            pxResourceCreateInfo.ObjectReference = &uiEE;
                            pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObject = pxModel;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXResourceTypeModel;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = uiTreeViewItemModel;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                            char buffer[256];
                            PXTextPrintA(buffer, 256, "[Model]");
                            pxResourceCreateInfo.Name = buffer;

                            PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                            PXDictionaryAdd(&parentList, &uiEE, &pxModel);
                        }

                        for(PXSize i = 0; i < bfBitFireIDE->EngineScene.ResourceManager->SpritelLookUp.EntryAmountCurrent; i++)
                        {
                            PXDictionaryEntry pxDictionaryEntry;
                            PXShaderProgram* pxShaderProgram = PXNull;
                            PXWindow* uiEE = PXNull;

                            PXDictionaryIndex(&bfBitFireIDE->EngineScene.ResourceManager->ShaderProgramLookup, i, &pxDictionaryEntry);

                            pxShaderProgram = *(PXShaderProgram**)pxDictionaryEntry.Value;

                            PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                            pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                            pxResourceCreateInfo.ObjectReference = &uiEE;
                            pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObject = pxShaderProgram;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXResourceTypeShaderProgram;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = uiTreeViewItemShader;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                            char buffer[256];
                            PXTextPrintA(buffer, 256, "[ShaderProgram]");
                            pxResourceCreateInfo.Name = buffer;

                            PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                            PXDictionaryAdd(&parentList, &uiEE, &pxShaderProgram);
                        }


                        for(PXSize i = 0; i < bfBitFireIDE->EngineScene.ResourceManager->ImageLookUp.EntryAmountCurrent; i++)
                        {
                            PXDictionaryEntry pxDictionaryEntry;
                            PXImage* pxImage = PXNull;
                            PXWindow* uiEE = PXNull;

                            PXDictionaryIndex(&bfBitFireIDE->EngineScene.ResourceManager->ImageLookUp, i, &pxDictionaryEntry);

                            pxImage = *(PXImage**)pxDictionaryEntry.Value;


                            PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                            pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                            pxResourceCreateInfo.ObjectReference = &uiEE;
                            pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObject = pxImage;
                            pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXResourceTypeImage;
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
                PXWindow* uiElement = PXNull;

                PXDictionaryIndex(uiElementLookup, i, &pxDictionaryEntry);

                uiElement = *(PXWindow**)pxDictionaryEntry.Value;

                PXWindow* uiElementItem = PXNull;

                PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
                pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
                pxResourceCreateInfo.ObjectReference = &uiElementItem;
                //pxResourceCreateInfo.Name = uiElement->NameData;
                pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeViewItem;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObject = uiElement;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.OwningObjectType = PXResourceTypeGUIElement;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                // Fetch parrant
                pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = uiAncer;

                if(uiElement->Info.Hierarchy.Parrent)
                {
                    PXWindow* aaaparentElement = (PXWindow*)uiElement->Info.Hierarchy.Parrent;
                    PXWindow* grandParentElement = PXNull;

                    const PXBool found = PXDictionaryFindEntry(&parentList, &aaaparentElement->Info.ID, &grandParentElement);

                    if(found)
                    {
                        pxResourceCreateInfo.UIElement.Data.TreeViewItem.ItemParent = grandParentElement;
                    }
                }

                PXEngineResourceCreate(pxEngineEditor, &pxResourceCreateInfo);

                PXDictionaryAdd(&parentList, &uiElement, &uiElementItem);
            }
        }




        // Add more?
    }

#endif


}

void PXAPI BFInfoSelectUpdate(BFBitFireIDE* const bfBitFireIDE)
{

}




/*

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
        case PXWindowEventTypeElementClick:
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
        case PXWindowEventTypeElementClick:
        {
            PXAudio* const pxAudio = &bfBitFireIDE->EngineEditor.Audio;

            pxAudio->DeviceStop(pxAudio->SystemReference, &_soundAudioDevice);

            break;
        }

        default:
            break;
    }
}

void PXMakeUIEnable(PXGUISystem* const pxGgui, PXAudio* pxAudio, PXAudioEffectType effect, int flag, PXWindow* button)
{
    PXAudioEffect pxAudioEffect;
    PXClear(PXAudioEffect, &pxAudioEffect);
    pxAudioEffect.Type = effect;
    pxAudioEffect.Enable = !(_soundAudioDevice.FXSettingFlagList & flag);

    pxAudio->DeviceEffectUpdate(pxAudio->SystemReference, &_soundAudioDevice, &pxAudioEffect);

  //  PXWindowUpdateInfo pxGUIElementUpdateInfo[3];
  //  PXClearList(PXWindowUpdateInfo, pxGUIElementUpdateInfo, 3);

  //  pxGUIElementUpdateInfo[0].Property = PXUIElementPropertyTextContent;
  //  pxGUIElementUpdateInfo[0].UIElement = button;

   // pxGUIElementUpdateInfo[1].Property = PXUIElementPropertyBackGroundColor;
  //  pxGUIElementUpdateInfo[1].UIElement = button;

    if(pxAudioEffect.Enable)
    {
        //pxGUIElementUpdateInfo[0].Data.Text.Content = "ON";
    }
    else
    {
       // pxGUIElementUpdateInfo[0].Data.Text.Content = "OFF";
    }

  //  PXWindowUpdate(pxGgui, pxGUIElementUpdateInfo, 2);
}

void PXAPI PXOnSoundEffectUpdate_Chorus_Toggle(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeElementClick:
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
        case PXWindowEventTypeElementClick:
        {
            PXWindow* aaa[7] =
            {
                _textSoundChorusWetDryMixInput,
                _textSoundChorusDepthInput,
                _textSoundChorusFeedbackInput,
                _textSoundChorusFrequencyInput,
                _textSoundChorusWaveformInput,
                _textSoundChorusDelayInput,
                _textSoundChorusPhaseInput
            };
            float ddd[7] = { 0,0,0,0,0,0,0 };

            PXWindowValueFetch(aaa, 7, PXUIElementPropertySliderPercentage, ddd);

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
        case PXWindowEventTypeElementClick:
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
        case PXWindowEventTypeElementClick:
        {
            PXWindow* aaa[6] =
            {
                _textSoundCompressorGainInput,
                _textSoundCompressorAttackInput,
                _textSoundCompressorReleaseInput,
                _textSoundCompressorThresholdInput,
                _textSoundCompressorRatioInput,
                _textSoundCompressorPredelayInput
            };
            float ddd[6] = { 0,0,0,0,0,0 };

            PXWindowValueFetch(aaa, 6, PXUIElementPropertySliderPercentage, ddd);

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
        case PXWindowEventTypeElementClick:
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
        case PXWindowEventTypeElementClick:
        {
            PXWindow* aaa[5] =
            {
                _textSoundDistortionGainInput,
                _textSoundDistortionEdgeInput,
                _textSoundDistortionPostEQCenterFrequencyInput,
                _textSoundDistortionPostEQBandwidthInput,
                _textSoundDistortionPreLowpassCutoffInput
            };
            float ddd[5] = { 0,0,0,0,0 };

            PXWindowValueFetch(aaa, 5, PXUIElementPropertySliderPercentage, ddd);

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
        case PXWindowEventTypeElementClick:
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
        case PXWindowEventTypeElementClick:
        {
            PXWindow* aaa[5] =
            {
                _textSoundEchoWetDryMixInput,
                _textSoundEchoFeedbackInput,
                _textSoundEchoLeftDelayInput,
                _textSoundEchoRightDelayInput,
                _textSoundEchoPanDelayInput
            };
            float ddd[5] = { 0,0,0,0,0 };

            PXWindowValueFetch(aaa, 5, PXUIElementPropertySliderPercentage, ddd);

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
        case PXWindowEventTypeElementClick:
        {
            PXWindow* aaa[7] =
            {
                _textSoundFlangerWetDryMixInput,
                _textSoundFlangerDepthInput,
                _textSoundFlangerFeedbackInput,
                _textSoundFlangerFrequencyInput,
                _textSoundFlangerWaveformInput,
                _textSoundFlangerDelayInput,
                _textSoundFlangerPhaseInput
            };
            float ddd[7] = { 0,0,0,0,0,0,0 };

            PXWindowValueFetch(aaa, 7, PXUIElementPropertySliderPercentage, ddd);

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
        case PXWindowEventTypeElementClick:
        {
            PXWindow* aaa[2] =
            {
                _textSoundGargleRateHzInput,
                _textSoundGargleWaveShapeInput
            };
            float ddd[2] = { 0,0 };

            PXWindowValueFetch(aaa, 2, PXUIElementPropertySliderPercentage, ddd);

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
        case PXWindowEventTypeElementClick:
        {
            PXWindow* aaa[4] =
            {
                _textSoundWavesReverbInGainInput,
                _textSoundWavesReverbReverbMixInput,
                _textSoundWavesReverbReverbTimeInput,
                _textSoundWavesReverbHighFreqRTRatioInput,
            };
            float ddd[4] = { 0,0,0,0 };

            PXWindowValueFetch(aaa, 4, PXUIElementPropertySliderPercentage, ddd);

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

*/





BFEUISound _bfeUISound;
BFEUIConsole _bfeUIConsole;
BFEUIFooter _bfeUIFooter;
BFEUIHeader _bfeUIHeader;
BFEUITab _bfeUITab;
BFEUIScene _bfeUISceneCreate;
BFEUIFileView _bfeUIFileView;
BFEUIResourceInfo _bfeUIResourceInfo;
BFEUIResourceList _bfeUIResourceList;


PXWindow* _panelLeftPanel = 0;
PXWindow* _panelLeftSceneElements = 0;
PXWindow* _panelFilemenu = 0;


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
   // Panel:Left (Left one)
   //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_panelLeftPanel;
        pxUIElementCreateData.Name = "Panel-Left";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.ColorTintReference = &panelReference;
        pxUIElementCreateData.UIElement.WindowParent = pxEngine->Window; // _tabControlMain
        pxUIElementCreateData.UIElement.Setting = PXResourceInfoNoRender | PXWindowAllignLeft | PXWindowBehaviourBorder;
        pxUIElementCreateData.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Margin.Top = PXDefaultTopOffset;
        pxUIElementCreateData.UIElement.Position.Margin.Right = 1.60f;
        pxUIElementCreateData.UIElement.Position.Margin.Bottom = PXDefaultBotOffset;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


    //-----------------------------------------------------
    // SceneElements - Base
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_panelLeftSceneElements;
        pxUIElementCreateData.Name = "Container-Left.Upper";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.ColorTintReference = &panelReference;
        pxUIElementCreateData.UIElement.WindowParent = _panelLeftPanel;
        pxUIElementCreateData.UIElement.Setting = PXWindowBehaviourBorder | PXWindowAllignLeft;
        pxUIElementCreateData.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Margin.Top = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Margin.Bottom = 0.85;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


    //-----------------------------------------------------
    // FileTreeView - Base
    //-----------------------------------------------------
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_panelFilemenu;
        pxUIElementCreateData.Name = "Container-Left.Lower";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypePanel;
        pxUIElementCreateData.UIElement.ColorTintReference = &panelReference;
        pxUIElementCreateData.UIElement.WindowParent = _panelLeftPanel;
        pxUIElementCreateData.UIElement.Setting = PXWindowBehaviourBorder | PXWindowAllignLeft;
        pxUIElementCreateData.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.85;
        pxUIElementCreateData.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxUIElementCreateData.UIElement.Position.Margin.Bottom = PXDefaultOffset;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    BFEUIFooterCreate(&_bfeUIFooter, pxEngine, PXNull);
    BFEUIHeaderCreate(&_bfeUIHeader, pxEngine, PXNull);
    BFEUIConsoleCreate(&_bfeUIConsole, pxEngine); 

    BFEUIFileViewCreate(&_bfeUIFileView, pxEngine, _panelFilemenu);

    BFEUIResourceInfoCreate(&_bfeUIResourceInfo, pxEngine);
    BFEUIResourceListCreate(&_bfeUIResourceList, pxEngine, _panelLeftSceneElements);

    BFEUITabCreate(&_bfeUITab, pxEngine);


    BFEUISceneCreate(&_bfeUISceneCreate, &bfBitFireIDE->EngineScene, _bfeUITab.PageScene); // 







#if 1

 




#if 0
#pragma region [Sound]

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
        pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;
        pxUIElementCreateData.UIElement.Position.Width = 35;
        pxUIElementCreateData.UIElement.Position.Form.Height = 35;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.95f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.0;
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
        pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
        pxUIElementCreateData.UIElement.Position.Width = 35;
        pxUIElementCreateData.UIElement.Position.Form.Height = 35;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 1.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.0;
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
            pxUIElementCreateData.Name = "Chorus";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth-100;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 0;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusEnable;
            pxUIElementCreateData.Name = "Sound_ChorusEffect_Phase";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = 35;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.40;
            pxUIElementCreateData.UIElement.Position.Margin.Top = 0;
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
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = 70;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.45;
            pxUIElementCreateData.UIElement.Position.Margin.Top = 0;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Apply";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Chorus;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusWetDryMix;
            pxUIElementCreateData.Name = "WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusDepth;
            pxUIElementCreateData.Name = "Depth";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusFeedback;
            pxUIElementCreateData.Name = "Feedback";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusFrequency;
            pxUIElementCreateData.Name = "Frequency";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusWaveform;
            pxUIElementCreateData.Name = "Waveform";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusDelay;
            pxUIElementCreateData.Name = "Delay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusPhase;
            pxUIElementCreateData.Name = "Phase";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 7;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusWetDryMixInput;
            pxUIElementCreateData.Name = "WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusDepthInput;
            pxUIElementCreateData.Name = "Depth";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusFeedbackInput;
            pxUIElementCreateData.Name = "Feedback";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusFrequencyInput;
            pxUIElementCreateData.Name = "Frequency";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusWaveformInput;
            pxUIElementCreateData.Name = "Waveform";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusDelayInput;
            pxUIElementCreateData.Name = "Delay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundChorusPhaseInput;
            pxUIElementCreateData.Name = "Phase";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundChorusEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 7;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }

    // Compressor
    {
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressor;
            pxUIElementCreateData.Name = "Compressor";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 8.25;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorEnable;
            pxUIElementCreateData.Name = "Compressor_Toggle";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = 35;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.40;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 8.25;
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
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = 70;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.45;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 8.25;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Apply";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Compressor;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorGain;
            pxUIElementCreateData.Name = "Gain";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorAttack;
            pxUIElementCreateData.Name = "Attack";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorRelease;
            pxUIElementCreateData.Name = "Release";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorThreshold;
            pxUIElementCreateData.Name = "Threshold";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorRatio;
            pxUIElementCreateData.Name = "Ratio";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorPredelay;
            pxUIElementCreateData.Name = "Predelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorGainInput;
            pxUIElementCreateData.Name = "Gain";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorAttackInput;
            pxUIElementCreateData.Name = "Attack";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorReleaseInput;
            pxUIElementCreateData.Name = "Release";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorThresholdInput;
            pxUIElementCreateData.Name = "Threshold";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorRatioInput;
            pxUIElementCreateData.Name = "Ratio";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundCompressorPredelayInput;
            pxUIElementCreateData.Name = "Predelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundCompressor;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }

    // Distortion
    {
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortion;
            pxUIElementCreateData.Name = "Distortion";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.6f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 0;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionEnable;
            pxUIElementCreateData.Name = "Compressor_Toggle";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = 35;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.6 + 0.40;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 0;
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
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = 70;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.6 + 0.45;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 0;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Apply";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Distortion;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionGain;
            pxUIElementCreateData.Name = "Gain";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionEdge;
            pxUIElementCreateData.Name = "Edge";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPostEQCenterFrequency;
            pxUIElementCreateData.Name = "PostEQCenterFrequency";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPostEQBandwidth;
            pxUIElementCreateData.Name = "PostEQBandwidth";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPreLowpassCutoff;
            pxUIElementCreateData.Name = "PreLowpassCutoff";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionGainInput;
            pxUIElementCreateData.Name = "Sound_Distortion_Gain";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionEdgeInput;
            pxUIElementCreateData.Name = "Sound_Distortion_Edge";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPostEQCenterFrequencyInput;
            pxUIElementCreateData.Name = "Sound_Distortion_PostEQCenterFrequency";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPostEQBandwidthInput;
            pxUIElementCreateData.Name = "Sound_Distortion_PostEQBandwidth";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundDistortionPreLowpassCutoffInput;
            pxUIElementCreateData.Name = "Sound_Distortion_PreLowpassCutoff";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundDistortion;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }







    // Sound_Echo
    {
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoEffect;
            pxUIElementCreateData.Name = "Echo";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.6f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6.5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoEnable;
            pxUIElementCreateData.Name = "Echo_Toggle";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = 35;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.6 + 0.40;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6.5;
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
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = 70;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.6 + 0.45;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6.5;
            pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Apply";
            pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Echo;
            pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoWetDryMix;
            pxUIElementCreateData.Name = "WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoFeedback;
            pxUIElementCreateData.Name = "Feedback";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoLeftDelay;
            pxUIElementCreateData.Name = "LeftDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoRightDelay;
            pxUIElementCreateData.Name = "RightDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoPanDelay;
            pxUIElementCreateData.Name = "PanDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoWetDryMixInput;
            pxUIElementCreateData.Name = "Sound_Echo_WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoFeedbackInput;
            pxUIElementCreateData.Name = "Sound_Echo_Feedback";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoLeftDelayInput;
            pxUIElementCreateData.Name = "Sound_Echo_LeftDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoRightDelayInput;
            pxUIElementCreateData.Name = "Sound_Echo_RightDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundEchoPanDelayInput;
            pxUIElementCreateData.Name = "Sound_Echo_PanDelay";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundEchoEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }












#if 0


    // Flange
    {


        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerEffect;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.6f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 13;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Flanger";

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerWetDryMix;
            pxUIElementCreateData.Name = "Sound_Flanger_WetDryMix";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.00f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.00f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.00f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.00f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.00f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.00f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.00f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 7;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerDepthInput;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerFeedbackInput;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerFrequencyInput;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerWaveformInput;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerDelayInput;
            pxUIElementCreateData.Name = "Sound_FlangerEffect";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundFlangerPhaseInput;
            pxUIElementCreateData.Name = "Sound_Flanger_Phase";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundFlangerEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 7;

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
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 15.5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Gargle";

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundGargleRateHz;
            pxUIElementCreateData.Name = "Sound_Gargle_RateHz";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundGargleEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.00f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundGargleEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.00f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundGargleEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundGargleWaveShapeInput;
            pxUIElementCreateData.Name = "Sound_Gargle_WaveShape";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundGargleEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

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
            pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.6f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 21.5;
            pxUIElementCreateData.UIElement.Data.Text.Content = "Interactive3DLevel2Reverb";

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {

            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbRoom;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 7;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 8;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 9;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 10;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 11;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 12;
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
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbRoomHFInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbRoomRolloffFactorInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDecayTimeInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDecayHFRatioInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReflectionsInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 6;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReflectionsDelayInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 7;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReverbInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 8;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbReverbDelayInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 9;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDiffusionInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 10;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbDensityInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 11;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
        {
            PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
            pxUIElementCreateData.Type = PXResourceTypeGUIElement;
            pxUIElementCreateData.ObjectReference = &_textSoundInteractive3DLevel2ReverbHFReferenceInput;
            pxUIElementCreateData.Name = "Sound_Interactive3DLevel2Reverb";
            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
            pxUIElementCreateData.UIElement.WindowParent= _textSoundInteractive3DLevel2ReverbEffect;
            pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
            pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
            pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
            pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
            pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
            pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
            pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
            pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 12;

            PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
        }
    }




    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqEffect;
        pxUIElementCreateData.Name = "Sound_ParamEq";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 18.75;
        pxUIElementCreateData.UIElement.Data.Text.Content = "ParamEq";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqCenter;
        pxUIElementCreateData.Name = "Sound_ParamEq_Center";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.WindowParent= _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqBandwidthInput;
        pxUIElementCreateData.Name = "Sound_ParamEqEffect";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
        pxUIElementCreateData.UIElement.WindowParent= _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundParamEqGainInput;
        pxUIElementCreateData.Name = "Sound_ParamEqEffect";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTrackBar;
        pxUIElementCreateData.UIElement.WindowParent= _textSoundParamEqEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


















    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbEffect;
        pxUIElementCreateData.Name = "Sound_WavesReverb";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageSound;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 23;
        pxUIElementCreateData.UIElement.Data.Text.Content = "WavesReverb";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbInGain;
        pxUIElementCreateData.Name = "Sound_WavesReverbEffect_InGain";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.WindowParent= _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowA;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 1;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 2;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 3;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidthRowB;
        pxUIElementCreateData.UIElement.Position.Form.Height = SoundHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = SoundRowOffsetX1;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 4;
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
        pxUIElementCreateData.UIElement.WindowParent= _textSoundWavesReverbEffect;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop | PXUIElementKeepWidth | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Width = 55;
        pxUIElementCreateData.UIElement.Position.Form.Height = 35;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.60f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 5;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Apply";
        pxUIElementCreateData.UIElement.InteractCallBack = PXOnSoundEffectUpdate_Chorus;
        pxUIElementCreateData.UIElement.InteractOwner = bfBitFireIDE;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }



    //FLOAT   fInGain;                // [-96.0,0.0]            default: 0.0 dB
    //FLOAT   fReverbMix;             // [-96.0,0.0]            default: 0.0 db
    //FLOAT   fReverbTime;            // [0.001,3000.0]         default: 1000.0 ms
    //FLOAT   fHighFreqRTRatio;       // [0.001,0.999]          default: 0.001

#endif

#pragma endregion
#endif


#pragma region [DataBase]
#if 0



    //-----------------------------------------------------
    // TAB::Database
    //-----------------------------------------------------
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundWavesReverbEffect;
        pxUIElementCreateData.Name = "Button_Database";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowBehaviourDefaultKeepAspect;
        pxUIElementCreateData.UIElement.Position.Width = 100;
        pxUIElementCreateData.UIElement.Position.Form.Height = 35;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.4;
        pxUIElementCreateData.UIElement.Position.Margin.Right = 0.8f;
        pxUIElementCreateData.UIElement.Position.Margin.Bottom = 0.6f;
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
        pxUIElementCreateData.Name = "ODBC";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowBehaviourDefaultKeepAspect;;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowAWidth;
        pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.0;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textDatabaseDriver;
        pxUIElementCreateData.Name = "Driver";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowBehaviourDefaultKeepAspect;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowAWidth;
        pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.1;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_comboBoxDatabaseDriver;
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeDropDown;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowBehaviourDefaultKeepAspect;;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowBWidth;
        pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.2f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.1;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);


        PXDataBaseInitialize(&pxEngine->DataBase);

        PXDataBaseScanForDrivers(&pxEngine->DataBase);
    }
#endif
#pragma endregion



#if 0
        PXWindowUpdateInfo pxGUIElementUpdateInfo;

        PXClear(PXWindowUpdateInfo, &pxGUIElementUpdateInfo);

        pxGUIElementUpdateInfo.Property = PXUIElementPropertyComboBoxAdd;
        pxGUIElementUpdateInfo.UIElement = _comboBoxDatabaseDriver;
        pxGUIElementUpdateInfo.Data.ComboBox.DataList = pxEngine->DataBase.DriverList;
        pxGUIElementUpdateInfo.Data.ComboBox.DataListAmount = pxEngine->DataBase.DriverListAmount;

        PXWindowUpdate(&pxEngine->GUISystem, &pxGUIElementUpdateInfo, 1);
#endif



#if 0
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textBoxDatabaseIP;
        pxUIElementCreateData.Name = "IP";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowBehaviourDefaultKeepAspect;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowAWidth;
        pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.2;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_comboBoxDatabaseIP;
        pxUIElementCreateData.Name = "127.0.0.1";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTextEdit;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowBehaviourDefaultKeepAspect;;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowBWidth;
        pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.2f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.2;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textBoxDatabasePort;
        pxUIElementCreateData.Name = "Port";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowBehaviourDefaultKeepAspect;;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowAWidth;
        pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.3;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_comboBoxDatabasePort;
        pxUIElementCreateData.Name = "25565";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeTextEdit;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageDatabase;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowBehaviourDefaultKeepAspect;
        pxUIElementCreateData.UIElement.Position.Width = DatabaseRowBWidth;
        pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.2f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.3;

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
        pxUIElementCreateData.UIElement.WindowParent= _tabPageNetwork;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowKeepWidth | PXWindowKeepHeight | PXWindowAllignTop;;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.6;
        pxUIElementCreateData.UIElement.Position.Margin.Right = 0.2f;
        pxUIElementCreateData.UIElement.Position.Margin.Bottom = 0.2f;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Network";

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

    }
#endif


#if 0
    {

        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_colorPickerTest;
        pxUIElementCreateData.Name = "Color picker";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeColorPicker;
        pxUIElementCreateData.UIElement.WindowParent= _tabPageNetwork;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultDecorative | PXWindowAllignTop | PXResourceInfoUseByEngine;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = 0.0;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
#endif

#if 0
    {
        PXClear(PXResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.Type = PXResourceTypeGUIElement;
        pxUIElementCreateData.ObjectReference = &_textSoundCompressor;
        pxUIElementCreateData.Name = "Compressor";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeText;
        pxUIElementCreateData.UIElement.WindowParent = _tabPageSound;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXWindowBehaviourDefaultText;
        pxUIElementCreateData.UIElement.Position.Width = SoundWidth;
        pxUIElementCreateData.UIElement.Position.Form.Height = PXDefaultTextHeight;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.0f;
        pxUIElementCreateData.UIElement.Position.Margin.Top = SoundRowOffsetY * 8.25;

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
        pxUIElementCreateData.UIElement.WindowParent= pxEngine->Window;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleMenuButtonReference;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementNormal;
        pxUIElementCreateData.UIElement.StyleFlagList = PXWindowStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignLeft | PXUIElementKeepHeight;
        pxUIElementCreateData.UIElement.Position.Form.Height = 35;
        pxUIElementCreateData.UIElement.Position.Margin.Left = 0.5f;
        pxUIElementCreateData.UIElement.Position.Margin.Right = 0.5f;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Edit";
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.FontID = DefaultFont;

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }
#endif




   

#endif







    BFObjectTreeViewUpdate(bfBitFireIDE);
}

void PXAPI OnShutDownEvent(BFBitFireIDE* const bfBitFireIDE, PXEngine* const pxEngine)
{

}

