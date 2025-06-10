#include "BFEUIFileView.h"

#include <PX/OS/Console/PXConsole.h>

void PXAPI BFEUIFileViewCreate(BFEUIFileView* const bfeUIFileView, PXEngine* const pxEngine, PXWindow* const parent)
{
    PXResourceCreateInfo pxResourceCreateInfo;


    float buttonHeight = 25;
    float offsetX = 0.040;
    float offsetY = 0.075;

    //-----------------------------------------------------
    // FileTreeView - Title
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "File'n'Data";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->Main;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeText;
        // pxResourceCreateInfo.UIElement.ColorTintReference = &textColor;
        pxResourceCreateInfo.UIElement.WindowParent = parent;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourDefaultText | PXWindowBehaviourBorder;
        pxResourceCreateInfo.UIElement.Position.Form.Height = PXDefaultTitleBar;
        // pxUIElementCreateData.UIElement.Position.Margin.Left = 1;
        // pxUIElementCreateData.UIElement.Position.Margin.Top = 0;
        // pxUIElementCreateData.UIElement.Position.Margin.Right = 0;
        // pxUIElementCreateData.UIElement.Position.Margin.Bottom = PXDefaultOffset;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

        bfeUIFileView->Main->NameContent = "File'n'Data";
        bfeUIFileView->Main->NameContentSize = 11;
    }

    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "ButtonFolderPrevious";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->ButtonFolderPrevious;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeButton;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        // pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight | PXWindowKeepWidth;
        pxResourceCreateInfo.UIElement.Position.Form.Height = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Width = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = offsetY;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.03;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "ButtonFolderForward";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->ButtonFolderForward;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeButton;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        // pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight | PXWindowKeepWidth;
        pxResourceCreateInfo.UIElement.Position.Form.Height = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Width = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = offsetY;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.03;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "ButtonFolderUp";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->ButtonFolderUp;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeButton;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        // pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight | PXWindowKeepWidth;
        pxResourceCreateInfo.UIElement.Position.Form.Height = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Width = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset + offsetX * 1;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = offsetY;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.03;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "ButtonRefresh";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->ButtonRefresh;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeButton;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        // pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight | PXWindowKeepWidth;
        pxResourceCreateInfo.UIElement.Position.Form.Height = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Width = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset + offsetX * 2;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = offsetY;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.03;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "ButtonExplorerOpen";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->ButtonExplorerOpen;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeButton;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        // pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight | PXWindowKeepWidth;
        pxResourceCreateInfo.UIElement.Position.Form.Height = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Width = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset + offsetX * 3;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = offsetY;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.03;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "ButtonExplorerSelect";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->ButtonExplorerSelect;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeButton;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        // pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight | PXWindowKeepWidth;
        pxResourceCreateInfo.UIElement.Position.Form.Height = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Width = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset + offsetX * 4;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = offsetY;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.03;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "InputSearch";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->InputSearch;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeText;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        // pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Height = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Width = 100;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset+ offsetX*5;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = offsetY;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.03;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "InputPathCurrent";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->InputPathCurrent;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeText;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        // pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Height = buttonHeight;
        pxResourceCreateInfo.UIElement.Position.Form.Width = 100;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = offsetY *2;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.03;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }





    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "TreeView_File";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->Data;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeFileDirectyView;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        // pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXResourceInfoUseByEngine;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = offsetY * 3;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.03;
        pxResourceCreateInfo.UIElement.InteractCallBack = BFEUIFileViewUpdate;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);
    }
}

void PXAPI BFEUIFileViewUpdate(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent)
{
    switch(pxWindowEvent->Type)
    {
        case PXWindowEventTypeElementSelect:
        {
            PXWindow* const uiElementSelected = pxWindowEvent->UIElementSender;

            PXLogPrint
            (
                PXLoggingInfo,
                "BF",
                "Event",
                "Select: <%s>",
                ""// uiElementSelected->NameData
            );
           

            break;
        }
        default:
            break;
    }
}