#include "ByteStream.h"
#include <cassert>
#include <cstring>

#include <Text/Text.h>

BF::ByteStream::ByteStream()
{
	DataSet(nullptr, 0);
}

BF::ByteStream::ByteStream(Byte* data, size_t dataSize)
{
	DataSet(data, dataSize);
}

void BF::ByteStream::DataSet(Byte* data, size_t dataSize, size_t cursorPosition)
{
	Data = data;
	DataSize = dataSize;
	DataCursorPosition = cursorPosition;
}

void BF::ByteStream::CursorToBeginning()
{
	DataCursorPosition = 0;
}

Byte* BF::ByteStream::CursorCurrentAdress()
{
	return Data + DataCursorPosition;
}

void BF::ByteStream::CursorAdvance(const size_t steps)
{
	DataCursorPosition += steps;
}

unsigned int BF::ByteStream::ReadNextLineInto(char* exportBuffer)
{
	SkipEndOfLineCharacters();

	const size_t beginningPosition = DataCursorPosition;	
	const char* input = (char*)Data + beginningPosition;
	size_t length = 0;

	for 
	(
		; 
		DataCursorPosition < DataSize && // End of length
		Data[DataCursorPosition] != '\r' && // Windows additional "Return cursor"
		Data[DataCursorPosition] != '\n' && // Line-End
		Data[DataCursorPosition] != '\0' // End Of String
		;
		++DataCursorPosition
	);

	length = DataCursorPosition - beginningPosition;

	if (length == 0)
	{
		return 0;
	}

	Text::Copy(exportBuffer, input, length);

	SkipEndOfLineCharacters();

	return length;
}

void BF::ByteStream::SkipEndOfLineCharacters()
{
	for
		(
			;
			DataCursorPosition < DataSize && (Data[DataCursorPosition] == '\r' || Data[DataCursorPosition] == '\n') && Data[DataCursorPosition] != '\0'
			;
			++DataCursorPosition
			);
}

void BF::ByteStream::Read(bool& value)
{
	char byte = Data[DataCursorPosition++];

	switch (byte)
	{
		case '1':
		case 1:
			value = true;
			break;

		default:
			value = false;
			break;
	}
}

void BF::ByteStream::Read(char& value)
{
	Read((unsigned char&)value);
}

void BF::ByteStream::Read(unsigned char& value)
{
	value = Data[DataCursorPosition++];
}

void BF::ByteStream::Read(short& value, Endian endian)
{
	Read((unsigned short&)value, endian);
}

void BF::ByteStream::Read(unsigned short& value, Endian endian)
{
	unsigned char valueData[2];

	Read(valueData, 2u);

	switch (endian)
	{
		case Endian::Big:
			value =
				(valueData[0] << 8) |
				(valueData[1]);

			break;

		default:
		case Endian::Little:
			value =
				(valueData[0]) |
				(valueData[1] << 8);
			break;
	}

	//assert(value < 65408);
}

void BF::ByteStream::Read(int& value, Endian endian)
{
	Read((unsigned int&)value, endian);
}

void BF::ByteStream::Read(unsigned int& value, Endian endian)
{
	unsigned char valueData[4];

	Read(valueData, 4u);

	switch (endian)
	{
		case Endian::Big:
			value =
				(valueData[0] << 24) |
				(valueData[1] << 16) |
				(valueData[2] << 8) |
				(valueData[3]);

			break;

		default:
		case Endian::Little:
			value =
				(valueData[0]) |
				(valueData[1] << 8) |
				(valueData[2] << 16) |
				(valueData[3] << 24);
			break;
	}
}

void BF::ByteStream::Read(unsigned long long& value, Endian endian)
{
	unsigned char valueData[8];

	Read(valueData, 8u);

	switch (endian)
	{
		case Endian::Big:
		{
			value =
				((unsigned long long)valueData[0] << 56LL) |
				((unsigned long long)valueData[1] << 48LL) |
				((unsigned long long)valueData[2] << 40LL) |
				((unsigned long long)valueData[3] << 32LL) |
				((unsigned long long)valueData[4] << 24LL) |
				((unsigned long long)valueData[5] << 16LL) |
				((unsigned long long)valueData[6] << 8LL) |
				((unsigned long long)valueData[7]);

			break;
		}
		default:
		case Endian::Little:
			value =
				((unsigned long long)valueData[0]) |
				((unsigned long long)valueData[1] << 8LL) |
				((unsigned long long)valueData[2] << 16LL) |
				((unsigned long long)valueData[3] << 24LL) |
				((unsigned long long)valueData[4] << 32LL) |
				((unsigned long long)valueData[5] << 40LL) |
				((unsigned long long)valueData[6] << 48LL) |
				((unsigned long long)valueData[7] << 56LL);
			break;
	}
}

void BF::ByteStream::Read(void* value, size_t length)
{
	memcpy(value, Data + DataCursorPosition, length);

	DataCursorPosition += length;
}

bool BF::ByteStream::ReadAndCompare(const Byte* value, size_t length)
{
	return ReadAndCompare((void*)value, length);
}

bool BF::ByteStream::ReadAndCompare(const char* value, size_t length)
{
	return ReadAndCompare((void*)value, length);
}

bool BF::ByteStream::ReadAndCompare(void* value, size_t length)
{
	bool result = memcmp(value, Data + DataCursorPosition, length) == 0;

	DataCursorPosition += length;

	return result;
}

bool BF::ByteStream::ReadAndCompare(const unsigned int value)
{
	const unsigned char* sourceAdress = Data + DataCursorPosition;
	const unsigned int sourceValue = *((unsigned int*)sourceAdress);

	const bool isEqual = sourceValue == value;

	DataCursorPosition += 4;

	return isEqual;
}

void BF::ByteStream::Write(bool value)
{
	Data[DataCursorPosition++] = value;
}

void BF::ByteStream::Write(char value)
{
	Data[DataCursorPosition++] = value;
}

void BF::ByteStream::Write(unsigned char value)
{
	Data[DataCursorPosition++] = value;
}

void BF::ByteStream::Write(short value, Endian endian)
{
	Write((unsigned short)value, endian);
}

void BF::ByteStream::Write(unsigned short value, Endian endian)
{
	unsigned char valueData[2];

	switch (endian)
	{
		case Endian::Big:
		{
			valueData[0] = (value & 0xFF00) >> 8;
			valueData[1] = (value & 0x00FF);
			break;
		}
		default:
		case Endian::Little:
		{
			valueData[0] = (value & 0x00FF);
			valueData[1] = (value & 0xFF00) >> 8;
			break;
		}
	}

	Write(valueData, 2u);
}

void BF::ByteStream::Write(int value, Endian endian)
{
	Write((unsigned int)value, endian);
}

void BF::ByteStream::Write(unsigned int value, Endian endian)
{
	unsigned char valueData[4];

	switch (endian)
	{
		case Endian::Big:
		{
			valueData[0] = (value & 0xFF000000) >> 24;
			valueData[1] = (value & 0x00FF0000) >> 16;
			valueData[2] = (value & 0x0000FF00) >> 8;
			valueData[3] = value & 0x000000FF;
			break;
		}
		default:
		case Endian::Little:
		{
			valueData[0] = value & 0x000000FF;
			valueData[1] = (value & 0x0000FF00) >> 8;
			valueData[2] = (value & 0x00FF0000) >> 16;
			valueData[3] = (value & 0xFF000000) >> 24;
			break;
		}
	}

	Write(valueData, 4u);
}

void BF::ByteStream::Write(const char* string, size_t length)
{
	Write((void*)string, length);
}

void BF::ByteStream::Write(unsigned long long& value, Endian endian)
{
}

void BF::ByteStream::Write(void* value, size_t length)
{
	memcpy(Data + DataCursorPosition, value, length);

	DataCursorPosition += length;
}