#pragma once

#include "../File/Endian.h"

namespace BF
{
	class BitStreamHusk
	{
		private:
		void Allign();

		public:
		unsigned char* StartAdress;

		unsigned int CurrentPosition;
		unsigned int DataLengh;
		unsigned int CurrentBitOffset;

		unsigned int BlockSizeInBits;	

		BitStreamHusk();
		BitStreamHusk(unsigned char* startAdress, unsigned int dataLengh);
		BitStreamHusk(unsigned char* startAdress, unsigned int dataLengh, size_t startPosition);

		void RePosition(unsigned char* startAdress, unsigned int dataLengh);
		void SkipBitsToNextByte();

		unsigned int ExtractBitsAndMove(unsigned char amountOfBits);
		unsigned int ExtractBits(unsigned char amountOfBits);
		void Move(size_t amount);	

		static void PrintBinary(unsigned int number);
		static void PrintBinary(unsigned char number);
	};
}