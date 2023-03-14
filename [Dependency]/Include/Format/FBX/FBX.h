#ifndef FBXInclude
#define FBXInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct FBX_
	{
		unsigned int __dummy__;
	}
	FBX;

	PXPublic PXActionResult FBXParse(const void* data, const PXSize dataSize);

#ifdef __cplusplus
}
#endif

#endif