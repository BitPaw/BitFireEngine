#ifndef BashInclude
#define BashInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	PXPublic PXActionResult BashExecuteA(const char* programPath, const unsigned char syncronous);
	PXPublic PXActionResult BashExecuteW(const wchar_t* programPath, const unsigned char syncronous);

#ifdef __cplusplus
}
#endif

#endif
