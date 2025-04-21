#include "BFEUIBase.h"

typedef struct BFEUITimeline_
{
    PXWindow* Main;
}
BFEUITimeline;

void PXAPI BFEUITimelineCreate(BFEUITimeline* const bfeUITimeline, PXEngine* const pxEngine);