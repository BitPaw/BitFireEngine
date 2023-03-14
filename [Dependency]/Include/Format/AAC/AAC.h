#ifndef AACInclude
#define AACInclude

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct AAC_
	{
		unsigned int __dummy__;
	}
	AAC;

	PXPublic PXActionResult AACParse(const void* data, const PXSize dataSize);

#ifdef __cplusplus
}
#endif

#endif