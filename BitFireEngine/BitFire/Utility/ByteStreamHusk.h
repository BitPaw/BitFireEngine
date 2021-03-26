#pragma once

#include "Word.h"
#include "DoubleWord.h"

namespace BF
{
	class ByteStreamHusk
	{
		public:
		unsigned char* StartAdress;
		unsigned int DataLength;

		unsigned int CurrentPosition;

		

		ByteStreamHusk(unsigned char* startAdress, unsigned int dataLengh);

		unsigned char ExtractByteAndMove();
		unsigned short ExtractShortAndMove(EndianType endianType);
		unsigned int ExtractIntegerAndMove(EndianType endianType);

		DoubleWord ExtractDoubleWord();
		Word ExtractWord();

		bool IsAtEnd();
	};
}