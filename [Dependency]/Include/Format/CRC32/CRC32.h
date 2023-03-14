#ifndef CRC32Include
#define CRC32Include

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	PXPublic unsigned int CRC32Generate(const unsigned char* const data, const PXSize length);

#ifdef __cplusplus
}
#endif

#endif