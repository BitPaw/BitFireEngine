#pragma once

#include "../IImageFormat.h"

#include "Chunk/PNGImageHeader.h"
#include "Chunk/PNGPalette.h"
#include "Chunk/PNGPrimaryChromatics.h"

namespace BF
{
	struct PNG : public IImageFormat
	{
		public:
		PNGImageHeader ImageHeader;
		//---[ IDAT - Image Data (Compressed)]---------------------------------------
		//size_t ZLIBHeaderListSize;
		//ZLIBHeader* ZLIBHeaderList;
		//---------------------------------------------------------------------------
		PNGPalette Palette;
		PNGPrimaryChromatics PrimaryChromatics;	

		//---[ sBIT - SignificantBits]-----------------------------------------------
		unsigned int SignificantBits;
		//---------------------------------------------------------------------------

		//---[ gAMA - ImageGamma ]---------------------------------------------------
		unsigned int Gamma;
		//---------------------------------------------------------------------------

		//---[ bKGD - BackgroundColor]-----------------------------------------------
		unsigned short BackgroundColorGreyScale; 
		unsigned short BackgroundColorRed;
		unsigned short BackgroundColorGreen;
		unsigned short BackgroundColorBlue;
		unsigned char BackgroundColorPaletteIndex;
		//---------------------------------------------------------------------------

		//---[ hIST - PaletteHistogram]----------------------------------------------
		size_t ColorFrequencyListSize;
		unsigned short* ColorFrequencyList;
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
		unsigned short Year;
		unsigned char Month;
		unsigned char Day;
		unsigned char Hour;
		unsigned char Minute;
		unsigned char Second;
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

		size_t PixelDataSize;
		Byte* PixelData;

		unsigned int BitsPerPixel();

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);

		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertFrom(Image& image);		
	};
}