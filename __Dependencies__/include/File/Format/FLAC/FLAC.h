#ifndef FLACInclude
#define FLACInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct FLAC_
	{
		unsigned int __dummy__;
	}
	FLAC;

	extern ActionResult FLACParse(const void* data, const size_t dataSize);

#ifdef __cplusplus
}
#endif

#endif