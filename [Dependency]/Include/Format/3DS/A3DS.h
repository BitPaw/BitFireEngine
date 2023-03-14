#ifndef A3DSInclude
#define A3DSInclude

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct A3DS_
	{
		unsigned int __dummy__;
	}
	A3DS;

	PXPublic PXActionResult A3DSParse(const void* data, const PXSize dataSize);

#ifdef __cplusplus
}
#endif

#endif