#include "BFEUIResourceInfo.h"

void PXAPI BFEUIResourceInfoCreate(BFEUIResourceInfo* const bfeUIResourceInfo, PXEngine* const pxEngine)
{
    PXResourceCreateInfo pxResourceCreateInfo;

    //-----------------------------------------------------
    // Panel::Info::Bar
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.ObjectReference = &bfeUIResourceInfo->Main;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypePanel;
        pxResourceCreateInfo.UIElement.WindowParent = pxEngine->Window;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder;
        //pxResourceCreateInfo.UIElement.ColorTintReference = &titleColor;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = 1.6f;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = PXDefaultTopOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.54f;
        pxResourceCreateInfo.UIElement.Position.Form.Height = 30.0f;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }

    //-----------------------------------------------------
    // Panel::Info::Bar::Text
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.ObjectReference = &bfeUIResourceInfo->Text;
        pxResourceCreateInfo.Name = "Info";
        //pxResourceCreateInfo.UIElement.ColorTintReference = &textColor;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeText;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIResourceInfo->Main;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourDefaultText | PXWindowBehaviourBorder;
        pxResourceCreateInfo.UIElement.Position.Form.Height = PXDefaultTitleBar;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.ObjectReference = &bfeUIResourceInfo->Info;
        pxResourceCreateInfo.Name = "Info";
        //pxResourceCreateInfo.UIElement.ColorTintReference = &textColor;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeResourceInfo;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIResourceInfo->Main;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = PXDefaultContentOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = PXDefaultOffset;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
}