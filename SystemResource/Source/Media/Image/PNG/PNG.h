#pragma once

#include "../IImageFormat.h"

#include "Chunk/PNGImageHeader.h"
#include "Chunk/PNGPalette.h"
#include "Chunk/PNGPrimaryChromatics.h"
#include "Chunk/PNGLastModificationTime.h"
#include "Chunk/PNGBackgroundColor.h"
#include "Chunk/PNGPaletteHistogram.h"
#include "Chunk/PNGSuggestedPalette.h"
#include "Chunk/PNGPhysicalPixelDimension.h"
#include "Chunk/PNGTransparency.h"

namespace BF
{
	struct PNG : public IImageFormat
	{
		public:
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
		PNGTransparency Transparency; // tRNS
		PNGPhysicalPixelDimension PhysicalPixelDimension; // pHYs
		PNGSuggestedPalette SuggestedPalette; // sPLT
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

		PNG();
		~PNG();

		unsigned int BitsPerPixel();

		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath);

		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertFrom(Image& image);		

		//---------------------------------------------------------------------------
	};
}