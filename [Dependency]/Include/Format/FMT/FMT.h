#ifndef FMTInclude
#define FMTInclude

#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

	// Format header
	typedef struct FMT_
	{
		unsigned int ChunkSize;
		unsigned short AudioFormat;
		unsigned short NumerOfChannels;
		unsigned int SampleRate;
		unsigned int ByteRate;
		unsigned short BlockAllign;
		unsigned short BitsPerSample;
	}
	FMT;

	PXPublic void FMTConstruct(FMT* const fmt);

	PXPublic PXActionResult FMTParse(FMT* const fmt, PXDataStream* const pxDataStream, const Endian endian);

	PXPublic PXActionResult FMTSerialize(const FMT* const fmt, PXDataStream* const pxDataStream, const Endian endian);

#ifdef __cplusplus
}
#endif

#endif