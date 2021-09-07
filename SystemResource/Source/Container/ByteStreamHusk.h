#pragma once

#include "../Types/QuadWord.h"
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

		Word ExtractWord();
		DoubleWord ExtractDoubleWord();
		QuadWord ExtractQuadWord();
		unsigned char ExtractByteAndMove();
		unsigned short ExtractShortAndMove(Endian Endian);
		unsigned int ExtractIntegerAndMove(Endian Endian);
		unsigned long long ExtractLongLongAndMove(Endian Endian);

		void InsertShortAndMove(Endian Endian, unsigned short value);
		void InsertIngegerAndMove(Endian Endian, unsigned int value);
		void InsertArrayAndMove(void* data, unsigned int length);	

		char CompareBytesAndMove(void* data, unsigned int size);

		void CopyBytesAndMove(char* destination, unsigned int size);
		void CopyBytesAndMove(unsigned char* destination, unsigned int size);

		bool IsAtEnd();
	};
}