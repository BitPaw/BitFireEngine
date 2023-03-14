#ifndef EndianInclude
#define EndianInclude

#include <Format/Type.h>

#if 1
#define EndianCurrentSystemIsLittle
#else
#define EndianCurrentSystemIsBig
#endif

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

	PXPublic void EndianSwap(void* data, const PXSize dataSize, const Endian endianFrom, const Endian endianTo);

#ifdef __cplusplus
}
#endif

#endif