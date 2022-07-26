#ifndef FileOpenDialogInclude
#define FileOpenDialogInclude

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

	extern unsigned char FileOpenDialogA(char* filePathOutput);
	extern unsigned char FileOpenDialogW(wchar_t* filePathOutput);

#ifdef __cplusplus
}
#endif

#endif