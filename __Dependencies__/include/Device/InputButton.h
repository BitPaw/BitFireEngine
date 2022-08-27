#ifndef InputButtonInclude
#define InputButtonInclude

#ifdef __cplusplus
extern "C"
{
#endif

	extern unsigned char InputButtonReset(unsigned char* value);
	extern unsigned char InputButtonIncrement(unsigned char* value);
	extern unsigned char InputButtonIncrementIfAlreadyPressed(unsigned char* value);
	extern unsigned char InputButtonIsShortPressed(const unsigned char value);
	extern unsigned char InputButtonIsLongPressed(const unsigned charvalue);
	extern unsigned char InputButtonIsPressed(const unsigned char value);

#ifdef __cplusplus
}
#endif

#endif