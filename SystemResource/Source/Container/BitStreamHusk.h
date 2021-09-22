#pragma once

#include "../Types/Endian.h"

namespace BF
{
	class BitStreamHusk
	{
		private:
		bool _leftToRight;

		public:
		unsigned char* StartAdress;

		unsigned int CurrentPosition;
		unsigned int DataLengh;

		unsigned int BlockSizeInBytes;
		unsigned int BlockSizeInBits;
		unsigned int CurrentBitOffset;

		BitStreamHusk();
		BitStreamHusk(unsigned char* startAdress, unsigned int dataLengh, bool leftToRight);

		void RePosition(unsigned char* startAdress, unsigned int dataLengh);
		void SkipBitsToNextByte();
		unsigned int ExtractBitsAndMove(unsigned char amountOfBits);
		unsigned int GetFromCurrentPosition(unsigned char amountOfBits);	
	};
}