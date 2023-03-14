#ifndef ADAM7Include
#define ADAM7Include

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>
#include <Format/PNG/PNG.h>

#ifdef __cplusplus
extern "C"
{
#endif

	PXPublic unsigned char ADAM7paethPredictor(short a, short b, short c);
	PXPublic unsigned ADAM7unfilterScanline(unsigned char* recon, const unsigned char* scanline, const unsigned char* precon, PXSize bytewidth, unsigned char filterType, PXSize length);
	PXPublic PXSize ADAM7lodepng_get_raw_size_idat(PXSize w, PXSize h, PXSize bpp);
	PXPublic unsigned ADAM7unfilter(unsigned char* out, const unsigned char* in, PXSize w, PXSize h, PXSize bpp);
	PXPublic void ADAM7removePaddingBits(unsigned char* out, const unsigned char* in, PXSize olinebits, PXSize ilinebits, PXSize h);
	PXPublic unsigned char ADAM7readBitFromReversedStream(PXSize* bitpointer, const unsigned char* bitstream);
	PXPublic void ADAM7setBitOfReversedStream(PXSize* bitpointer, unsigned char* bitstream, unsigned char bit);
	PXPublic void ADAM7_getpassvalues(unsigned passw[7], unsigned passh[7], PXSize filter_passstart[8], PXSize padded_passstart[8], PXSize passstart[8], PXSize w, PXSize h, PXSize bpp);
	PXPublic void ADAM7_deinterlace(unsigned char* out, const unsigned char* in, PXSize w, unsigned h, unsigned bpp);




	PXPublic unsigned int ADAM7ScanlinesDecode
	(
		unsigned char* out,
		unsigned char* in,
		PXSize width,
		PXSize height,
		PXSize bbp,
		PNGInterlaceMethod interlaceMethod
	);

	PXPublic unsigned int ADAM7ScanlinesEncode
	(
		unsigned char* out,
		unsigned char* in,
		PXSize width,
		PXSize height,
		PXSize bbp,
		PNGInterlaceMethod interlaceMethod
	);


	PXPublic PXSize ADAM7CaluclateExpectedSize(PXSize width, PXSize height, PXSize bpp);


#ifdef __cplusplus
}
#endif

#endif