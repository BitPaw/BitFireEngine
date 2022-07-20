#ifndef PLYInclude
#define PLYInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct PLY_
	{
		unsigned int __dummy__;
	}
	PLY;

	extern ActionResult PLYParse(const void* data, const size_t dataSize);

#ifdef __cplusplus
}
#endif

#endif