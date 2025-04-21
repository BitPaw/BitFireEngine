#include "BFEUIBase.h"

typedef struct BFEUIFooter_
{
    PXWindow* Main;
}
BFEUIFooter;

void PXAPI BFEUIFooterCreate(BFEUIFooter* const bfeUIFooter, PXEngine* const pxEngine, PXWindow* const parent);