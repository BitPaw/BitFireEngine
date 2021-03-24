#pragma once
#include "../IO/EndianType.h"

namespace BF
{
	struct DoubleWord
	{
		public:
		unsigned char ByteA;
		unsigned char ByteB;
		unsigned char ByteC;
		unsigned char ByteD;

		DoubleWord();
		DoubleWord(unsigned char byteA, unsigned char byteB, unsigned char byteC, unsigned  char byteD);

		void Set(unsigned char byteA, unsigned  char byteB, unsigned  char byteC, unsigned char byteD);

		unsigned int ExtractInt(EndianType endianType);
		unsigned int InsertInt(EndianType endianType, unsigned int value);
	};
}