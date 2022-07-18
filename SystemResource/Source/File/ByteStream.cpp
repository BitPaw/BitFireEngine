#include "ByteStream.h"
#include <cstdarg>

BF::ByteStream::ByteStream()
{
	DataSet(nullptr, 0);
}

BF::ByteStream::ByteStream(void* data, const size_t dataSize)
{
	DataSet(data, dataSize);
}

BF::ByteStream::ByteStream(const void* data, const size_t dataSize)
{
	DataSet((void*)data, dataSize);
}

size_t BF::ByteStream::ReadPossibleSize()
{
	return ParsingStreamRemainingSize(this);
}

bool BF::ByteStream::IsAtEnd()
{
	return ParsingStreamIsAtEnd(this);
}

void BF::ByteStream::DataSet(void* data, const size_t dataSize, const size_t cursorPosition)
{
	ParsingStreamConstruct(this, data, dataSize);
}

void BF::ByteStream::CursorToBeginning()
{
	ParsingStreamCursorToBeginning(this);
}

Byte__* BF::ByteStream::CursorCurrentAdress()
{
	return ParsingStreamCursorPosition(this);
}

void BF::ByteStream::CursorAdvance(const size_t steps)
{
	ParsingStreamCursorAdvance(this, steps);
}

void BF::ByteStream::CursorRewind(const size_t steps)
{
	ParsingStreamCursorRewind(this, steps);
}

void BF::ByteStream::CursorToEnd()
{
	ParsingStreamCursorToEnd(this);
}

unsigned int BF::ByteStream::ReadNextLineInto(char* exportBuffer)
{
	return ParsingStreamReadNextLineInto(this, exportBuffer, -1);
}

void BF::ByteStream::SkipEndOfLineCharacters()
{
	ParsingStreamSkipEndOfLineCharacters(this);
}

void BF::ByteStream::SkipEmpty()
{
	ParsingStreamSkipEmptySpace(this);
}

void BF::ByteStream::SkipBlock()
{
	ParsingStreamSkipBlock(this);
}

size_t BF::ByteStream::SkipLine()
{
	return ParsingStreamSkipLine(this);
}

void BF::ByteStream::Read(bool& value)
{
	unsigned char byte = 0;

	ParsingStreamReadCU(this, &byte);

	value = byte;
}

void BF::ByteStream::Read(char& value)
{
	ParsingStreamReadC(this, &value);
}

void BF::ByteStream::Read(unsigned char& value)
{
	ParsingStreamReadCU(this, &value);
}

void BF::ByteStream::Read(short& value, const Endian endian)
{
	ParsingStreamReadS(this, &value, endian);
}

void BF::ByteStream::Read(unsigned short& value, const Endian endian)
{
	ParsingStreamReadSU(this, &value, endian);
}

void BF::ByteStream::Read(int& value, const Endian endian)
{
	ParsingStreamReadI(this, &value, endian);
}

void BF::ByteStream::Read(unsigned int& value, const Endian endian)
{
	ParsingStreamReadIU(this, &value, endian);
}

void BF::ByteStream::Read(unsigned long long& value, const Endian endian)
{
	ParsingStreamReadULL(this, &value, endian);
}

void BF::ByteStream::Read(void* value, const size_t length)
{
	ParsingStreamReadD(this, value, length);
}

void BF::ByteStream::ReadUntil(char* value, const size_t length, const char character)
{
	ParsingStreamReadUntil(this, value, length, character);
}

void BF::ByteStream::ReadUntil(wchar_t* value, const size_t length, const wchar_t character)
{	
	ParsingStreamReadUntil(this, value, length, character);
}

size_t BF::ByteStream::ReadSafe(Byte__* value, const size_t length)
{
	const size_t possibleReadSize = ReadPossibleSize();
	const bool canFullfill = possibleReadSize >= length;
	const size_t readBytes = canFullfill ? length : possibleReadSize;

	Read(value, readBytes);

	return readBytes;
}

bool BF::ByteStream::ReadAndCompare(const Byte__* value, const size_t length)
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
	return ParsingStreamReadAndCompare(this, value, length);
}

bool BF::ByteStream::ReadAndCompare(const unsigned int value)
{
	return ParsingStreamReadAndCompare(this, &value, sizeof(unsigned int));
}

void BF::ByteStream::Write(const bool value)
{
	const unsigned char valueChar = value;

	Write(valueChar);
}

void BF::ByteStream::Write(const char value)
{
	ParsingStreamWriteC(this, value);
}

void BF::ByteStream::Write(const unsigned char value)
{
	ParsingStreamWriteC(this, value);
}

void BF::ByteStream::Write(const short value, const Endian endian)
{
	ParsingStreamWriteS(this, value, endian);
}

void BF::ByteStream::Write(const unsigned short value, const Endian endian)
{
	ParsingStreamWriteSU(this, value, endian);
}

void BF::ByteStream::Write(const int value, const Endian endian)
{
	ParsingStreamWriteSU(this, value, endian);
}

void BF::ByteStream::Write(unsigned int value, const Endian endian)
{
	ParsingStreamWriteSU(this, value, endian);
}

void BF::ByteStream::Write(const long long value, const Endian endian)
{
	ParsingStreamWriteSU(this, value, endian);
}

void BF::ByteStream::Write(const unsigned long long value, const Endian endian)
{
	ParsingStreamWriteSU(this, value, endian);
}

void BF::ByteStream::Write(const char* value, const size_t length)
{
	ParsingStreamWriteD(this, (void*)value, length);
}

void BF::ByteStream::Write(const unsigned char* value, const size_t length)
{
	ParsingStreamWriteD(this, (void*)value, length);
}

void BF::ByteStream::Write(const void* value, const size_t length)
{
	ParsingStreamWriteD(this, (void*)value, length);
}

size_t BF::ByteStream::Write(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	size_t readBytes = ParsingStreamWrite(this, format, args);

	va_end(args);
	
	return readBytes;
}