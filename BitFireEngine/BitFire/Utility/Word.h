#pragma once
#include "../IO/EndianType.h"

namespace BF
{
	class Word
	{
		public:
		char ByteA;
		char ByteB;

		Word();
		Word(char byteA, char byteB);

		void Set(char byteA, char byteB);

		unsigned int ExtractInt(EndianType endianType);
		unsigned int InsertInt(EndianType endianType, unsigned int value);
	};
}