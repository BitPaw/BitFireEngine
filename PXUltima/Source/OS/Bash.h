#ifndef MonitorInclude
#define MonitorInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	extern ActionResult BashExecuteA(const char* programPath, const unsigned char syncronous);
	extern ActionResult BashExecuteW(const wchar_t* programPath, const unsigned char syncronous);

#ifdef __cplusplus
}
#endif

#endif
