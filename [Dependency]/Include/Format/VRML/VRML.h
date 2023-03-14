#ifndef VRMLInclude
#define VRMLInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct VRML_
	{
		unsigned int __dummy__;
	}
	VRML;

	PXPublic PXActionResult VRMLParse(const void* data, const PXSize dataSize);

#ifdef __cplusplus
}
#endif

#endif