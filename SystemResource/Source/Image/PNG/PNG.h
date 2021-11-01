#pragma once

#include "PNGColorType.h"
#include "PNGChunk.h"

#include "../IImageFormat.h"

#include "../../Compression/ZLIB/ZLIBHeader.h"

namespace BF
{
	struct PNG : public IImageFormat
	{
		public:
		//---[ IHDR - Image Header ]----------------------------------------------
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
		unsigned char InterlaceMethod;
		//---------------------------------------------------------------------------

		//---[ IDAT - Image Data (Compressed)]---------------------------------------
		size_t ZLIBHeaderListSize;
		ZLIBHeader* ZLIBHeaderList;
		//---------------------------------------------------------------------------

		//---[ PLTE - Palette ]------------------------------------------------------
		unsigned char Palette[3];
		//---------------------------------------------------------------------------

		//---[ cHRM - PrimaryChromaticities ]----------------------------------------
		unsigned int CromaWhite[2];
		unsigned int CromaRed[2];
		unsigned int CromaGreen[2];
		unsigned int CromaBlue[2];
		//---------------------------------------------------------------------------

		//---[ sBIT - SignificantBits]-----------------------------------------------
		unsigned int SignificantBits;
		//---------------------------------------------------------------------------

		//---[ gAMA - ImageGamma ]---------------------------------------------------
		unsigned int Gamma;
		//---------------------------------------------------------------------------

		//---[ bKGD - BackgroundColor]-----------------------------------------------
		// Depends on colorType
		//---------------------------------------------------------------------------

		//---[ hIST - PaletteHistogram]----------------------------------------------

		//---------------------------------------------------------------------------

		//---[ tRNS - Transparency ]-------------------------------------------------
		// Depends on colorType
		//---------------------------------------------------------------------------

		//---[ sRGB - StandardRGBColorSpace ]----------------------------------------
		unsigned char RenderingIntent;
		//---------------------------------------------------------------------------

		//---[ pHYs - PhysicalPixelDimensions ]--------------------------------------
		unsigned int PixelsPerUnit[2];
		unsigned char UnitSpecifier;
		//---------------------------------------------------------------------------

		//---[ oFFs - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------

		//---------------------------------------------------------------------------

		//---[ sCAL - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------
	
		//---------------------------------------------------------------------------

		//---[ tIME - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------

		//---------------------------------------------------------------------------

		//---[ tEXt - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------

		//---------------------------------------------------------------------------

		//---[ zTXt - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------

		//---------------------------------------------------------------------------

		//---[ fRAc - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------

		//---------------------------------------------------------------------------

		//---[ gIFg - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------

		//---------------------------------------------------------------------------

		//---[ gIFt - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------

		//---------------------------------------------------------------------------

		//---[ gIFx - xxxxxxxxxxxxxxxxxxxxxxx ]--------------------------------------

		//---------------------------------------------------------------------------

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);

		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertFrom(Image& image);

		void PrintData();
	};
}