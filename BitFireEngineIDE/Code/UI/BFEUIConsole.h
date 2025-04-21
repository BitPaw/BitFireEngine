#include "BFEUIBase.h"

typedef struct BFEUIConsole_
{
    PXWindow* Main;
    PXWindow* Data;
    PXWindow* Content;
}
BFEUIConsole;

void PXAPI BFEUIConsoleCreate(BFEUIConsole* const bfeBFEUIConsole, PXEngine* const pxEngine);