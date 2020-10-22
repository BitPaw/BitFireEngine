#pragma once

#include <vector>
#include "../../IO/EndianType.h"

namespace BF
{
	class Converter
	{
		public:
		static unsigned int ConvertHexadezimalToDezimal(unsigned char hex);
		static unsigned int CovertByteToNumber(EndianType type, std::vector<unsigned char> bytes);
		static unsigned int ConvertTwoBytesToNumber(EndianType type, unsigned char byteA, unsigned char byteB);
		static unsigned int Convert4BytesToNumber(EndianType type, unsigned char byteA, unsigned char byteB, unsigned char byteC, unsigned char byteD);
	};
}