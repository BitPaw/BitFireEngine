#include "BFEUITab.h"

void PXAPI BFEUITabCreate(BFEUITab* const bfeUITab, PXEngine* const pxEngine)
{
    PXResourceCreateInfo pxResourceCreateInfo;

    // Load icon atlas
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeIconAtlas;
        pxResourceCreateInfo.ObjectReference = &bfeUITab->IconAtlasMenu;
        pxResourceCreateInfo.FilePath = "Texture/IconAtlas.png";
        pxResourceCreateInfo.IconAtlas.CellSize = 16;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }


    //-----------------------------------------------------
    // Panel:Menu
    //-----------------------------------------------------
    {
        PXIconAtlas* const pxIconAtlas = bfeUITab->IconAtlasMenu;

        PXUIElementTabPageSingleInfo pxUIElementTabPageSingleInfo[] =
        {
            { &bfeUITab->PageScene,       "Scene",    &pxIconAtlas->IconList[7], PXUIElementTypeScene },
            { &bfeUITab->PageBehaviour,   "Behaviour",&pxIconAtlas->IconList[7] , PXUIElementTypeGraphBehaviour},
            { &bfeUITab->PageTime,        "Time",     &pxIconAtlas->IconList[7], PXUIElementTypeGraphTime },
            { &bfeUITab->PageSound,       "Sound",    &pxIconAtlas->IconList[8] , PXUIElementTypeSoundPlayerMixer},
            { &bfeUITab->PageVideo,       "Video",    &pxIconAtlas->IconList[2], PXUIElementTypeVideoCutter },
            { &bfeUITab->PageDatabase,    "Database", &pxIconAtlas->IconList[3] , PXUIElementTypeDataBaseManager},
            { &bfeUITab->PageNetwork,     "Network",  &pxIconAtlas->IconList[11], PXUIElementTypeNetworkTester },
            { &bfeUITab->PageInput,       "Input",    &pxIconAtlas->IconList[12], PXUIElementTypeInputView },
            { &bfeUITab->PageHardware,    "Hardware", &pxIconAtlas->IconList[0] , PXUIElementTypeHardwareInfo}
        };
        const PXSize amount = sizeof(pxUIElementTabPageSingleInfo) / sizeof(PXUIElementTabPageSingleInfo);

        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "TAB-Controller";
        pxResourceCreateInfo.ObjectReference = &bfeUITab->Main;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTabControll;
        //pxResourceCreateInfo.UIElement.ColorTintReference = &titleColor;
        pxResourceCreateInfo.UIElement.WindowParent = pxEngine->Window;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowAllignTop;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = 0.41f;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = PXDefaultTopOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = 0.41f;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.54f;
        pxResourceCreateInfo.UIElement.Data.TabPage.TabPageSingleInfoAmount = amount;
        pxResourceCreateInfo.UIElement.Data.TabPage.TabPageSingleInfoList = pxUIElementTabPageSingleInfo;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
}