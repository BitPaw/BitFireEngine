#ifndef PXStopWatchINCLUDE
#define PXStopWatchINCLUDE

#include <Format/Type.h>
#include <OS/Time/PXTime.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXStopWatch_
	{
		PXTime* TimeStampData;
		PXSize TimeStampDataSizeUsed;
		PXSize TimeStampDataSizeAllocated;
	}
	PXStopWatch;

	PXPublic void PXStopWatchConstruct(PXStopWatch* const stopWatch);

	PXPublic void PXStopWatchSet(PXStopWatch* const stopWatch, void* const data, const PXSize dataSize);

	PXPublic void PXStopWatchStart(PXStopWatch* const stopWatch);
	PXPublic PXBool PXStopWatchTrigger(PXStopWatch* const stopWatch, PXTime* const time);
	PXPublic void PXStopWatchReset(PXStopWatch* const stopWatch);

#ifdef __cplusplus
}
#endif

#endif