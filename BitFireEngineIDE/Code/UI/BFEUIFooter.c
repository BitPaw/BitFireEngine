#include "BFEUIFooter.h"

void PXAPI BFEUIFooterCreate(BFEUIFooter* const bfeUIFooter, PXEngine* const pxEngine, PXWindow* const parent)
{
    PXResourceCreateInfo pxResourceCreateInfo;

    PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
    pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
    pxResourceCreateInfo.Name = "StatusBar";
    pxResourceCreateInfo.ObjectReference = &bfeUIFooter->Main;
    pxResourceCreateInfo.UIElement.Type = PXUIElementTypeStatusBar;
    //pxResourceCreateInfo.UIElement.ColorTintReference = &titleColor;
    pxResourceCreateInfo.UIElement.WindowParent = pxEngine->Window;
    pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight | PXWindowAllignBottom;
    pxResourceCreateInfo.UIElement.Position.Form.Height = 25;
    pxResourceCreateInfo.UIElement.Position.Margin.Bottom = PXDefaultBotStaleSize;

    PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
}