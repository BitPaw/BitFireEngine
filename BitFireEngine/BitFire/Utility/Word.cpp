#include "Word.h"

BF::Word::Word()
{
	Set(0, 0);
}

BF::Word::Word(unsigned char byteA, unsigned char byteB)
{
	Set(byteA, byteB);
}

void BF::Word::Set(unsigned char byteA, unsigned char byteB)
{
	ByteData[0] = byteA;
	ByteData[1] = byteB;
}

unsigned int BF::Word::ExtractInt(EndianType endianType)
{
	switch (endianType)
	{
		case BF::EndianType::Big:
			return (ByteData[0] << 8) | (ByteData[1]);

		default:
		case BF::EndianType::Little:
			return (ByteData[0]) | (ByteData[1] << 8);
	}
}

unsigned int BF::Word::InsertInt(EndianType endianType, unsigned int value)
{
	return 0;
}
