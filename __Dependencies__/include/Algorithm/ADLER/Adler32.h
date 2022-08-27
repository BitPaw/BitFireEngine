#ifndef A3DSInclude
#define A3DSInclude

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

	extern unsigned int Adler32Check(unsigned char* data, size_t length);
	extern unsigned int Adler32Create(size_t adler, const unsigned char* data, size_t length);

#ifdef __cplusplus
}
#endif

#endif