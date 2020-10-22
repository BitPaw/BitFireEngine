#pragma once

#include <string>

#include "BMP.h"
#include "Chunk/BMPType.h"
#include "Chunk/Header/BMPInformationHeaderType.h"

#include "../../ILoader.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Mathematic/Math.h"
#include "../../../Mathematic/Converter/Converter.h"

namespace BF
{
	class BMPLoader : public ILoader
	{
	private:
		// Header
		static BMPInformationHeaderType GetType(unsigned char byte);
		static BMPType ParseType(unsigned char leftByte, unsigned char rightByte);

	public:
		static BMP* LoadFromFile(std::string path);
		static void SaveToFile(std::string path, BMP& bitMap);

		//static PixelArray GeneratePixelArray(BMP& bitmap);
		static void PrintBitMapInformation(BMP& bitMap);
	};
}