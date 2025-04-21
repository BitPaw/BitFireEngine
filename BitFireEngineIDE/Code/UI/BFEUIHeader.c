#include "BFEUIHeader.h"

void PXAPI BFEUIHeaderCreate(BFEUIHeader* const bfeUIHeader, PXEngine* const pxEngine, PXWindow* const parent)
{
    PXWindowMenuItemInfo pxGUIElementMenuItemListProject[9];
    PXClearList(PXWindowMenuItemInfo, pxGUIElementMenuItemListProject, 9);
    pxGUIElementMenuItemListProject[0].TextData = "New";
    pxGUIElementMenuItemListProject[0].TextSize = 4;

    pxGUIElementMenuItemListProject[1].TextData = "Open";
    pxGUIElementMenuItemListProject[1].TextSize = 4;

    pxGUIElementMenuItemListProject[2].Flags = PXGUIMenuItemTypeMFT_MENUBARBREAK;

    pxGUIElementMenuItemListProject[3].TextData = "Save";
    pxGUIElementMenuItemListProject[3].TextSize = 4;

    pxGUIElementMenuItemListProject[4].Flags = PXGUIMenuItemTypeCheckmark;
    pxGUIElementMenuItemListProject[4].TextData = "AutoSave";
    pxGUIElementMenuItemListProject[4].TextSize = 8;

    pxGUIElementMenuItemListProject[5].Flags = PXGUIMenuItemTypeMFT_MENUBARBREAK;

    pxGUIElementMenuItemListProject[6].TextData = "Close";
    pxGUIElementMenuItemListProject[6].TextSize = 5;

    pxGUIElementMenuItemListProject[7].Flags = PXGUIMenuItemTypeMFT_MENUBARBREAK;

    pxGUIElementMenuItemListProject[8].TextData = "Exit";
    pxGUIElementMenuItemListProject[8].TextSize = 4;

    PXWindowMenuItemList addas;
    addas.MenuItemInfoListAmount = 9;
    addas.MenuItemInfoListData = pxGUIElementMenuItemListProject;

    PXWindowMenuItemInfo pxGUIElementMenuItemList[5];
    PXClearList(PXWindowMenuItemInfo, pxGUIElementMenuItemList, 5);
    pxGUIElementMenuItemList[0].Flags = PXGUIMenuItemTypeImage;
    pxGUIElementMenuItemList[1].TextData = "Project";
    pxGUIElementMenuItemList[1].TextSize = 7;
    pxGUIElementMenuItemList[1].ChildList = &addas;
    pxGUIElementMenuItemList[2].TextData = "Edit";
    pxGUIElementMenuItemList[2].TextSize = 4;
    pxGUIElementMenuItemList[3].TextData = "Window";
    pxGUIElementMenuItemList[3].TextSize = 6;
    pxGUIElementMenuItemList[4].TextData = "Help";
    pxGUIElementMenuItemList[4].TextSize = 4;


    PXResourceCreateInfo pxResourceCreateInfo;

    PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
    pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
    pxResourceCreateInfo.Name = "MenuStrip";
    pxResourceCreateInfo.ObjectReference = &bfeUIHeader->Main;
    pxResourceCreateInfo.UIElement.WindowParent = pxEngine->Window;
    pxResourceCreateInfo.UIElement.Type = PXUIElementTypeMenuStrip;
    pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight | PXWindowAllignTop;
    pxResourceCreateInfo.UIElement.Data.MenuItem.MenuItemInfoListData = pxGUIElementMenuItemList;
    pxResourceCreateInfo.UIElement.Position.Form.Height = 25;
    pxResourceCreateInfo.UIElement.Data.MenuItem.MenuItemInfoListAmount = 5;

    PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
}