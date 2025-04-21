#pragma once

#include <PX/Media/PXResource.h>
#include <PX/Engine/PXEngine.h>



#define PXDefaultOffset 0.005f
#define PXDefaultTopOffset PXDefaultOffset + 0.08
#define PXDefaultBotStaleSize 0.005
#define PXDefaultBotOffset PXDefaultOffset + PXDefaultBotStaleSize + 0.08
#define PXDefaultTitleBar 20.0f
#define PXDefaultContentOffset 0.06f

#define PXDefaultTextHeight 20


typedef struct BFBitFireIDE_
{
    PXEngine EngineScene;
    PXEngine EngineEditor;
}
BFBitFireIDE;


typedef void (PXAPI* BFEUICreateFunction)(void* const adress, PXEngine* const pxEngine);