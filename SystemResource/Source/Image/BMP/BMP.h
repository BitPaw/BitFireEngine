#pragma once

#include "BMPType.h"
#include "BMPInfoHeader.h"
#include "BMPInfoHeaderType.h"

#include "../Image.h"

namespace BF
{
	// Image in BitMap-Format [.BMP]
	struct BMP
	{	
		public:
		//---[Header]-------------------------------------		
		BMPType Type; // 2 Bytes
		unsigned int SizeOfFile; 		// [4 bytes] The size of the BMP file in bytes 		
		unsigned int ReservedBlock;// [4 bytes] Reserved; actual value depends on the application that creates the image 		
		unsigned int DataOffset; // [4 Bytes] The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found. 
		//-------------------------------------------------------

		BMPInfoHeaderType InfoHeaderType;
		BMPInfoHeader InfoHeader;

		unsigned int PixelDataSize;
		unsigned char* PixelData;

		BMP();
		~BMP();

		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);
		ResourceLoadingResult ConvertFrom(Image& image);
		ResourceLoadingResult ConvertTo(Image& image);
	};
}