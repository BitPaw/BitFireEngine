#ifndef FLACInclude
#define FLACInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct FLAC_
	{
		unsigned int __dummy__;
	}
	FLAC;

	PXPublic PXActionResult FLACParse(const void* data, const PXSize dataSize);

#ifdef __cplusplus
}
#endif

#endif