#pragma once

#include <cstddef>

#include "../../Image/PNG/Chunk/PNGInterlaceMethod.h"

namespace BF
{
	class ADAM7
	{
		private:
		static unsigned char paethPredictor(short a, short b, short c);
		static unsigned unfilterScanline(unsigned char* recon, const unsigned char* scanline, const unsigned char* precon, size_t bytewidth, unsigned char filterType, size_t length);
		static size_t lodepng_get_raw_size_idat(size_t w, size_t h, size_t bpp);
		static unsigned unfilter(unsigned char* out, const unsigned char* in, size_t w, size_t h, size_t bpp);
		static void removePaddingBits(unsigned char* out, const unsigned char* in, size_t olinebits, size_t ilinebits, size_t h);
		static unsigned char readBitFromReversedStream(size_t* bitpointer, const unsigned char* bitstream);
		static void setBitOfReversedStream(size_t* bitpointer, unsigned char* bitstream, unsigned char bit);
		static void Adam7_getpassvalues(unsigned passw[7], unsigned passh[7], size_t filter_passstart[8], size_t padded_passstart[8], size_t passstart[8], size_t w, size_t h, size_t bpp);
		static void Adam7_deinterlace(unsigned char* out, const unsigned char* in, size_t w, unsigned h, unsigned bpp);

		public:
		static unsigned int ScanlinesDecode
		(
			unsigned char* out, 
			unsigned char* in, 
			size_t width,
			size_t height, 
			size_t bbp,
			PNGInterlaceMethod interlaceMethod
		);		

		static unsigned int ScanlinesEncode
		(
			unsigned char* out,
			unsigned char* in,
			size_t width,
			size_t height,
			size_t bbp,
			PNGInterlaceMethod interlaceMethod
		);


		static size_t CaluclateExpectedSize(size_t width, size_t height, size_t bpp);
	};
}