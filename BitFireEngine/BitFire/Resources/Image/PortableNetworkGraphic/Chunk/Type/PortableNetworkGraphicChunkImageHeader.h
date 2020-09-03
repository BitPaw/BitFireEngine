#pragma once
class PortableNetworkGraphicChunkImageHeader
{
public:
	const unsigned int DataSizeInBytes = 13;

	// Image width in pixels [Range (1 - 2^31)]
	unsigned int Width;

	// Image height in pixels [Range (1 - 2^31)]
	unsigned int Height;

	// Number of bits per sample or per palette index (not per pixel). Valid values are 1, 2, 4, 8, and 16, although not all values are allowed for all color types. 
	unsigned char BitDepth;

	//
	unsigned char ColorType;

	//
	unsigned char CompressionMethod;

	//
	unsigned char FilterMethod;

	//
	unsigned char InterlaceMethod;
};