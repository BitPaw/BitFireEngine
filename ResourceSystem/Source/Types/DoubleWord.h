#pragma once

#include "Endian.h"

namespace BF
{
	struct DoubleWord
	{
		public:
		unsigned char ByteData[4];

		DoubleWord();
		DoubleWord(unsigned char byteA, unsigned char byteB, unsigned char byteC, unsigned  char byteD);

		void Set(unsigned char byteA, unsigned  char byteB, unsigned  char byteC, unsigned char byteD);

		unsigned int ExtractInt(Endian endian);
		unsigned int InsertInt(Endian endian, unsigned int value);
	};
}