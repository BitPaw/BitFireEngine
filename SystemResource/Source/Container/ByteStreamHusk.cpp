#include "ByteStreamHusk.h"

#include <string.h>

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

unsigned short BF::ByteStreamHusk::ExtractShortAndMove(Endian endian)
{
	Word word = ExtractWord();
	unsigned int result = word.ExtractInt(endian);

	return result;
}

unsigned int BF::ByteStreamHusk::ExtractIntegerAndMove(Endian endian)
{
	DoubleWord dWord = ExtractDoubleWord();
	unsigned int result = dWord.ExtractInt(endian);

	return result;
}

unsigned long long BF::ByteStreamHusk::ExtractLongLongAndMove(Endian endian)
{
	QuadWord qword = ExtractQuadWord();
	unsigned long long result = qword.ExtractLongLong(endian);

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
	unsigned char* extractionPoint = StartAdress + CurrentPosition;
	const unsigned int length = 4u;
	DoubleWord dWord;

	memcpy(dWord.ByteData, extractionPoint, length);

	CurrentPosition += length;

	return dWord;
}

BF::QuadWord BF::ByteStreamHusk::ExtractQuadWord()
{
	unsigned char* extractionPoint = StartAdress + CurrentPosition;
	const unsigned int length = 8u;
	QuadWord qword;

	memcpy(qword.ByteData, extractionPoint, length);

	CurrentPosition += length;

	return qword;
}

BF::Word BF::ByteStreamHusk::ExtractWord()
{
	Word word;

	word.ByteData[0] = ExtractByteAndMove();
	word.ByteData[1] = ExtractByteAndMove();

	return word;
}

char BF::ByteStreamHusk::CompareBytesAndMove(void* data, unsigned int size)
{
	unsigned char* target = &StartAdress[CurrentPosition];
	int result = memcmp(data, target, size) == 0;

	return result;
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
