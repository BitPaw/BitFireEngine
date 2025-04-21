#include "BFEUIResourceList.h"

#include <PX/OS/Console/PXConsole.h>

void PXAPI BFEUIFileViewUpdate(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent);

void PXAPI BFEUIResourceListCreate(BFEUIResourceList* const bfeUIResourceList, PXEngine* const pxEngine, PXWindow* const parent)
{
    PXResourceCreateInfo pxResourceCreateInfo;

    //-----------------------------------------------------
  // SceneElements - Title
  //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "Objects";
        pxResourceCreateInfo.ObjectReference = &bfeUIResourceList->Main;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeText;
        //pxResourceCreateInfo.UIElement.ColorTintReference = &textColor;
        pxResourceCreateInfo.UIElement.WindowParent = parent;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourDefaultText | PXWindowBehaviourBorder;
        pxResourceCreateInfo.UIElement.Position.Form.Height = PXDefaultTitleBar;
        //pxUIElementCreateData.UIElement.Position.Margin.Bottom = PXDefaultOffset;

        PXEngineResourceCreate(pxEngine, &pxResourceCreateInfo);

        bfeUIResourceList->Main->NameContent = "Objects";
        bfeUIResourceList->Main->NameContentSize = 7;
    }


    //-----------------------------------------------------
    // Panel::Scene::Render
    //-----------------------------------------------------
    {
        PXClear(PXResourceCreateInfo, &pxResourceCreateInfo);
        pxResourceCreateInfo.Type = PXResourceTypeGUIElement;
        pxResourceCreateInfo.Name = "Loaded Objects";
        pxResourceCreateInfo.ObjectReference = &bfeUIResourceList->Objects;
        pxResourceCreateInfo.UIElement.Type = PXUIElementTypeResourceManger;
        pxResourceCreateInfo.UIElement.WindowParent = bfeUIResourceList->Main;
        //pxResourceCreateInfo.UIElement.ColorTintReference = &titleMenuButtonTextColorReference;
        pxResourceCreateInfo.UIElement.Setting = PXWindowBehaviourBorder;
        pxResourceCreateInfo.UIElement.Position.Margin.Left = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Top = PXDefaultContentOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Right = PXDefaultOffset;
        pxResourceCreateInfo.UIElement.Position.Margin.Bottom = PXDefaultOffset;
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


            // _uiInfoPanelObjectNameContent->TextInfo.Content = pxUIElementInteractInfo->UIElementSelected->NameData;

             //const char* typeName = PXUIElementTypeToString(uiElementSelected->Type);

            // _uiInfoPanelObjectTypeContent->TextInfo.Content = typeName;

           //  PXWindowUpdateInfo pxUIElementUpdateInfo[2];
            // PXClearList(PXWindowUpdateInfo, pxUIElementUpdateInfo, 2);

             /*

             pxUIElementUpdateInfo[0].UIElement = _uiInfoPanelObjectNameContent;
             pxUIElementUpdateInfo[0].WindowReference = &bfBitFireIDE->EngineEditor.Window;
             pxUIElementUpdateInfo[0].Property = PXUIElementPropertyTextContent;
           //  pxUIElementUpdateInfo[0].Data.Text.Content = _uiInfoPanelObjectNameContent->NameData;

             pxUIElementUpdateInfo[1].UIElement = _uiInfoPanelObjectTypeContent;
             pxUIElementUpdateInfo[1].WindowReference = &bfBitFireIDE->EngineEditor.Window;
             pxUIElementUpdateInfo[1].Property = PXUIElementPropertyTextContent;
          //   pxUIElementUpdateInfo[1].Data.Text.Content = _uiInfoPanelObjectTypeContent->NameData;

              PXWindowUpdate(PXNull, pxUIElementUpdateInfo, 1);
              */

            break;
        }
        default:
            break;
    }
}
