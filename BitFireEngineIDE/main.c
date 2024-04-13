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
//---------------------------------------------------------

//---------------------------------------------------------
// Scene
//---------------------------------------------------------

//---------------------------------------------------------

//---------------------------------------------------------
// Sound
PXUIElement* _panelSoundMain = 0;
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
            PXGUIElementUpdateInfo pxGUIElementUpdateInfo;
            PXClear(PXGUIElementUpdateInfo, &pxGUIElementUpdateInfo);
            pxGUIElementUpdateInfo.Show = PXFalse;
            pxGUIElementUpdateInfo.UIElement = _tabPageSound;
            pxGUIElementUpdateInfo.Property = PXUIElementPropertyVisibility;

            PXGUIElementUpdate(&bfBitFireIDE->EngineEditor.GUISystem, &pxGUIElementUpdateInfo, 1);

  

            PXUIElement* const uiElementSelected = pxWindowEvent->UIElementSender;

            PXLogPrint
            (
                PXLoggingInfo,
                "BF",
                "Event",
                "Select: <%s>",
                uiElementSelected->NameData
            );


           // _uiInfoPanelObjectNameContent->TextInfo.Content = pxUIElementInteractInfo->UIElementSelected->NameData;

            //const char* typeName = PXUIElementTypeToString(uiElementSelected->Type);

           // _uiInfoPanelObjectTypeContent->TextInfo.Content = typeName;

            PXGUIElementUpdateInfo pxUIElementUpdateInfo[2];
            PXClearList(PXGUIElementUpdateInfo, pxUIElementUpdateInfo, 2);

            pxUIElementUpdateInfo[0].UIElement = _uiInfoPanelObjectNameContent;
            pxUIElementUpdateInfo[0].WindowReference = &bfBitFireIDE->EngineEditor.Window;
            pxUIElementUpdateInfo[0].Property = PXUIElementPropertyTextContent;
            pxUIElementUpdateInfo[0].Data.Text.Content = _uiInfoPanelObjectNameContent->NameData;

            pxUIElementUpdateInfo[1].UIElement = _uiInfoPanelObjectTypeContent;
            pxUIElementUpdateInfo[1].WindowReference = &bfBitFireIDE->EngineEditor.Window;
            pxUIElementUpdateInfo[1].Property = PXUIElementPropertyTextContent;
            pxUIElementUpdateInfo[1].Data.Text.Content = _uiInfoPanelObjectTypeContent->NameData;

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

    // DOne UI Stuff

    {
        // Load data for UI
        {
            PXDictionary parentList;

            PXDictionaryConstruct(&parentList, sizeof(PXUIElement*), sizeof(PXUIElement*), PXDictionaryValueLocalityInternalEmbedded);


            PXDictionary* const uiElementLookup = &pxEngineEditor->GUISystem.UIElementLookUp;

            PXUIElement* uiAncer = 0;
            PXUIElement* sceneAncer = 0;

            //  Create UI element, a container for the full UI things
            {
                PXUIElement* uiElementItem = PXNull;

                PXEngineResourceCreateInfo pxUIElementCreateData;
                PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
                pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
                pxUIElementCreateData.ObjectReference = &uiElementItem;
                pxUIElementCreateData.Name = "UI";
                pxUIElementCreateData.UIElement.Type = PXUIElementTypeTreeViewItem;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeEmpty;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.ItemParent = PXNull;

                PXEngineResourceCreate(pxEngineEditor, &pxUIElementCreateData);

                PXDictionaryAdd(&parentList, &uiElementItem, &uiElementItem);

                uiAncer = uiElementItem;
            }

            // Create scene UI container elemenents
            {
                PXUIElement* uiElementItem = PXNull;

                PXEngineResourceCreateInfo pxUIElementCreateData;
                PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
                pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
                pxUIElementCreateData.ObjectReference = &uiElementItem;
                pxUIElementCreateData.Name = "Scene";
                pxUIElementCreateData.UIElement.Type = PXUIElementTypeTreeViewItem;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeEmpty;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.ItemParent = PXNull;

                PXEngineResourceCreate(pxEngineEditor, &pxUIElementCreateData);

                PXDictionaryAdd(&parentList, &uiElementItem, &uiElementItem);

                // Add multible 
                {
                    PXUIElement* uiTreeViewItemModel = PXNull;
                    PXUIElement* uiTreeViewItemShader = PXNull;
                    PXUIElement* uiTreeViewItemImage = PXNull;


                    PXEngineResourceCreateInfo pxUIElementCreateData[8];
                    PXClearList(PXEngineResourceCreateInfo, &pxUIElementCreateData, 8);
                    pxUIElementCreateData[0].CreateType = PXEngineCreateTypeUIElement;
                    pxUIElementCreateData[0].ObjectReference = &uiTreeViewItemModel;
                    pxUIElementCreateData[0].Name = "Model";
                    pxUIElementCreateData[0].UIElement.Type = PXUIElementTypeTreeViewItem;
                    pxUIElementCreateData[0].UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeEmpty;
                    pxUIElementCreateData[0].UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                    pxUIElementCreateData[0].UIElement.Data.TreeViewItem.ItemParent = uiElementItem;
                    pxUIElementCreateData[0].UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                    pxUIElementCreateData[1].CreateType = PXEngineCreateTypeUIElement;
                    pxUIElementCreateData[1].ObjectReference = &uiTreeViewItemShader;
                    pxUIElementCreateData[1].Name = "Shader";
                    pxUIElementCreateData[1].UIElement.Type = PXUIElementTypeTreeViewItem;
                    pxUIElementCreateData[1].UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeEmpty;
                    pxUIElementCreateData[1].UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                    pxUIElementCreateData[1].UIElement.Data.TreeViewItem.ItemParent = uiElementItem;
                    pxUIElementCreateData[1].UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                    pxUIElementCreateData[2].CreateType = PXEngineCreateTypeUIElement;
                    pxUIElementCreateData[2].ObjectReference = &uiTreeViewItemImage;
                    pxUIElementCreateData[2].Name = "Image";
                    pxUIElementCreateData[2].UIElement.Type = PXUIElementTypeTreeViewItem;
                    pxUIElementCreateData[2].UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeEmpty;
                    pxUIElementCreateData[2].UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                    pxUIElementCreateData[2].UIElement.Data.TreeViewItem.ItemParent = uiElementItem;
                    pxUIElementCreateData[2].UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;


                    for(size_t i = 0; i < 3; i++)
                    {
                        PXEngineResourceCreateInfo* pxEngineResourceCreateInfo = &pxUIElementCreateData[i];

                        PXEngineResourceCreate(pxEngineEditor, pxEngineResourceCreateInfo);

                        PXDictionaryAdd(&parentList, &pxEngineResourceCreateInfo->ObjectReference, &pxEngineResourceCreateInfo->ObjectReference);
                    }


                    if(bfBitFireIDE->EngineScene.IsRunning)
                    {
                        for(PXSize i = 0; i < bfBitFireIDE->EngineScene.ModelLookUp.EntryAmountCurrent; i++)
                        {
                            PXDictionaryEntry pxDictionaryEntry;
                            PXModel* pxModel = PXNull;
                            PXUIElement* uiEE = PXNull;

                            PXDictionaryIndex(&bfBitFireIDE->EngineScene.ModelLookUp, i, &pxDictionaryEntry);

                            pxModel = *(PXModel**)pxDictionaryEntry.Value;



                            PXEngineResourceCreateInfo pxUIElementCreateData;
                            PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
                            pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
                            pxUIElementCreateData.ObjectReference = &uiEE;
                            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTreeViewItem;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.OwningObject = pxModel;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeModel;;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.ItemParent = uiTreeViewItemModel;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                            char buffer[256];
                            PXTextPrintA(buffer, 256, "[Model]");
                            pxUIElementCreateData.Name = buffer;

                            PXEngineResourceCreate(pxEngineEditor, &pxUIElementCreateData);

                            PXDictionaryAdd(&parentList, &uiEE, &pxModel);
                        }

                        for(PXSize i = 0; i < bfBitFireIDE->EngineScene.ShaderProgramLookup.EntryAmountCurrent; i++)
                        {
                            PXDictionaryEntry pxDictionaryEntry;
                            PXShaderProgram* pxShaderProgram = PXNull;
                            PXUIElement* uiEE = PXNull;

                            PXDictionaryIndex(&bfBitFireIDE->EngineScene.ShaderProgramLookup, i, &pxDictionaryEntry);

                            pxShaderProgram = *(PXShaderProgram**)pxDictionaryEntry.Value;



                            PXEngineResourceCreateInfo pxUIElementCreateData;
                            PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
                            pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
                            pxUIElementCreateData.ObjectReference = &uiEE;
                            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTreeViewItem;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.OwningObject = pxShaderProgram;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeRenderShader;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.ItemParent = uiTreeViewItemShader;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                            char buffer[256];
                            PXTextPrintA(buffer, 256, "[ShaderProgram]");
                            pxUIElementCreateData.Name = buffer;

                            PXEngineResourceCreate(pxEngineEditor, &pxUIElementCreateData);

                            PXDictionaryAdd(&parentList, &uiEE, &pxShaderProgram);
                        }


                        for(PXSize i = 0; i < bfBitFireIDE->EngineScene.ImageLookUp.EntryAmountCurrent; i++)
                        {
                            PXDictionaryEntry pxDictionaryEntry;
                            PXImage* pxImage = PXNull;
                            PXUIElement* uiEE = PXNull;

                            PXDictionaryIndex(&bfBitFireIDE->EngineScene.ImageLookUp, i, &pxDictionaryEntry);

                            pxImage = *(PXImage**)pxDictionaryEntry.Value;



                            PXEngineResourceCreateInfo pxUIElementCreateData;
                            PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
                            pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
                            pxUIElementCreateData.ObjectReference = &uiEE;
                            pxUIElementCreateData.UIElement.Type = PXUIElementTypeTreeViewItem;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.OwningObject = pxImage;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeImage;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.ItemParent = uiTreeViewItemImage;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                            pxUIElementCreateData.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                            char buffer[256];
                            PXTextPrintA(buffer, 256, "[Image]");
                            pxUIElementCreateData.Name = buffer;

                            PXEngineResourceCreate(pxEngineEditor, &pxUIElementCreateData);

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

                PXEngineResourceCreateInfo pxUIElementCreateData;
                PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
                pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
                pxUIElementCreateData.ObjectReference = &uiElementItem;
                pxUIElementCreateData.Name = uiElement->NameData;
                pxUIElementCreateData.UIElement.Type = PXUIElementTypeTreeViewItem;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.OwningObject = uiElement;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.OwningObjectType = PXFileResourceTypeUI;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.TreeView = _treeViewObjects;
                pxUIElementCreateData.UIElement.Data.TreeViewItem.InsertMode = PXUIElementTreeViewItemInsertModeLAST;

                // Fetch parrant
                pxUIElementCreateData.UIElement.Data.TreeViewItem.ItemParent = uiAncer;

                if(uiElement->Parent)
                {
                    PXUIElement* parentElement = PXNull;

                    const PXBool found = PXDictionaryFindEntry(&parentList, &uiElement->Parent, &parentElement);

                    if(found)
                    {
                        pxUIElementCreateData.UIElement.Data.TreeViewItem.ItemParent = parentElement;
                    }
                }

                PXEngineResourceCreate(pxEngineEditor, &pxUIElementCreateData);

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
            { &_tabPageNetwork, "Network", -1}
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

        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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

        //PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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


    //-----------------------------------------------------
    // TAB::Sound
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_panelSoundMain;
        pxUIElementCreateData.Name = "Button_Sound";
        pxUIElementCreateData.UIElement.Type = PXUIElementTypeButton;
        pxUIElementCreateData.UIElement.UIElementParent = _tabPageSound;
        pxUIElementCreateData.UIElement.ColorTintReference = &titleColor;
        pxUIElementCreateData.UIElement.BehaviourFlags = PXUIElementDecorative;
        pxUIElementCreateData.UIElement.StyleFlagList = PXGUIElementStyleDefault;
        pxUIElementCreateData.UIElement.Position.FlagListKeep = PXUIElementAllignTop;
        pxUIElementCreateData.UIElement.Position.MarginLeft = 0.2f;
        pxUIElementCreateData.UIElement.Position.MarginTop = 0.6;
        pxUIElementCreateData.UIElement.Position.MarginRight = 0.6f;
        pxUIElementCreateData.UIElement.Position.MarginBottom = 0.2f;
        pxUIElementCreateData.UIElement.Data.Button.TextInfo.Content = "Sound";

       PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

    }


    //-----------------------------------------------------
    // TAB::Database
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
        pxUIElementCreateData.ObjectReference = &_buttonDatabaseConnect;
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

        PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);

    }


#define DatabaseRowAWidth 135
#define DatabaseRowBWidth 250

    //-----------------------------------------------------
    // TAB::Database::
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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


#if 1
    //-----------------------------------------------------
    // Panel::Info::Bar
    //-----------------------------------------------------
    {
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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
        PXEngineResourceCreateInfo pxUIElementCreateData;
        PXClear(PXEngineResourceCreateInfo, &pxUIElementCreateData);
        pxUIElementCreateData.CreateType = PXEngineCreateTypeUIElement;
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