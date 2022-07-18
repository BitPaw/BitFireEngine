
#if !defined(UserInclude)
#define UserInclude

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

	extern unsigned char UserNameGetA(char* name, const size_t nameSizeMax, size_t* nameSizeWritten);
	extern unsigned char UserNameGetW(wchar_t* name, const size_t nameSizeMax, size_t* nameSizeWritten);

#ifdef __cplusplus
}
#endif

#endif