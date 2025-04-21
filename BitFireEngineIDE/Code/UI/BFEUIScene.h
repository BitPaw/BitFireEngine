#include "BFEUIBase.h"

typedef struct BFEUIScene_
{
    PXWindow* Main;
}
BFEUIScene;

void PXAPI BFEUISceneCreate(BFEUIScene* const bfeUIScene, PXEngine* const pxEngine, PXWindow* const parent);