#ifndef STLInclude
#define STLInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct STL_
	{
		unsigned int __dummy__;
	}
	STL;

	extern ActionResult STLParse(const void* data, const size_t dataSize);

#ifdef __cplusplus
}
#endif

#endif