#if !defined(EndianInclude)
#define EndianInclude

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

	// Ordering or sequencing of bytes
	typedef enum Endian_
	{
		EndianInvalid,

		// Left to Right. Left smallest value.
		EndianBig,

		// Right to Left. Right smallest value.
		EndianLittle
	}
	Endian;

#define EndianCurrentSystem EndianLittle

	extern void EndianSwap(void* data, const size_t dataSize, const Endian endianFrom, const Endian endianTo);

#ifdef __cplusplus
}
#endif

#endif