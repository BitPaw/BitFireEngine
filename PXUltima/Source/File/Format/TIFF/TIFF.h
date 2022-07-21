#ifndef QOIInclude
#define QOIInclude

#include <stddef.h>

#include <Error/ActionResult.h>

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

	extern ActionResult TIFFParse(TIFF* tiff, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif