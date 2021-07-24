#pragma once

#include "Chunk/Header/BMPInfoHeader.h"
#include "Chunk/Header/IBMPInformationHeader.h"
#include "Chunk/Header/BMPInformationHeaderType.h"

#include "BMPType.h"

#include "../Image.h"

namespace BF
{
	// Image in BitMap-Format [.BMP]
	struct BMP
	{
		public:
		unsigned int Height;
		unsigned int Width;

		//---[Header]-------------------------------------		
		BMPType Type; // 2 Bytes
		unsigned int SizeOfFile; 		// [4 bytes] The size of the BMP file in bytes 		
		unsigned int ReservedBlock;// [4 bytes] Reserved; actual value depends on the application that creates the image 		
		unsigned int DataOffset; // [4 Bytes] The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found. 
		//-------------------------------------------------------

		BMPInformationHeaderType InformationHeaderType;
		IBMPInformationHeader* InformationHeader;

		List<unsigned char> PixelData;

		BMP();
		~BMP();

		// Raw Pixel, Image is already fliped!
		//RGB<unsigned char>* GetPixel(unsigned int x, unsigned int y);


		void Load(const char* filePath);
		void Save(const char* filePath);
		void Convert(Image& image);
		void PrintContent();
	};
}