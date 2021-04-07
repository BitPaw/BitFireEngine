#pragma once

#include "PNGColorType.h"
#include "PNGChunk.h"

#include "../Image.h"

#include "../../Compression/ZLIB/ZLibHeader.h"

#include "../../../Color/RGB.hpp"
#include "../../../Mathematic/Geometry/Point.hpp"
#include "../../../Utility/AsciiString.h"

namespace BF
{
	struct PNG
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

		//---[ PLTE - Palette ]------------------------------------------------------
		RGB<unsigned char> Palette;
		//---------------------------------------------------------------------------

		//---[ cHRM - PrimaryChromaticities ]----------------------------------------
		Point<unsigned int> CromaWhite;
		Point<unsigned int> CromaRed;
		Point<unsigned int> CromaGreen;
		Point<unsigned int> CromaBlue;
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
		unsigned int RenderingIntent;
		//---------------------------------------------------------------------------

		//---[ pHYs - PhysicalPixelDimensions ]--------------------------------------
		Point<unsigned int> PixelsPerUnit;
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

		// Temp
		ZLibHeader zlib;

		void Load(AsciiString& filePath);
		void Save(AsciiString& filePath);
		void Convert(Image& image);
		void PrintData();
	};
}