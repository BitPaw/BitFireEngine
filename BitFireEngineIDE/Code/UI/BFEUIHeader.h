#include "BFEUIBase.h"

typedef struct BFEUIHeader_
{
    PXWindow* Main;
}
BFEUIHeader;

void PXAPI BFEUIHeaderCreate(BFEUIHeader* const bfeUIHeader, PXEngine* const pxEngine, PXWindow* const parent);