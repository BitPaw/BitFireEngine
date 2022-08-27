#ifndef FBXInclude
#define FBXInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct FBX_
	{
		unsigned int __dummy__;
	}
	FBX;

	extern ActionResult FBXParse(const void* data, const size_t dataSize);

#ifdef __cplusplus
}
#endif

#endif