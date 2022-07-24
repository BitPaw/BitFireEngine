#ifndef PNGInclude
#define PNGInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum PNGColorType_
	{
		PNGColorInvalid,
		PNGColorGrayscale, // ColorType = 0
		PNGColorTruecolor,  // ColorType = 2
		PNGColorIndexedColor,  // ColorType = 3
		PNGColorGrayscaleWithAlphaChannel,  // ColorType = 4
		PNGColorTruecolorWithAlphaChannel  // ColorType = 6
	}
	PNGColorType;

	typedef enum PNGInterlaceMethod_
	{
		PNGInterlaceInvalid,
		PNGInterlaceNone,
		PNGInterlaceADAM7
	}
	PNGInterlaceMethod;

	typedef struct PNGPhysicalPixelDimension_
	{
		unsigned int PixelsPerUnit[2];
		unsigned char UnitSpecifier;
	}PNGPhysicalPixelDimension;

	typedef struct PNGPrimaryChromatics_
	{
		unsigned int WhiteX;
		unsigned int WhiteY;
		unsigned int RedX;
		unsigned int RedY;
		unsigned int GreenX;
		unsigned int GreenY;
		unsigned int BlueX;
		unsigned int BlueY;
	}PNGPrimaryChromatics;


	typedef struct PNGPalette_
	{
		unsigned char Red;
		unsigned char Green;
		unsigned char Blue;
	}PNGPalette;

	typedef struct PNGBackgroundColor_
	{
		unsigned short GreyScale;
		unsigned short Red;
		unsigned short Green;
		unsigned short Blue;
		unsigned char PaletteIndex;
	}
	PNGBackgroundColor;

	typedef struct PNGLastModificationTime_
	{
		unsigned short Year;
		unsigned char Month;
		unsigned char Day;
		unsigned char Hour;
		unsigned char Minute;
		unsigned char Second;
	}
	PNGLastModificationTime;

	typedef struct PNGPaletteHistogram_
	{
		size_t ColorFrequencyListSize;
		unsigned short* ColorFrequencyList;
	}
	PNGPaletteHistogram;





	// Chunk Specifications
	typedef enum PNGChunkType_
	{
		PNGChunkInvalid,

		//--------------------------------------------------------------------------
		// [Critical chunks]
		//--------------------------------------------------------------------------	

		PNGChunkImageHeader,	// [IHDR] The chunk will appear first.	
		PNGChunkPalette,	// [PLTE] Palette	
		PNGChunkImageData,	// [IDAT] Image data	
		PNGChunkImageEnd,	// [IEND] The chunk appears LAST. It marks the end of the PNG datastream.

		//--------------------------------------------------------------------------
		// [Ancillary chunks]
		//--------------------------------------------------------------------------
		// Transparency information
		//--------------------------------------------------------------------------

	
		PNGChunkTransparency, 	// [tRNS] Transparency

		//--------------------------------------------------------------------------
		// Color space information
		//--------------------------------------------------------------------------
			
		PNGChunkImageGamma, 	// [gAMA] Image gamma
		PNGChunkPrimaryChromaticities,		// [cHRM] -  
		PNGChunkStandardRGBColorSpace,		// [sRGB] -
		PNGChunkEmbeddedICCProfile,		// [iCCP] - 

		//--------------------------------------------------------------------------
		// Textual, information
		//--------------------------------------------------------------------------
			
		PNGChunkTextualData,	// [tEXt] - 		
		PNGChunkCompressedTextualData,// [zTXt] - 	
		PNGChunkInternationalTextualData,	// [iTXt] - 

		//--------------------------------------------------------------------------
		// Miscellaneous information
		//--------------------------------------------------------------------------
			
		PNGChunkBackgroundColor, 	// [bKGD] - 	
		PNGChunkPhysicalPixelDimensions, 	// [pHYs] - 
		PNGChunkSignificantBits, 		// [sBIT] - 
		PNGChunkSuggestedPalette,		// [sPLT] - 	
		PNGChunkPaletteHistogram,	// [hIST] - 	
		PNGChunkLastModificationTime,	// [tIME] - 

		//--------------------------------------------------------------------------
		// Additional chunk types
		//--------------------------------------------------------------------------

		// Unkown type, placegolder for future types or a midified PNG standard
		PNGChunkCustom
	}
	PNGChunkType;





	typedef	struct PNGChunk_
	{
		unsigned char IsEssential; // Ancillary Bit - Is this chunk not replaceable?.
		unsigned char IsRegisteredStandard; // Private Bit - Is this chunk in the offically registered in any way?  
		unsigned char IsSafeToCopy;  // Can this cunk be modifyed anyhow or does it have a depecdency on the imagedata?

		// [4-byte] Giving the number of bytes in the chunk's data field. The length counts only the data field, not itself, the chunk type code, or the CRC. Zero is a valid length. Although encoders and decoders should treat the length as unsigned, its value must not exceed 231 bytes. 
		unsigned int Lengh;

		char ChunkTypeRaw[4];

		// [4-byte] uppercase and lowercase ASCII letters (A-Z and a-z, or 65-90 and 97-122 decimal).
		PNGChunkType ChunkType;

		// The data bytes appropriate to the chunk type, if any. This field can be of zero length. 
		unsigned char* ChunkData;

		// A 4-byte CRC (Cyclic Redundancy Check) calculated on the preceding bytes in the chunk, including the chunk type code and chunk data fields, but not including the length field. The CRC is always present, even for chunks containing no data. See CRC algorithm. 

		unsigned char CRCOK;
		unsigned int CRC;
	}
	PNGChunk;









	typedef struct PNGImageHeader_
	{
		unsigned int Width;
		unsigned int Height;

		/*
			Bit depth is a single-byte integer giving the number of bits per sample or per palette index (not per pixel).
			Valid values are 1, 2, 4, 8, and 16, although not all values are allowed for all color types.
		*/
		unsigned char BitDepth;

		/*
			Color type is a single-byte integer that describes the interpretation of the image data.
			Color type codes represent sums of the following values: 1 (palette used), 2 (color used),
			and 4 (alpha channel used). Valid values are 0, 2, 3, 4, and 6.
		*/
		PNGColorType ColorType;
		unsigned char CompressionMethod;
		unsigned char FilterMethod;
		PNGInterlaceMethod InterlaceMethod;
	}
	PNGImageHeader;

	typedef struct PNG_
	{
		//---[Important Data]--------------------------------------------------------
		PNGImageHeader ImageHeader;
		PNGPalette Palette;
		PNGPrimaryChromatics PrimaryChromatics;
		//---------------------------------------------------------------------------

		//---[Optional Data]---------------------------------------------------------
		unsigned int SignificantBits; // sBIT
		unsigned int Gamma; // gAMA
		PNGBackgroundColor BackgroundColor; // bKGD
		PNGPaletteHistogram PaletteHistogram; // hIST
		// XXXXXXXXXXXXXX XXXXXXXXXXXXXX // cHRM
		// XXXXXXXXXXXXXX XXXXXXXXXXXXXX // iCCP
		// XXXXXXXXXXXXXX XXXXXXXXXXXXXX // cHRM
		unsigned char RenderingIntent; // sRGB
		//PNGTransparency Transparency; // tRNS
		PNGPhysicalPixelDimension PhysicalPixelDimension; // pHYs
		//PNGSuggestedPalette SuggestedPalette; // sPLT
		PNGLastModificationTime LastModificationTime; // tIME
		// XXXXXXXXXXXXXX XXXXXXXXXXXXXX // iTXt
		// 
		//---[ oFFs - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------
		//---[ sCAL - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------
		//---[ tEXt - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------
		//---[ zTXt - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------
		//---[ fRAc - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------
		//---[ gIFg - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------
		//---[ gIFt - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------
		//---[ gIFx - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------
		//---------------------------------------------------------------------------

		//---[ IDAT - Image Data (Compressed)]---------------------------------------
		//size_t ZLIBHeaderListSize;
		//ZLIBHeader* ZLIBHeaderList;
		//---------------------------------------------------------------------------

		size_t PixelDataSize;
		unsigned char* PixelData;

		//---------------------------------------------------------------------------
	}
	PNG;








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


	/*
One node of a color tree
This is the data structure used to count the number of unique colors and to get a palette
index for a color. It's like an octree, but because the alpha channel is used too, each
node has 16 instead of 8 children.
*/
	typedef struct PNGColorTree_
	{
		struct PNGColorTree_* children[16]; /*up to 16 pointers to ColorTree of next level*/
		int index; /*the payload. Only has a meaningful value if this is in the last level*/	
	}
	PNGColorTree;

	static unsigned int color_tree_add(PNGColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a, unsigned index);
	
	static unsigned int Decompress(const unsigned char* pixelDataIn, unsigned char* pixelDataOut, size_t width, size_t height, unsigned char bitDepth, PNGColorType colorType);

	static unsigned getNumColorChannels(LodePNGColorType colortype);

	static size_t lodepng_get_bpp_lct(LodePNGColorType colortype, size_t bitdepth);

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
	static void getPixelColorRGBA8(unsigned char* r, unsigned char* g,								   unsigned char* b, unsigned char* a,								   const unsigned char* in, size_t i,								   const LodePNGColorMode* mode);


	/*put a pixel, given its RGBA color, into image of any color type*/
	static unsigned rgba8ToPixel(unsigned char* out, size_t i,								 const LodePNGColorMode* mode, PNGColorTree* tree /*for palette*/,								 unsigned char r, unsigned char g, unsigned char b, unsigned char a);


	extern size_t lodepng_get_raw_size_lct(size_t w, size_t h, LodePNGColorType colortype, size_t bitdepth);
	extern size_t lodepng_get_raw_size(size_t w, size_t h, const LodePNGColorMode* color);

	/*returns -1 if color not present, its index otherwise*/
	extern int color_tree_get(PNGColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	/*index: bitgroup index, bits: bitgroup size(1, 2 or 4), in: bitgroup value, out: octet array to add bits to*/
	extern void addColorBits(unsigned char* out, size_t index, unsigned int bits, unsigned int in);

	extern unsigned char readBitFromReversedStream(size_t* bitpointer, const unsigned char* bitstream);
	extern unsigned readBitsFromReversedStream(size_t* bitpointer, const unsigned char* bitstream, size_t nbits);






	static PNGChunkType ConvertToChunkType(const unsigned int pngchunkType);
	static unsigned int ConvertFromChunkType(const PNGChunkType pngchunkType);

	static PNGColorType ConvertToPNGColorType(const unsigned int colorType);
	static unsigned int ConvertFromPNGColorType(const PNGColorType colorType);

	static PNGInterlaceMethod ConvertToPNGInterlaceMethod(const unsigned char interlaceMethod);
	static unsigned char ConvertFromPNGInterlaceMethod(const PNGInterlaceMethod interlaceMethod);



	extern void PNGConstruct(PNG* png);
	extern void PNGDestruct(PNG* png);


	extern size_t NumberOfColorChannels(const PNGColorType pngColorType);
	extern size_t BitsPerPixel(PNG* png);

	extern ActionResult PNGParse(PNG* png, const void* data, const size_t dataSize, size_t* dataRead);
	extern ActionResult PNGSerialize(PNG* png, void* data, const size_t dataSize, size_t* dataWritten);

#ifdef __cplusplus
}
#endif

#endif