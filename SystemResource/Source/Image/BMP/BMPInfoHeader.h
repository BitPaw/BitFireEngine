#pragma once

namespace BF
{
	struct BMPInfoHeader
	{
		public:	
		//---<Shared>---
		unsigned int HeaderSize; 	// Size of this header, in bytes(40)		
	
		unsigned short NumberOfBitsPerPixel; // [2-Bytes] number of bits per pixel, which is the color depth of the image.Typical values are 1, 4, 8, 16, 24 and 32.
		unsigned short NumberOfColorPlanes; // [2-Bytes] number of color planes(must be 1)

		int Width; // [4-Bytes] bitmap width in pixels(signed integer)
		int Height; // [4-Bytes] bitmap height in pixels(signed integer)
		//------------
	

		//---<BitMapInfoHeader ONLY>-------------------------------------------	
		unsigned int CompressionMethod; // [4-Bytes] compression method being used.See the next table for a list of possible values	
		unsigned int ImageSize; 	// [4-Bytes] image size.This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.

		int HorizontalResolution; 	// [4-Bytes] horizontal resolution of the image. (pixel per metre, signed integer)		
		int VerticalResolution; // [4-Bytes] vertical resolution of the image. (pixel per metre, signed integer)		

		unsigned int NumberOfColorsInTheColorPalette; // [4-Bytes] number of colors in the color palette, or 0 to default to 2n 
		unsigned int NumberOfImportantColorsUsed; 	// [4-Bytes] number of important colors used, or 0 when every color is important; generally ignored
		//---------------------------------------------------------------------

	
		//---<OS22XBitMapHeader ONLY>---
		unsigned short HorizontalandVerticalResolutions = 0; // An enumerated value specifying the units for the horizontaland vertical resolutions(offsets 38 and 42).The only defined value is 0, meaning pixels per metre		
		unsigned short DirectionOfBits = 0; // An enumerated value indicating the direction in which the bits fill the bitmap.The only defined value is 0, meaning the origin is the lower - left corner.Bits fill from left - to - right, then bottom - to - top.
		unsigned short halftoningAlgorithm = 0; // An enumerated value indicating a halftoning algorithm that should be used when rendering the image.
		unsigned int HalftoningParameterA = 0; // Halftoning parameter 1 (see below)
		unsigned int HalftoningParameterB = 0; // Halftoning parameter 2 (see below)
		unsigned int ColorEncoding = 0; // An enumerated value indicating the color encoding for each entry in the color table.The only defined value is 0, indicating RGB.
		unsigned int ApplicationDefinedByte = 0; // 	An application - defined identifier.Not used for image rendering
		//------------------------------

		BMPInfoHeader();
	};
}