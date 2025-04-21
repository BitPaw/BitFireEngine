#include "BFEUIBase.h"

typedef struct BFEUIVideo_
{
    PXWindow* Main;
}
BFEUIVideo;

void PXAPI BFEUIVideoCreate(BFEUIVideo* const bfeUIVideo, PXEngine* const pxEngine, PXWindow* const parent);