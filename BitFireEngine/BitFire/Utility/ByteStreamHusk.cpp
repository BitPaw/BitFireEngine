#include "ByteStreamHusk.h"

BF::ByteStreamHusk::ByteStreamHusk(unsigned char* startAdress, unsigned int dataLengh)
{
	StartAdress = startAdress;
	DataLength = dataLengh;
	CurrentPosition = 0;
}

unsigned char BF::ByteStreamHusk::ExtractByteAndMove()
{
	return StartAdress[CurrentPosition++];
}

unsigned int BF::ByteStreamHusk::ExtractIntegerAndMove()
{
	DoubleWord dWord = ExtractDoubleWord();
	unsigned int result = dWord.ExtractInt(EndianType::Big);

	return result;
}

BF::DoubleWord BF::ByteStreamHusk::ExtractDoubleWord()
{
	DoubleWord dWord;

	dWord.ByteA = ExtractByteAndMove();
	dWord.ByteB = ExtractByteAndMove();
	dWord.ByteC = ExtractByteAndMove();
	dWord.ByteD = ExtractByteAndMove();

	return dWord;
}

bool BF::ByteStreamHusk::IsAtEnd()
{
	return CurrentPosition >= DataLength;
}
