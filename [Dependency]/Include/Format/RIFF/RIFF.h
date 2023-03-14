#ifndef RIFFInclude
#define RIFFInclude

#include <File/PXDataStream.h>
#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>
#include <OS/File/Endian.h>

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
		PXBool Valid;
		Endian EndianFormat;
		unsigned int ChunkSize;
		RIFFFormat Format;
	}
	RIFF;

	PXPrivate void RIFFText();

	PXPublic PXActionResult RIFFParse(RIFF* const riff, PXDataStream* const pxDataStream);

	PXPublic PXActionResult RIFFSerialize(const RIFF* const riff, PXDataStream* const pxDataStream);

#ifdef __cplusplus
}
#endif

#endif