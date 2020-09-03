#pragma once

#include "BitMapType.h"

class BitMapFileHeader
{
public:
	// 2 Bytes
	BitMapType Type;

	// [4 bytes] The size of the BMP file in bytes 
	unsigned int SizeOfFile;

	// [4 bytes] Reserved; actual value depends on the application that creates the image 
	unsigned int ActualSizeOfFile;

	// The offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found. 
	unsigned int DataOffset;
};