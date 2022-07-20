#ifndef WAVInclude
#define WAVInclude

#include <stddef.h>

#include <Error/ActionResult.h>
#include <File/Format/FMT/FMT.h>

#ifdef __cplusplus
extern "C"
{
#endif

	// Waveform Audio File
	typedef struct WAV_
	{
		FMT Format;

		unsigned int SoundDataSize; // 32-Bit
		unsigned char* SoundData;
	}
	WAV;

	extern ActionResult WAVParse(WAV* wav, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif