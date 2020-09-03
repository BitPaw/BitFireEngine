#pragma once

#include "IBitMapInformationHeader.h"

// Used under Windows
class BitMapInfoHeader : public IBitMapInformationHeader
{
public:	
	// [2-Bytes] number of color planes(must be 1)
	unsigned int NumberOfColorPlanes;
			
	// [2-Bytes] number of bits per pixel, which is the color depth of the image.Typical values are 1, 4, 8, 16, 24 and 32.
	unsigned int NumberOfBitsPerPixel;

	// [4-Bytes] compression method being used.See the next table for a list of possible values
	unsigned int CompressionMethod;

	// [4-Bytes] image size.This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.
	unsigned int ImageSize;
	
	// [4-Bytes] horizontal resolution of the image. (pixel per metre, signed integer)
	int HorizontalResolution;

	// [4-Bytes] vertical resolution of the image. (pixel per metre, signed integer)
	int VerticalResolution;

	// [4-Bytes] number of colors in the color palette, or 0 to default to 2n
	unsigned int NumberOfColorsInTheColorPalette;

	// [4-Bytes] number of important colors used, or 0 when every color is important; generally ignored
	unsigned int NumberOfImportantColorsUsed;

	BitMapInfoHeader();
};