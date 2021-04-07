#pragma once

#include "Endian.h"

namespace BF
{
	class Word
	{
		public:
		unsigned char ByteData[2];

		Word();
		Word(unsigned char byteA, unsigned char byteB);

		void Set(unsigned char byteA, unsigned char byteB);

		unsigned int ExtractInt(Endian Endian);
		unsigned int InsertInt(Endian Endian, unsigned int value);
	};
}