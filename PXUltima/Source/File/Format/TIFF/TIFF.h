#ifndef QOIInclude
#define QOIInclude

#include <stddef.h>

#include <Error/ActionResult.h>
#include <File/Image.h>

#ifdef __cplusplus
extern "C"
{
#endif

	// Tag Image File Format
	typedef struct TIFF_
	{
		unsigned int __dummy__;
	}
	TIFF;

	extern size_t TIFFFilePredictSize(const size_t width, const size_t height, const size_t bbp);

	extern ActionResult TIFFParse(TIFF* tiff, const void* data, const size_t dataSize, size_t* dataRead);

	extern ActionResult TIFFSerializeFromImage(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten);

#ifdef __cplusplus
}
#endif

#endif