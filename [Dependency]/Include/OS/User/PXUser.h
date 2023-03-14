#ifndef UserInclude
#define UserInclude

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	PXPublic PXSize PXUserNameGetA(PXTextASCII* name, const PXSize nameSizeMax);
	PXPublic PXSize PXUserNameGetW(PXTextUNICODE* name, const PXSize nameSizeMax);
	PXPublic PXSize PXUserNameGetU(PXTextUTF8* name, const PXSize nameSizeMax);

#ifdef __cplusplus
}
#endif

#endif