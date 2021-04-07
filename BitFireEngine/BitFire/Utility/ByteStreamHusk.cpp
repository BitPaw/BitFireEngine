#include "ByteStreamHusk.h"

#include <vcruntime_string.h>

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

unsigned short BF::ByteStreamHusk::ExtractShortAndMove(Endian Endian)
{
	Word word = ExtractWord();
	unsigned int result = word.ExtractInt(Endian);

	return result;
}

unsigned int BF::ByteStreamHusk::ExtractIntegerAndMove(Endian Endian)
{
	DoubleWord dWord = ExtractDoubleWord();
	unsigned int result = dWord.ExtractInt(Endian);

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

void BF::ByteStreamHusk::CopyBytesAndMove(char* destination, unsigned int size)
{
	CopyBytesAndMove((unsigned char*)(destination), size);
}

void BF::ByteStreamHusk::CopyBytesAndMove(unsigned char* destination, unsigned int size)
{
	memcpy(destination, &StartAdress[CurrentPosition], size);

	CurrentPosition += size;
}

bool BF::ByteStreamHusk::IsAtEnd()
{
	return CurrentPosition >= DataLength;
}
