#ifndef BMPInclude
#define BMPInclude

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef Image_
	typedef struct Image_ Image;
#endif

    typedef enum BMPType_
    {
        BMPInvalid,    
        BMPWindows,					// [BM] Windows 3.1x, 95, NT, ... etc.
        BMPOS2StructBitmapArray,	// [BA] OS/2 struct bitmap array        
        BMPOS2StructColorIcon,		// [CI] OS/2 struct color icon       
        BMPOS2ConstColorPointer,	// [CP] OS/2 const color pointer       
        BMPOS2StructIcon,			// [IC] OS/2 struct icon       
        BMPOS2Pointer				// [PT] OS/2 pointer
    }
	BMPType;

	// DIB header (bitmap information header) - Type / Version
	typedef enum BMPInfoHeaderType_
	{
		BMPHeaderUnkownOrInvalid,
		BMPHeaderBitMapCoreHeader, 	// [12-Bytes] Windows 2.0 or later		
		BMPHeaderOS21XBitMapHeader,  // [12-Bytes] OS/2 1.x		
		BMPHeaderOS22XBitMapHeader,  // [16-Bytes] This variant of the previous header contains only the first 16 bytes and the remaining bytes are assumed to be zero values.	
		BMPHeaderBitMapInfoHeader, 	// [40-Bytes] Windows NT, 3.1x or later		
		BMPHeaderBitMapV2InfoHeader, // [52-Bytes] Undocumented 
		BMPHeaderBitMapV3InfoHeader, // [56-Bytes] Not officially documented, but this documentation was posted on Adobe's forums,	
		BMPHeaderBitMapV4Header, 	// [108-Bytes] Windows NT 4.0, 95 or later 
		BMPHeaderBitMapV5Header 		// [124-Bytes] Windows NT 5.0, 98 or later 
	}
	BMPInfoHeaderType;

	typedef struct BitMapInfoHeader_
	{
		PXInt32U CompressionMethod; // [4-Bytes] compression method being used.See the next table for a list of possible values	
		PXInt32U ImageSize; // [4-Bytes] image size.This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.

		PXInt32S HorizontalResolution; 	// [4-Bytes] horizontal resolution of the image. (pixel per metre, signed integer)		
		PXInt32S VerticalResolution; // [4-Bytes] vertical resolution of the image. (pixel per metre, signed integer)		

		PXInt32U NumberOfColorsInTheColorPalette; // [4-Bytes] number of colors in the color palette, or 0 to default to 2n 
		PXInt32U NumberOfImportantColorsUsed; 	// [4-Bytes] number of important colors used, or 0 when every color is important; generally ignored
	}
	BitMapInfoHeader;

	typedef struct OS22XBitMapHeader_
	{
		PXInt16U HorizontalandVerticalResolutions; // An enumerated value specifying the units for the horizontaland vertical resolutions(offsets 38 and 42).The only defined value is 0, meaning pixels per metre		
		PXInt16U DirectionOfBits; // An enumerated value indicating the direction in which the bits fill the bitmap.The only defined value is 0, meaning the origin is the lower - left corner.Bits fill from left - to - right, then bottom - to - top.
		PXInt16U halftoningAlgorithm; // An enumerated value indicating a halftoning algorithm that should be used when rendering the image.
		PXInt32U HalftoningParameterA; // Halftoning parameter 1 (see below)
		PXInt32U HalftoningParameterB; // Halftoning parameter 2 (see below)
		PXInt32U ColorEncoding; // An enumerated value indicating the color encoding for each entry in the color table.The only defined value is 0, indicating RGB.
		PXInt32U ApplicationDefinedByte; // 	An application - defined identifier.Not used for image rendering
	}
	OS22XBitMapHeader;

	typedef struct BMPInfoHeader_
	{
		//---<Shared>---
		PXInt32U HeaderSize; // Size of this header, in bytes(40)

		PXInt16U NumberOfBitsPerPixel; // [2-Bytes] number of bits per pixel, which is the color depth of the image.Typical values are 1, 4, 8, 16, 24 and 32.
		PXInt16U NumberOfColorPlanes; // [2-Bytes] number of color planes(must be 1)

		PXInt32S Width; // [4-Bytes] bitmap width in pixels(signed integer)
		PXInt32S Height; // [4-Bytes] bitmap height in pixels(signed integer)
		//------------

		union
		{
			BitMapInfoHeader BitMapInfo;
			OS22XBitMapHeader OS22XBitMap;
		}
		ExtendedInfo;
	}
	BMPInfoHeader;
	   
	typedef struct BMP_
	{
		BMPType Type;

		BMPInfoHeaderType InfoHeaderType;
		BMPInfoHeader InfoHeader;

		PXSize PixelDataSize;
		void* PixelData;
	}
	BMP;

	typedef struct BMPImageDataLayout_
	{
		PXSize ImageSize;
		PXSize RowImageDataSize;
		PXSize RowPaddingSize;
		PXSize RowFullSize;
		PXSize RowAmount;
	}
	BMPImageDataLayout;

	//---<Private Functions>------------------------------------------------------
	PXPrivate BMPType ConvertToBMPType(const unsigned short bmpTypeID);
	PXPrivate unsigned short ConvertFromBMPType(const BMPType headerType);

	PXPrivate BMPInfoHeaderType ConvertToBMPInfoHeaderType(const unsigned int infoHeaderType);
	PXPrivate unsigned int ConvertFromBMPInfoHeaderType(const BMPInfoHeaderType infoHeaderType);
	//----------------------------------------------------------------------------

	//---<Public Functions--------------------------------------------------------
	PXPublic void BMPConstruct(BMP* const bmp);
	PXPublic void BMPDestruct(BMP* const bmp);

	// Calculate information about the layout how the raw image data is stored.
	// There will be "amount of vertical rows", and "pixeldata" + "padding" .
	PXPublic void BMPImageDataLayoutCalculate(BMPImageDataLayout* const bmpImageDataLayout, const PXSize width, const PXSize height, const PXSize bbp);

	//----------------------------------------------------------------------------
	PXPublic PXSize BMPFilePredictSize(const PXSize width, const PXSize height, const PXSize bitsPerPixel);

	PXPublic PXActionResult BMPParseToImage(Image* const image, PXDataStream* const dataStream);

	PXPublic PXActionResult BMPSerializeFromImage(const Image* const image, PXDataStream* const dataStream);
	//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif