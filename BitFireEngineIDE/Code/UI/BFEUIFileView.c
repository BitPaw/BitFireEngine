#include "BFEUIFileView.h"
#include <PX/OS/Console/PXConsole.h>



void PXAPI BFEUIFileViewCreate(BFEUIFileView* const bfeUIFileView, PXEngine* const pxEngine, PXWindow* const parent)
{
    PXResourceCreateInfo pxResourceCreateInfo;

    //-----------------------------------------------------
  // FileTreeView - Title
  //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "File'n'Data";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->Main;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeText;
        //pxResourceCreateInfo.UIElement.ColorTintReference = &textColor;
        pxResourceCreateInfo.UIElement.WindowParent = parent;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourDefaultText | PXWindowBehaviourBorder;
        pxResourceCreateInfo.UIElement.Position.Form.Height = PXDefaultTitleBar;
        // pxUIElementCreateData.UIElement.Position.Margin.Left = 1;
        // pxUIElementCreateData.UIElement.Position.Margin.Top = 0;
        // pxUIElementCreateData.UIElement.Position.Margin.Right = 0;
         //pxUIElementCreateData.UIElement.Position.Margin.Bottom = PXDefaultOffset;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

        bfeUIFileView->Main->NameContent = "File'n'Data";
        bfeUIFileView->Main->NameContentSize = 11;
    }




    //-----------------------------------------------------
    // Panel(Left)::FileStuff::TreeView
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "Button Select";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->Select;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeTreeView;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        //pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXWindowKeepHeight;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = 0.08;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = 0.03;

        //  PXEngineResourceCreate(pxEngine, &pxUIElementCreateData);
    }


    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "TreeView_File";
        pxResourceCreateInfo.ObjectReference = &bfeUIFileView->Data;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeFileDirectyView;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIFileView->Main;
        //pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder | PXResourceInfoUseByEngine;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = 0.08;
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
