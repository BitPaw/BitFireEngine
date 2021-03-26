#pragma once
#include "../IO/EndianType.h"

namespace BF
{
	class Word
	{
		public:
		unsigned char ByteData[2];

		Word();
		Word(unsigned char byteA, unsigned char byteB);

		void Set(unsigned char byteA, unsigned char byteB);

		unsigned int ExtractInt(EndianType endianType);
		unsigned int InsertInt(EndianType endianType, unsigned int value);
	};
}