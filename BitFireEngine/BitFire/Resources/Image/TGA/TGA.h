#pragma once

#include "../../../Utility/ASCIIString.h"
#include "../../../Utility/List.hpp"
#include "TGAImageDataType.h"
#include "../Image.h"
#include "TGABitsPerPixel.h"

namespace BF
{
	// Truevision Advanced Raster Graphics Array
	struct TGA
	{
		public:	
		//---[Header]----------------------
		unsigned char ImageIDLengh;
		unsigned char ColorPaletteType;
		TGAImageDataType ImageDataType;

		unsigned short ColorPaletteChunkEntryIndex;
		unsigned short ColorPaletteChunkSize;
		unsigned char ColorPaletteEntrySizeInBits;

		unsigned short OriginX;
		unsigned short OriginY;
		unsigned short Width;
		unsigned short Height;
		TGABitsPerPixel PixelDepth;
		unsigned char ImageDescriptor;
		//---------------------------------
	
		//---[Image specification]---------
		List<unsigned char> ImageID; // Optional field containing identifying information
		List<unsigned char> ColorMapData; // Look-up table containing color map data
		List<unsigned char> ImageData; // Stored according to the image descriptor 
		//----------------------------------


		//---- Versiion 2.0 only----------------
		// Extension Area

		// Footer
		unsigned int ExtensionOffset;
		unsigned int DeveloperAreaOffset;
		unsigned char Signature[16];
		unsigned char DotField;
		unsigned char NULLField;
		//-------------------------------

		TGA();

		void Load(AsciiString& filePath);
		void Save(AsciiString& filePath);
		void Convert(Image& image);
	};
}



