#ifndef InputButtonInclude
#define InputButtonInclude

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	PXPublic unsigned char InputButtonReset(unsigned char* value);
	PXPublic unsigned char InputButtonIncrement(unsigned char* value);
	PXPublic unsigned char InputButtonIncrementIfAlreadyPressed(unsigned char* value);
	PXPublic unsigned char InputButtonIsShortPressed(const unsigned char value);
	PXPublic unsigned char InputButtonIsLongPressed(const unsigned charvalue);
	PXPublic unsigned char InputButtonIsPressed(const unsigned char value);

#ifdef __cplusplus
}
#endif

#endif