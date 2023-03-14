#ifndef AVIInclude
#define AVIInclude

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct AVIHeader_
	{
		unsigned int MicroSecPerFrame; // frame display rate (or 0)
		unsigned int MaxBytesPerSec; // max. transfer rate
		unsigned int PaddingGranularity; // pad to multiples of this
		// size;
		unsigned int Flags; // the ever-present flags
		unsigned int TotalFrames; // # frames in file
		unsigned int InitialFrames;
		unsigned int Streams;
		unsigned int SuggestedBufferSize;
		unsigned int Width;
		unsigned int Height;
		unsigned int Reserved[4];
	}
	AVIHeader;


	typedef struct AVI_
	{
		AVIHeader Header;
		unsigned int __dummy__;
	}
	AVI;

	PXPublic PXActionResult AVIParse(AVI* const avi, PXDataStream* const pxDataStream);

#ifdef __cplusplus
}
#endif

#endif