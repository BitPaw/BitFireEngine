#include "BFEUIBase.h"

typedef struct BFEUIResourceList_
{
    PXWindow* Main;
    PXWindow* Objects;
}
BFEUIResourceList;

void PXAPI BFEUIResourceListCreate(BFEUIResourceList* const bfeUIResourceList, PXEngine* const pxEngine, PXWindow* const parent);