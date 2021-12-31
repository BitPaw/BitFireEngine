#pragma once

#include "Chunk/PNGColorType.h"
#include "PNGColorTree.h"

namespace BF
{
	typedef enum LodePNGColorType
	{
		LCT_GREY = 0, /*grayscale: 1,2,4,8,16 bit*/
		LCT_RGB = 2, /*RGB: 8,16 bit*/
		LCT_PALETTE = 3, /*palette: 1,2,4,8 bit*/
		LCT_GREY_ALPHA = 4, /*grayscale with alpha: 8,16 bit*/
		LCT_RGBA = 6, /*RGB with alpha: 8,16 bit*/
		/*LCT_MAX_OCTET_VALUE lets the compiler allow this enum to represent any invalid
		byte value from 0 to 255 that could be present in an invalid PNG file header. Do
		not use, compare with or set the name LCT_MAX_OCTET_VALUE, instead either use
		the valid color type names above, or numeric values like 1 or 7 when checking for
		particular disallowed color type byte values, or cast to integer to print it.*/
		LCT_MAX_OCTET_VALUE = 255
	} LodePNGColorType;

	/*
	Color mode of an image. Contains all information required to decode the pixel
	bits to RGBA colors. This information is the same as used in the PNG file
	format, and is used both for PNG and raw image data in LodePNG.
	*/
	typedef struct LodePNGColorMode
	{
		/*header (IHDR)*/
		LodePNGColorType colortype; /*color type, see PNG standard or documentation further in this header file*/
		unsigned bitdepth;  /*bits per sample, see PNG standard or documentation further in this header file*/

		/*
		palette (PLTE and tRNS)

		Dynamically allocated with the colors of the palette, including alpha.
		This field may not be allocated directly, use lodepng_color_mode_init first,
		then lodepng_palette_add per color to correctly initialize it (to ensure size
		of exactly 1024 bytes).

		The alpha channels must be set as well, set them to 255 for opaque images.

		When decoding, by default you can ignore this palette, since LodePNG already
		fills the palette colors in the pixels of the raw RGBA output.

		The palette is only supported for color type 3.
		*/
		unsigned char* palette; /*palette in RGBARGBA... order. Must be either 0, or when allocated must have 1024 bytes*/
		size_t palettesize; /*palette size in number of colors (amount of used bytes is 4 * palettesize)*/

		/*
		transparent color key (tRNS)

		This color uses the same bit depth as the bitdepth value in this struct, which can be 1-bit to 16-bit.
		For grayscale PNGs, r, g and b will all 3 be set to the same.

		When decoding, by default you can ignore this information, since LodePNG sets
		pixels with this key to transparent already in the raw RGBA output.

		The color key is only supported for color types 0 and 2.
		*/
		unsigned key_defined; /*is a transparent color key given? 0 = false, 1 = true*/
		unsigned key_r;       /*red/grayscale component of color key*/
		unsigned key_g;       /*green component of color key*/
		unsigned key_b;       /*blue component of color key*/
	} LodePNGColorMode;

	class PNGColorCompressor
	{
		public:
		static unsigned int Decompress(const unsigned char* pixelDataIn, unsigned char* pixelDataOut, size_t width, size_t height, unsigned char bitDepth, PNGColorType colorType);
	
		static unsigned getNumColorChannels(LodePNGColorType colortype);

		static unsigned lodepng_get_bpp_lct(LodePNGColorType colortype, unsigned bitdepth);

		static int lodepng_color_mode_equal(const LodePNGColorMode* a, const LodePNGColorMode* b);
	
		/*Get RGBA16 color of pixel with index i (y * width + x) from the raw image with
given color type, but the given color type must be 16-bit itself.*/
		static void getPixelColorRGBA16(unsigned short* r, unsigned short* g, unsigned short* b, unsigned short* a,
			const unsigned char* in, size_t i, const LodePNGColorMode* mode);
		

		/*put a pixel, given its RGBA16 color, into image of any color 16-bitdepth type*/
		static void rgba16ToPixel(unsigned char* out, size_t i, const LodePNGColorMode* mode, unsigned short r, unsigned short g, unsigned short b, unsigned short a);
		

		/*Similar to getPixelColorRGBA8, but with all the for loops inside of the color
mode test cases, optimized to convert the colors much faster, when converting
to the common case of RGBA with 8 bit per channel. buffer must be RGBA with
enough memory.*/
		static void getPixelColorsRGBA8(unsigned char* buffer, size_t numpixels, const unsigned char* in, const LodePNGColorMode* mode);


		/*Similar to getPixelColorsRGBA8, but with 3-channel RGB output.*/
		static void getPixelColorsRGB8(unsigned char* buffer, size_t numpixels, const unsigned char* in, const LodePNGColorMode* mode);

		/*Get RGBA8 color of pixel with index i (y * width + x) from the raw image with given color type.*/
		static void getPixelColorRGBA8(unsigned char* r, unsigned char* g,
			unsigned char* b, unsigned char* a,
			const unsigned char* in, size_t i,
			const LodePNGColorMode* mode);


		/*put a pixel, given its RGBA color, into image of any color type*/
		static unsigned rgba8ToPixel(unsigned char* out, size_t i,
			const LodePNGColorMode* mode, PNGColorTree* tree /*for palette*/,
			unsigned char r, unsigned char g, unsigned char b, unsigned char a);


		static size_t lodepng_get_raw_size_lct(size_t w, size_t h, LodePNGColorType colortype, size_t bitdepth);
		static size_t lodepng_get_raw_size(size_t w, size_t h, const LodePNGColorMode* color);

		/*returns -1 if color not present, its index otherwise*/
		static int color_tree_get(PNGColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		/*index: bitgroup index, bits: bitgroup size(1, 2 or 4), in: bitgroup value, out: octet array to add bits to*/
		static void addColorBits(unsigned char* out, size_t index, unsigned int bits, unsigned int in);

		static unsigned char readBitFromReversedStream(size_t* bitpointer, const unsigned char* bitstream);		
		static unsigned readBitsFromReversedStream(size_t* bitpointer, const unsigned char* bitstream, size_t nbits);
	};
}