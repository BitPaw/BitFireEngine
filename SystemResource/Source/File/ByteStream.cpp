#include "ByteStream.h"

#include <cassert>
#include <cstring>

#include <Text/Text.h>
#include <Hardware/Memory/Memory.h>

#include <iso646.h>
#include <cstdarg>

#define InRange DataCursorPosition < DataSize	
#define NotEndOfString Data[DataCursorPosition] != '\0'
#define EndOfString Data[DataCursorPosition] == '\0'
#define EndOfLineCharacter (Data[DataCursorPosition] == '\r' || Data[DataCursorPosition] == '\n')

BF::ByteStream::ByteStream()
{
	DataSet(nullptr, 0);
}

BF::ByteStream::ByteStream(Byte* data, const size_t dataSize)
{
	DataSet(data, dataSize);
}

BF::ByteStream::ByteStream(const Byte* data, const size_t dataSize)
{
	DataSet(data, dataSize);
}

size_t BF::ByteStream::ReadPossibleSize() const
{
	return DataSize - DataCursorPosition;
}

bool BF::ByteStream::IsAtEnd() const
{
	return ReadPossibleSize() == 0;
}

void BF::ByteStream::DataSet(const Byte* data, const size_t dataSize, const size_t cursorPosition)
{
	Data = (Byte*)data;
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

void BF::ByteStream::CursorRewind(const size_t steps)
{
	DataCursorPosition -= steps;
}

void BF::ByteStream::CursorToEnd()
{
	DataCursorPosition = DataSize;
}

unsigned int BF::ByteStream::ReadNextLineInto(char* exportBuffer)
{
	SkipEndOfLineCharacters();

	const size_t beginningPosition = DataCursorPosition;	
	const char* input = (char*)Data + beginningPosition;
	size_t length = 0;

	while(InRange and !EndOfLineCharacter and NotEndOfString) ++DataCursorPosition;

	length = DataCursorPosition - beginningPosition;

	if (length == 0)
	{
		return 0;
	}

	Text::Copy(input, length, exportBuffer, length);

	SkipEndOfLineCharacters();

	return length;
}

void BF::ByteStream::SkipEndOfLineCharacters()
{
	while(InRange)
	{
		const bool advance = EndOfLineCharacter and NotEndOfString;

		if(!advance)
		{
			break;
		}

		++DataCursorPosition;
	}
}

void BF::ByteStream::SkipLine()
{
	while(InRange)
	{
		const bool advance = !EndOfLineCharacter and NotEndOfString;

		if(!advance)
		{
			break;
		}

		++DataCursorPosition;
	}

	SkipEndOfLineCharacters();
}

void BF::ByteStream::Read(bool& value)
{
	char byte = 0;

	Read((unsigned char&)byte);

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

void BF::ByteStream::Read(short& value, const Endian endian)
{
	Read((unsigned short&)value, endian);
}

void BF::ByteStream::Read(unsigned short& value, const Endian endian)
{
	const Byte* data = Data + DataCursorPosition;

	switch (endian)
	{
		case Endian::Big:
			value = MakeShortBE(data[0], data[1]);
			break;

		default:
		case Endian::Little:
			value = MakeShortLE(data[0], data[1]);
			break;
	}

	DataCursorPosition += sizeof(unsigned short);
}

void BF::ByteStream::Read(int& value, const Endian endian)
{
	Read((unsigned int&)value, endian);
}

void BF::ByteStream::Read(unsigned int& value, const Endian endian)
{
	const Byte* data = Data + DataCursorPosition;

	switch (endian)
	{
		case Endian::Big:
			value = MakeIntBE(data[0], data[1], data[2], data[3]);
			break;

		default:
		case Endian::Little:
			value = MakeIntLE(data[0], data[1], data[2], data[3]);
			break;
	}

	DataCursorPosition += sizeof(unsigned int);
}

void BF::ByteStream::Read(unsigned long long& value, const Endian endian)
{
	const Byte* data = Data + DataCursorPosition;

	switch (endian)
	{
		case Endian::Big:
		{
			value = MakeLongLongBE(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
			break;
		}
		default:
		case Endian::Little:
		{
			value = MakeLongLongLE(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
			break;
		}	
	}

	DataCursorPosition += sizeof(unsigned long long);
}

void BF::ByteStream::Read(void* value, const size_t length)
{
	Memory::Copy(value, Data + DataCursorPosition, length);

	DataCursorPosition += length;
}

void BF::ByteStream::ReadUntil(char* value, const size_t length, const char character)
{
	Byte* start = Data + DataCursorPosition;
	size_t lengthCopy = 0;

	while(InRange && Data[DataCursorPosition] != character && length <= lengthCopy)
	{
		++DataCursorPosition;
	}

	lengthCopy = DataCursorPosition;

	Memory::Copy(value, start, lengthCopy);
}

void BF::ByteStream::ReadUntil(wchar_t* value, const size_t length, const wchar_t character)
{	
	wchar_t* start = (wchar_t*)(Data + DataCursorPosition);
	const size_t characterOffset = sizeof(wchar_t);
	size_t lengthCopy = 0;

	while(InRange && *(wchar_t*)(Data + DataCursorPosition) != character && lengthCopy <= length)
	{
		DataCursorPosition += characterOffset;
		lengthCopy += characterOffset;
	}	

	DataCursorPosition += characterOffset;

	Memory::Copy(value, start, lengthCopy);
}

size_t BF::ByteStream::ReadSafe(Byte* value, const size_t length)
{
	const size_t possibleReadSize = ReadPossibleSize();
	const bool canFullfill = possibleReadSize >= length;
	const size_t readBytes = canFullfill ? length : possibleReadSize;

	Read(value, readBytes);

	return readBytes;
}

bool BF::ByteStream::ReadAndCompare(const Byte* value, const size_t length)
{
	return ReadAndCompare((void*)value, length);
}

bool BF::ByteStream::ReadAndCompare(const char* value, const size_t length)
{
	return ReadAndCompare((void*)value, length);
}

bool BF::ByteStream::ReadAndCompare(const char value)
{
	return ReadAndCompare(&value, sizeof(char));
}

bool BF::ByteStream::ReadAndCompare(const void* value, const size_t length)
{
	bool result = Memory::Compare(value, Data + DataCursorPosition, length) == 0;

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

void BF::ByteStream::Write(const bool value)
{
	Data[DataCursorPosition++] = value;
}

void BF::ByteStream::Write(const char value)
{
	Data[DataCursorPosition++] = value;
}

void BF::ByteStream::Write(const unsigned char value)
{
	Data[DataCursorPosition++] = value;
}

void BF::ByteStream::Write(const short value, const Endian endian)
{
	Write((unsigned short)value, endian);
}

void BF::ByteStream::Write(const unsigned short value, const Endian endian)
{
	Byte* data = Data + DataCursorPosition;

	ClusterShort clusterShort;

	clusterShort.Value = value;

	switch (endian)
	{
		case Endian::Big:
		{	
			data[0] = clusterShort.A;
			data[1] = clusterShort.B;
			break;
		}
		default:
		case Endian::Little:
		{
			data[0] = clusterShort.B;
			data[1] = clusterShort.A;
			break;
		}
	}

	DataCursorPosition += sizeof(unsigned short);
}

void BF::ByteStream::Write(const int value, const Endian endian)
{
	Write((unsigned int)value, endian);
}

void BF::ByteStream::Write(unsigned int value, const Endian endian)
{
	Byte* data = Data + DataCursorPosition;

	ClusterInt clusterInt;

	clusterInt.Value = value;

	switch (endian)
	{
		case Endian::Big:
		{
			data[0] = clusterInt.A;
			data[1] = clusterInt.B;
			data[2] = clusterInt.C;
			data[3] = clusterInt.D;
			break;
		}
		default:
		case Endian::Little:
		{
			data[0] = clusterInt.D;
			data[1] = clusterInt.C;
			data[2] = clusterInt.B;
			data[3] = clusterInt.A;
			break;
		}
	}

	DataCursorPosition += sizeof(unsigned int);
}

void BF::ByteStream::Write(const long long value, const Endian endian)
{
	Write((unsigned long long)value, endian);
}

void BF::ByteStream::Write(const unsigned long long value, const Endian endian)
{
	Byte* data = Data + DataCursorPosition;

	ClusterLongLong clusterLongLong;

	clusterLongLong.Value = value;

	switch(endian)
	{
		case Endian::Big:
		{
			data[0] = clusterLongLong.A;
			data[1] = clusterLongLong.B;
			data[2] = clusterLongLong.C;
			data[3] = clusterLongLong.D;
			data[4] = clusterLongLong.E;
			data[5] = clusterLongLong.F;
			data[6] = clusterLongLong.G;
			data[7] = clusterLongLong.H;
			break;
		}
		default:
		case Endian::Little:
		{
			data[0] = clusterLongLong.H;
			data[1] = clusterLongLong.G;
			data[2] = clusterLongLong.F;
			data[3] = clusterLongLong.E;
			data[4] = clusterLongLong.D;
			data[5] = clusterLongLong.C;
			data[6] = clusterLongLong.B;
			data[7] = clusterLongLong.A;
			break;
		}
	}

	DataCursorPosition += sizeof(unsigned long long);
}

void BF::ByteStream::Write(const char* value, const size_t length)
{
	Write((void*)value, length);
}

void BF::ByteStream::Write(const unsigned char* value, const size_t length)
{
	Write((void*)value, length);
}

void BF::ByteStream::Write(const void* value, const size_t length)
{
	Memory::Copy(Data + DataCursorPosition, value, length);

	DataCursorPosition += length;
}

size_t BF::ByteStream::Write(const char* format, ...)
{
	char* currentPosition = (char*)Data + DataCursorPosition;

	va_list args;
	va_start(args, format);

	int writtenBytes = vsprintf(currentPosition, format, args);

	va_end(args);
	
	{
		const bool sucessful = writtenBytes >= 0;

		if(!sucessful)
		{
			return 0;
		}
	}	

	DataCursorPosition += writtenBytes;

	return writtenBytes;
}