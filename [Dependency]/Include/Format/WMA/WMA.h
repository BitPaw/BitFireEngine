#ifndef WMAInclude
#define WMAInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	// Windows Media Audio
	typedef struct WMA_
	{
		unsigned int __dummy__;
	}
	WMA;

	PXPublic PXActionResult WMAParse(WMA* wma, const void* data, const PXSize dataSize, PXSize* dataRead);

#ifdef __cplusplus
}
#endif

#endif