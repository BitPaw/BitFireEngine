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

void BF::ByteStreamHusk::InsertShortAndMove(Endian Endian, unsigned short value)
{
	unsigned char* data = StartAdress + CurrentPosition;
	unsigned char integerData[2];

	memcpy(integerData, &value, 2);

	switch (Endian)
	{
		case BF::Endian::Big:
			data[0] = integerData[1];
			data[1] = integerData[0];
			break;

		default:
		case BF::Endian::Little:
			data[0] = integerData[0];
			data[1] = integerData[1];
			break;
	}

	CurrentPosition += 2;
}

void BF::ByteStreamHusk::InsertIngegerAndMove(Endian Endian, unsigned int value)
{
	unsigned char* data = StartAdress + CurrentPosition;

	unsigned char integerData[4];	

	memcpy(integerData, &value, 4);

	switch (Endian)
	{
		case BF::Endian::Big:
			data[0] = integerData[3];
			data[1] = integerData[2];
			data[2] = integerData[1];
			data[3] = integerData[0];
			break;

		default:		
		case BF::Endian::Little:
			data[0] = integerData[0];
			data[1] = integerData[1];
			data[2] = integerData[2];
			data[3] = integerData[3];
			break;
	}

	CurrentPosition += 4;
}

void BF::ByteStreamHusk::InsertArrayAndMove(void* data, unsigned int length)
{
	unsigned char* insertionPoint = StartAdress + CurrentPosition;

	memcpy(insertionPoint, data, length);

	CurrentPosition += length;
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
