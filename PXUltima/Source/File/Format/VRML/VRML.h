#ifndef VRMLInclude
#define VRMLInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct VRML_
	{
		unsigned int __dummy__;
	}
	VRML;

	extern ActionResult VRMLParse(const void* data, const size_t dataSize);

#ifdef __cplusplus
}
#endif

#endif