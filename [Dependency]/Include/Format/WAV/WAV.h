#ifndef WAVInclude
#define WAVInclude

#include <File/PXDataStream.h>
#include <Format/FMT/FMT.h>

#ifdef __cplusplus
extern "C"
{
#endif

	// Waveform Audio File
	typedef struct WAV_
	{
		FMT Format;

		PXInt32U SoundDataSize; // 32-Bit
		void* SoundData;
	}
	WAV;

	PXPublic PXActionResult WAVParse(WAV* const wav, PXDataStream* const pxDataStream);
	PXPublic PXActionResult WAVSerialize(WAV* const wav, PXDataStream* const pxDataStream);

#ifdef __cplusplus
}
#endif

#endif