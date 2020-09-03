#pragma once

#ifndef BF_BitMapLoader
#define BF_BitMapLoader

#include <string>
#include <vector>

#include "BitMap.h"
#include "Chunk/BitMapType.h"
#include "Chunk/Header/BitMapInformationHeaderType.h"

#include "../PixelArray/PixelArray.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Mathematic/Converter/Converter.h"

class BitMapLoader
{
private:
	// Header
	static BitMapInformationHeaderType GetType(unsigned char byte);
	static BitMapType ParseType(unsigned char leftByte, unsigned char rightByte);

public:
	static BitMap LoadFromFile(std::string path);
	static void SaveToFile(std::string path, BitMap& bitMap);

	static PixelArray GeneratePixelArray(BitMap& bitmap);
	static void PrintBitMapInformation(BitMap& bitMap);
};
#endif 