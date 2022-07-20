#ifndef CRC32Include
#define CRC32Include

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

	extern unsigned int CRC32Generate(const unsigned char* data, size_t length);

#ifdef __cplusplus
}
#endif

#endif