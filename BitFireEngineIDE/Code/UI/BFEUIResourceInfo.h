#include "BFEUIBase.h"

typedef struct BFEUIResourceInfo_
{
    PXWindow* Main;
    PXWindow* Text;
    PXWindow* Info;
}
BFEUIResourceInfo;

void PXAPI BFEUIResourceInfoCreate(BFEUIResourceInfo* const bfeUIResourceInfo, PXEngine* const pxEngine);