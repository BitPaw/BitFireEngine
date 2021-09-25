#include "BMPInfoHeader.h"

BF::BMPInfoHeader::BMPInfoHeader()
{
	HeaderSize = 40u;
	NumberOfBitsPerPixel = 24u;
	NumberOfColorPlanes = 1u;
	Width = 0;
	Height = 0;

	CompressionMethod = 0;
	ImageSize = 0;
	HorizontalResolution = 1u;
	VerticalResolution = 1u;

	NumberOfColorsInTheColorPalette = 0;
	NumberOfImportantColorsUsed = 0;

	HorizontalandVerticalResolutions = 0;
	DirectionOfBits = 0; 
	halftoningAlgorithm = 0; 
	HalftoningParameterA = 0;
	HalftoningParameterB = 0; 
	ColorEncoding = 0; 
	ApplicationDefinedByte = 0; 
}