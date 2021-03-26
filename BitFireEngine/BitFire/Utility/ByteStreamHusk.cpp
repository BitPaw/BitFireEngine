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

unsigned short BF::ByteStreamHusk::ExtractShortAndMove(EndianType endianType)
{
	Word word = ExtractWord();
	unsigned int result = word.ExtractInt(endianType);

	return result;
}

unsigned int BF::ByteStreamHusk::ExtractIntegerAndMove(EndianType endianType)
{
	DoubleWord dWord = ExtractDoubleWord();
	unsigned int result = dWord.ExtractInt(endianType);

	return result;
}

BF::DoubleWord BF::ByteStreamHusk::ExtractDoubleWord()
{
	DoubleWord dWord;

	dWord.ByteData[0] = ExtractByteAndMove();
	dWord.ByteData[1] = ExtractByteAndMove();
	dWord.ByteData[2] = ExtractByteAndMove();
	dWord.ByteData[3] = ExtractByteAndMove();

	return dWord;
}

BF::Word BF::ByteStreamHusk::ExtractWord()
{
	Word word;

	word.ByteData[0] = ExtractByteAndMove();
	word.ByteData[1] = ExtractByteAndMove();

	return word;
}

bool BF::ByteStreamHusk::IsAtEnd()
{
	return CurrentPosition >= DataLength;
}
