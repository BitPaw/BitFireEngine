#include "BFEUIBase.h"

typedef struct BFEUISound_
{
    PXWindow* Main;
}
BFEUISound;

void PXAPI BFEUISoundCreate(BFEUISound* const bfeUISound, PXEngine* const pxEngine);