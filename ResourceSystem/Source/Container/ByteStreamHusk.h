#pragma once

#include "../Types/DoubleWord.h"
#include "../Types/Word.h"

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
		unsigned short ExtractShortAndMove(Endian Endian);
		unsigned int ExtractIntegerAndMove(Endian Endian);

		void InsertShortAndMove(Endian Endian, unsigned short value);
		void InsertIngegerAndMove(Endian Endian, unsigned int value);
		void InsertArrayAndMove(void* data, unsigned int length);

		DoubleWord ExtractDoubleWord();
		Word ExtractWord();

		void CopyBytesAndMove(char* destination, unsigned int size);
		void CopyBytesAndMove(unsigned char* destination, unsigned int size);

		bool IsAtEnd();
	};
}