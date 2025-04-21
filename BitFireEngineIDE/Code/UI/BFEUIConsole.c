#include "BFEUIConsole.h"

void PXAPI BFEUIConsoleCreate(BFEUIConsole* const bfeBFEUIConsole, PXEngine* const pxEngine)
{
    PXResourceCreateInfo pxResourceCreateInfo;

    //-----------------------------------------------------
    // Panel:Console
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.ObjectReference = &bfeBFEUIConsole->Main;
        pxResourceCreateInfo.Name = "ConsoleLog";
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypePanel;
        pxResourceCreateInfo.UIElement.WindowParent = pxEngine->Window;
       // pxResourceCreateInfo.UIElement.ColorTintReference = &titleColor;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowAllignTop;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = 0.41f;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = 1.48f;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = 0.41f;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = PXDefaultBotOffset;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    {

        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.ObjectReference = &bfeBFEUIConsole->Data;
        pxResourceCreateInfo.Name = "Console";
        pxResourceCreateInfo.UIElement.WindowParent = bfeBFEUIConsole->Main;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeText;
       // pxResourceCreateInfo.UIElement.ColorTintReference = &titleColor;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowAllignTop | PXWindowKeepHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Height = PXDefaultTitleBar;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }

    {

        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.ObjectReference = &bfeBFEUIConsole->Content;
        pxResourceCreateInfo.Name = "Console Data";
        pxResourceCreateInfo.UIElement.WindowParent = bfeBFEUIConsole->Main;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTextEdit;
       // pxResourceCreateInfo.UIElement.ColorTintReference = &titleColor;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowAllignTop;
        pxResourceCreateInfo.UIElement.Position.Form.Height = PXDefaultTitleBar;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = 0.1f;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = PXDefaultOffset;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
}