#include "BFEUIBase.h"

typedef struct BFEUIFileView_
{
    PXWindow* Main;

    // Top menü
    PXWindow* ButtonFolderPrevious;
    PXWindow* ButtonFolderForward;
    PXWindow* ButtonFolderUp;
    PXWindow* ButtonRefresh;
    PXWindow* ButtonExplorerOpen;
    PXWindow* ButtonExplorerSelect;

    PXWindow* InputSearch;

    PXWindow* InputPathCurrent;

    // List
    PXWindow* Data;
}
BFEUIFileView;

void PXAPI BFEUIFileViewCreate(BFEUIFileView* const bfeUIFileView, PXEngine* const pxEngine, PXWindow* const parent);

PXPrivate void PXAPI BFEUIFileViewUpdate(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent);