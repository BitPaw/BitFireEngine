#pragma once

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
		unsigned int ExtractIntegerAndMove();
		DoubleWord ExtractDoubleWord();

		bool IsAtEnd();
	};
}