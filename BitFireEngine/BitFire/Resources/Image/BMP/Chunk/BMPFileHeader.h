#pragma once

#include "BMPType.h"

namespace BF
{
	class BMPFileHeader
	{
	public:
		// 2 Bytes
		BMPType Type;

		// [4 bytes] The size of the BMP file in bytes 
		unsigned int SizeOfFile;

		// [4 bytes] Reserved; actual value depends on the application that creates the image 
		unsigned int ActualSizeOfFile;

		// The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found. 
		unsigned int DataOffset;

		BMPFileHeader();
	};
}