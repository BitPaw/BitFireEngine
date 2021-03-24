#pragma once

#include <string>

#include "BMP.h"
#include "Chunk/BMPType.h"
#include "Chunk/Header/BMPInformationHeaderType.h"

#include "../../ILoader.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Mathematic/Math.h"

namespace BF
{
	class BMPLoader : public ILoader
	{
	private:
		// Header
		static BMPInformationHeaderType GetType(unsigned char byte);
		static BMPType ParseType(unsigned char leftByte, unsigned char rightByte);

	public:
		static BMP* LoadFromFile(AsciiString& path);
		static void SaveToFile(AsciiString& path, BMP& bitMap);

		//static PixelArray GeneratePixelArray(BMP& bitmap);
		static void PrintBitMapInformation(BMP& bitMap);
	};
}