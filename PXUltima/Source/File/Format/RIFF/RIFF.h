#ifndef RIFFInclude
#define RIFFInclude

#include <stddef.h>

#include <Error/ActionResult.h>
#include <File/Endian.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum RIFFFormat_
	{
		RIFFInvalid,
		RIFFWaveformAudio, // WAVE
		RIFFMultimediaMovieFile, // RMMP
		RIFFMIDI, // RMID
		RIFFDeviceIndependentBitmap, // RDIB
		RIFFPalette,  // PAL
		RIFFAudioVideoInterleave, // AVI 
		//DLS,
	}
	RIFFFormat;

	// Resource Interchange File Format. 
	typedef struct RIFF_
	{
		unsigned char Valid;
		Endian EndianFormat;
		unsigned int ChunkSize;
		RIFFFormat Format;
	}
	RIFF;

	extern ActionResult RIFFParse(RIFF* riff, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif