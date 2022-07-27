#include "ParsingStreamX.h"

#include <cstdarg>

BF::ParsingStreamX::ParsingStreamX()
{
	DataSet(nullptr, 0);
}

BF::ParsingStreamX::ParsingStreamX(void* data, const size_t dataSize)
{
	DataSet(data, dataSize);
}

BF::ParsingStreamX::ParsingStreamX(const void* data, const size_t dataSize)
{
	DataSet((void*)data, dataSize);
}

size_t BF::ParsingStreamX::ReadPossibleSize()
{
	return ParsingStreamRemainingSize(this);
}

bool BF::ParsingStreamX::IsAtEnd()
{
	return ParsingStreamIsAtEnd(this);
}

void BF::ParsingStreamX::DataSet(void* data, const size_t dataSize, const size_t cursorPosition)
{
	ParsingStreamConstruct(this, data, dataSize);
}

void BF::ParsingStreamX::CursorToBeginning()
{
	ParsingStreamCursorToBeginning(this);
}

Byte__* BF::ParsingStreamX::CursorCurrentAdress()
{
	return ParsingStreamCursorPosition(this);
}

void BF::ParsingStreamX::CursorAdvance(const size_t steps)
{
	ParsingStreamCursorAdvance(this, steps);
}

void BF::ParsingStreamX::CursorRewind(const size_t steps)
{
	ParsingStreamCursorRewind(this, steps);
}

void BF::ParsingStreamX::CursorToEnd()
{
	ParsingStreamCursorToEnd(this);
}

unsigned int BF::ParsingStreamX::ReadNextLineInto(char* exportBuffer)
{
	return ParsingStreamReadNextLineInto(this, exportBuffer, -1);
}

void BF::ParsingStreamX::SkipEndOfLineCharacters()
{
	ParsingStreamSkipEndOfLineCharacters(this);
}

void BF::ParsingStreamX::SkipEmpty()
{
	ParsingStreamSkipEmptySpace(this);
}

void BF::ParsingStreamX::SkipBlock()
{
	ParsingStreamSkipBlock(this);
}

size_t BF::ParsingStreamX::SkipLine()
{
	return ParsingStreamSkipLine(this);
}

void BF::ParsingStreamX::Read(bool& value)
{
	unsigned char byte = 0;

	ParsingStreamReadCU(this, &byte);

	value = byte;
}

void BF::ParsingStreamX::Read(char& value)
{
	ParsingStreamReadC(this, &value);
}

void BF::ParsingStreamX::Read(unsigned char& value)
{
	ParsingStreamReadCU(this, &value);
}

void BF::ParsingStreamX::Read(short& value, const Endian endian)
{
	ParsingStreamReadS(this, &value, endian);
}

void BF::ParsingStreamX::Read(unsigned short& value, const Endian endian)
{
	ParsingStreamReadSU(this, &value, endian);
}

void BF::ParsingStreamX::Read(int& value, const Endian endian)
{
	ParsingStreamReadI(this, &value, endian);
}

void BF::ParsingStreamX::Read(unsigned int& value, const Endian endian)
{
	ParsingStreamReadIU(this, &value, endian);
}

void BF::ParsingStreamX::Read(unsigned long long& value, const Endian endian)
{
	ParsingStreamReadLLU(this, &value, endian);
}

void BF::ParsingStreamX::Read(void* value, const size_t length)
{
	ParsingStreamReadD(this, value, length);
}

void BF::ParsingStreamX::ReadUntil(char* value, const size_t length, const char character)
{
	ParsingStreamReadUntil(this, value, length, character);
}

void BF::ParsingStreamX::ReadUntil(wchar_t* value, const size_t length, const wchar_t character)
{	
	ParsingStreamReadUntil(this, value, length, character);
}

size_t BF::ParsingStreamX::ReadSafe(Byte__* value, const size_t length)
{
	const size_t possibleReadSize = ReadPossibleSize();
	const bool canFullfill = possibleReadSize >= length;
	const size_t readBytes = canFullfill ? length : possibleReadSize;

	Read(value, readBytes);

	return readBytes;
}

bool BF::ParsingStreamX::ReadAndCompare(const Byte__* value, const size_t length)
{
	return ReadAndCompare((void*)value, length);
}

bool BF::ParsingStreamX::ReadAndCompare(const char* value, const size_t length)
{
	return ReadAndCompare((void*)value, length);
}

bool BF::ParsingStreamX::ReadAndCompare(const char value)
{
	return ReadAndCompare(&value, sizeof(char));
}

bool BF::ParsingStreamX::ReadAndCompare(const void* value, const size_t length)
{
	return ParsingStreamReadAndCompare(this, value, length);
}

bool BF::ParsingStreamX::ReadAndCompare(const unsigned int value)
{
	return ParsingStreamReadAndCompare(this, &value, sizeof(unsigned int));
}

void BF::ParsingStreamX::Write(const bool value)
{
	const unsigned char valueChar = value;

	Write(valueChar);
}

void BF::ParsingStreamX::Write(const char value)
{
	ParsingStreamWriteC(this, value);
}

void BF::ParsingStreamX::Write(const unsigned char value)
{
	ParsingStreamWriteC(this, value);
}

void BF::ParsingStreamX::Write(const short value, const Endian endian)
{
	ParsingStreamWriteS(this, value, endian);
}

void BF::ParsingStreamX::Write(const unsigned short value, const Endian endian)
{
	ParsingStreamWriteSU(this, value, endian);
}

void BF::ParsingStreamX::Write(const int value, const Endian endian)
{
	ParsingStreamWriteSU(this, value, endian);
}

void BF::ParsingStreamX::Write(unsigned int value, const Endian endian)
{
	ParsingStreamWriteSU(this, value, endian);
}

void BF::ParsingStreamX::Write(const long long value, const Endian endian)
{
	ParsingStreamWriteSU(this, value, endian);
}

void BF::ParsingStreamX::Write(const unsigned long long value, const Endian endian)
{
	ParsingStreamWriteSU(this, value, endian);
}

void BF::ParsingStreamX::Write(const char* value, const size_t length)
{
	ParsingStreamWriteD(this, (void*)value, length);
}

void BF::ParsingStreamX::Write(const unsigned char* value, const size_t length)
{
	ParsingStreamWriteD(this, (void*)value, length);
}

void BF::ParsingStreamX::Write(const void* value, const size_t length)
{
	ParsingStreamWriteD(this, (void*)value, length);
}

size_t BF::ParsingStreamX::Write(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	size_t readBytes = ParsingStreamWrite(this, format, args);

	va_end(args);
	
	return readBytes;
}