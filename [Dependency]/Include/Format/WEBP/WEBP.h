#ifndef WEBPInclude
#define WEBPInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct WEBP_
	{
		unsigned int __dummy__;
	}
	WEBP;

	PXPublic PXActionResult WEBPParse(WEBP* webp, const void* data, const PXSize dataSize, PXSize* dataRead);

#ifdef __cplusplus
}
#endif

#endif