#ifndef ADAM7Include
#define ADAM7Include

#include <stddef.h>

#include <Error/ActionResult.h>
#include <File/Format/PNG/PNG.h>

#ifdef __cplusplus
extern "C"
{
#endif

	static unsigned char ADAM7paethPredictor(short a, short b, short c);
	static unsigned ADAM7unfilterScanline(unsigned char* recon, const unsigned char* scanline, const unsigned char* precon, size_t bytewidth, unsigned char filterType, size_t length);
	static size_t ADAM7lodepng_get_raw_size_idat(size_t w, size_t h, size_t bpp);
	static unsigned ADAM7unfilter(unsigned char* out, const unsigned char* in, size_t w, size_t h, size_t bpp);
	static void ADAM7removePaddingBits(unsigned char* out, const unsigned char* in, size_t olinebits, size_t ilinebits, size_t h);
	static unsigned char ADAM7readBitFromReversedStream(size_t* bitpointer, const unsigned char* bitstream);
	static void ADAM7setBitOfReversedStream(size_t* bitpointer, unsigned char* bitstream, unsigned char bit);
	static void ADAM7_getpassvalues(unsigned passw[7], unsigned passh[7], size_t filter_passstart[8], size_t padded_passstart[8], size_t passstart[8], size_t w, size_t h, size_t bpp);
	static void ADAM7_deinterlace(unsigned char* out, const unsigned char* in, size_t w, unsigned h, unsigned bpp);


	extern unsigned int ADAM7ScanlinesDecode
	(
		unsigned char* out,
		unsigned char* in,
		size_t width,
		size_t height,
		size_t bbp,
		PNGInterlaceMethod interlaceMethod
	);

	extern unsigned int ADAM7ScanlinesEncode
	(
		unsigned char* out,
		unsigned char* in,
		size_t width,
		size_t height,
		size_t bbp,
		PNGInterlaceMethod interlaceMethod
	);


	extern size_t ADAM7CaluclateExpectedSize(size_t width, size_t height, size_t bpp);


#ifdef __cplusplus
}
#endif

#endif