#include "BFEUIBase.h"

typedef struct BFEUIFileView_
{
    PXWindow* Main;
    PXWindow* Select;
    PXWindow* Data;
}
BFEUIFileView;

void PXAPI BFEUIFileViewCreate(BFEUIFileView* const bfeUIFileView, PXEngine* const pxEngine, PXWindow* const parent);

PXPrivate void PXAPI BFEUIFileViewUpdate(BFBitFireIDE* const bfBitFireIDE, PXWindowEvent* const pxWindowEvent);