#include "BFEUIBase.h"

typedef struct BFEUITab_
{
    PXWindow* Main;

    PXIconAtlas* IconAtlasMenu;

    PXWindow* PageScene;
    PXWindow* PageBehaviour;
    PXWindow* PageTime;
    PXWindow* PageSound;
    PXWindow* PageNetwork;
    PXWindow* PageVideo;
    PXWindow* PageDatabase;
    PXWindow* PageInput;
    PXWindow* PageHardware;
}
BFEUITab;

void PXAPI BFEUITabCreate(BFEUITab* const bfeUITab, PXEngine* const pxEngine);