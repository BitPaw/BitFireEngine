#ifndef GIFInclude
#define GIFInclude

#include <stddef.h>

#include <Error/ActionResult.h>
#include <File/Image.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct GIFImageDescriptor_
	{
		unsigned char Separator;
		unsigned short LeftPosition;
		unsigned short TopPosition;
		unsigned short Width;
		unsigned short Height;
		unsigned char LocalColorTableSize;
		unsigned char Reserved;
		unsigned char SortFlag;
		unsigned char InterlaceFlag;
		unsigned char LocalColorTableFlag;
	}
	GIFImageDescriptor;

	typedef struct GIF_
	{
		unsigned short Width;
		unsigned short Height;

		unsigned char GlobalColorTableSize;
		unsigned char IsSorted;
		unsigned char ColorResolution;
		unsigned char IsGlobalColorTablePresent;

		unsigned char BackgroundColorIndex;
		unsigned char PixelAspectRatio;
	}
	GIF;

	extern size_t GIFFilePredictSize(const size_t width, const size_t height, const size_t bbp);

	extern ActionResult GIFLoad(GIF* gif, const void* data, const size_t dataSize, size_t* dataRead);

	extern ActionResult GIFSerializeFromImage(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten);

#ifdef __cplusplus
}
#endif

#endif