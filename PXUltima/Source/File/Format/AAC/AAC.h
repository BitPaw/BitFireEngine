#ifndef AACInclude
#define AACInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct AAC_
	{
		unsigned int __dummy__;
	}
	AAC;

	extern ActionResult AACParse(const void* data, const size_t dataSize);

#ifdef __cplusplus
}
#endif

#endif