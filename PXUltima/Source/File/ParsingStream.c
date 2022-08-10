#include "ParsingStream.h"

#include <Memory/Memory.h>
#include <Math/Math.h>
#include <Text/Text.h>

#include <iso646.h>
#include <stdarg.h>
#include <stdio.h>

#define IsEndOfString(c) (c == '\0')
#define IsEmptySpace(c) (c == ' ')
#define IsEndOfLineCharacter(c) (c == '\r' || c == '\n')

void ParsingStreamConstruct(ParsingStream* parsingStream, void* data, const size_t dataSize)
{
	parsingStream->Data = data;
	parsingStream->DataSize = dataSize;
	parsingStream->DataCursor = 0;
}

void ParsingStreamClear(ParsingStream* parsingStream)
{
	parsingStream->Data = 0;
	parsingStream->DataSize = 0;
	parsingStream->DataCursor = 0;
}

size_t ParsingStreamRemainingSize(ParsingStream* parsingStream)
{
	return parsingStream->DataSize - parsingStream->DataCursor;
}

unsigned char ParsingStreamIsAtEnd(ParsingStream* parsingStream)
{
	return parsingStream->DataCursor == parsingStream->DataSize;
}

unsigned char* ParsingStreamCursorPosition(ParsingStream* parsingStream)
{
	return parsingStream->Data + parsingStream->DataCursor;
}

void ParsingStreamCursorToBeginning(ParsingStream* parsingStream)
{
	parsingStream->DataCursor = 0;
}

void ParsingStreamCursorAdvance(ParsingStream* parsingStream, const size_t steps)
{
	parsingStream->DataCursor += steps; // Check overflow
}

void ParsingStreamCursorRewind(ParsingStream* parsingStream, const size_t steps)
{
	parsingStream->DataCursor -= steps; // Check underflow
}

void ParsingStreamCursorToEnd(ParsingStream* parsingStream)
{
	parsingStream->DataCursor = parsingStream->DataSize;
}

size_t ParsingStreamReadNextLineInto(ParsingStream* parsingStream, void* exportBuffer, const size_t exportBufferSize)
{
	ParsingStreamSkipEndOfLineCharacters(parsingStream);

	const size_t dataPositionBefore = parsingStream->DataCursor;
	
	while(!ParsingStreamIsAtEnd(parsingStream))
	{
		const unsigned char* data = ParsingStreamCursorPosition(parsingStream);
		const unsigned char advance = !IsEndOfLineCharacter(*data) and !IsEndOfString(*data);

		if(!advance)
		{
			break;
		}

		ParsingStreamCursorAdvance(parsingStream, 1u);
	}

	const unsigned char* dataPoint = parsingStream->Data + dataPositionBefore;
	const size_t dataPositionAfter = parsingStream->DataCursor;
	const size_t length = dataPositionAfter - dataPositionBefore;

	if(length == 0)
	{
		return 0;
	}

	TextCopyA(dataPoint, length, exportBuffer, length);

	ParsingStreamSkipEndOfLineCharacters(parsingStream);

	return length;
}

size_t ParsingStreamSkipEndOfLineCharacters(ParsingStream* parsingStream)
{
	while(!ParsingStreamIsAtEnd(parsingStream))
	{
		const unsigned char* data = ParsingStreamCursorPosition(parsingStream);
		const unsigned char advance = IsEndOfLineCharacter(*data) and !IsEndOfString(*data);

		if(!advance)
		{
			break;
		}

		ParsingStreamCursorAdvance(parsingStream, 1u);
	}
}

size_t ParsingStreamSkipEmptySpace(ParsingStream* parsingStream)
{
	while(!ParsingStreamIsAtEnd(parsingStream))
	{
		const unsigned char* data = ParsingStreamCursorPosition(parsingStream);
		const unsigned char advance = IsEmptySpace(*data);

		if(!advance)
		{
			break;
		}

		ParsingStreamCursorAdvance(parsingStream, 1u);
	}
}

size_t ParsingStreamSkipBlock(ParsingStream* parsingStream)
{
	while(!ParsingStreamIsAtEnd(parsingStream))
	{
		const unsigned char* data = ParsingStreamCursorPosition(parsingStream);
		const unsigned char advance = !IsEndOfString(*data) and !IsEmptySpace(*data);

		if(!advance)
		{
			break;
		}

		ParsingStreamCursorAdvance(parsingStream, 1u);
	}

	ParsingStreamSkipEmptySpace(parsingStream);
}

size_t ParsingStreamSkipLine(ParsingStream* parsingStream)
{
	const size_t positionBefore = parsingStream->DataCursor;

	while(!ParsingStreamIsAtEnd(parsingStream))
	{
		const unsigned char* data = ParsingStreamCursorPosition(parsingStream);
		const unsigned char advance = !IsEndOfLineCharacter(*data) and !IsEndOfString(*data);

		if(!advance)
		{
			break;
		}

		ParsingStreamCursorAdvance(parsingStream, 1u);
	}

	ParsingStreamSkipEndOfLineCharacters(parsingStream);

	const size_t skippedBytes = parsingStream->DataCursor - positionBefore;

	return skippedBytes;
}

size_t ParsingStreamReadC(ParsingStream* parsingStream, char* value)
{
	return ParsingStreamReadCU(parsingStream, (unsigned char*)value);
}

size_t ParsingStreamReadCU(ParsingStream* parsingStream, unsigned char* value)
{
	const size_t sizeOfChar = sizeof(char);
	const unsigned char* data = ParsingStreamCursorPosition(parsingStream);
	const unsigned char character = *data;

	*value = character;

	ParsingStreamCursorAdvance(parsingStream, sizeOfChar);

	return sizeOfChar;
}

size_t ParsingStreamReadS(ParsingStream* parsingStream, short* value, const Endian endian)
{
	return ParsingStreamReadSU(parsingStream, (unsigned short*)value, endian);
}

size_t ParsingStreamReadSU(ParsingStream* parsingStream, unsigned short* value, const Endian endian)
{
	const size_t dataSize = sizeof(unsigned short);
	const unsigned char* data = ParsingStreamCursorPosition(parsingStream);
	const unsigned short* dataValue = (unsigned short*)data;

	*value = *dataValue;

	EndianSwap(value, dataSize, endian, EndianCurrentSystem);

	ParsingStreamCursorAdvance(parsingStream, dataSize);

	return dataSize;
}

size_t ParsingStreamReadI(ParsingStream* parsingStream, int* value, const Endian endian)
{
	return ParsingStreamReadIU(parsingStream, (unsigned int*)value, endian);
}

size_t ParsingStreamReadIU(ParsingStream* parsingStream, unsigned int* value, const Endian endian)
{
	const size_t dataSize = sizeof(unsigned int);
	const unsigned char* data = ParsingStreamCursorPosition(parsingStream);
	const unsigned int* dataValue = (unsigned int*)data;

	*value = *dataValue;

	EndianSwap(value, dataSize, endian, EndianCurrentSystem);

	ParsingStreamCursorAdvance(parsingStream, dataSize);

	return dataSize;
}

size_t ParsingStreamReadLL(ParsingStream* parsingStream, long long* value, const Endian endian)
{
	return ParsingStreamReadLLU(parsingStream, (unsigned long long*)value, endian);
}

size_t ParsingStreamReadLLU(ParsingStream* parsingStream, unsigned long long* value, const Endian endian)
{
	const size_t dataSize = sizeof(unsigned long long);
	const unsigned char* data = ParsingStreamCursorPosition(parsingStream);
	const unsigned long long* dataValue = (unsigned long long*)data;

	*value = *dataValue;

	EndianSwap(value, dataSize, endian, EndianCurrentSystem);

	ParsingStreamCursorAdvance(parsingStream, dataSize);

	return dataSize;
}

size_t ParsingStreamReadD(ParsingStream* parsingStream, void* value, const size_t length)
{
	const unsigned char* currentPosition = ParsingStreamCursorPosition(parsingStream);
	const size_t readableSize = ParsingStreamRemainingSize(parsingStream);
	const size_t copyedBytes = MemoryCopy(currentPosition, readableSize, value, length);

	ParsingStreamCursorAdvance(parsingStream, copyedBytes);

	return copyedBytes;
}

size_t ParsingStreamRead(ParsingStream* parsingStream, const void* format, const size_t length, ...)
{
	return 0;
}

void ParsingStreamReadUntil(ParsingStream* parsingStream, void* value, const size_t length, const char character)
{
	const unsigned char* currentPosition = ParsingStreamCursorPosition(parsingStream);

	size_t lengthCopy = 0;

	while(!ParsingStreamIsAtEnd(parsingStream))
	{
		const unsigned char* data = ParsingStreamCursorPosition(parsingStream);
		const unsigned char advance = *data != character && length <= lengthCopy;

		if(!advance)
		{
			break;
		}

		++lengthCopy;

		ParsingStreamCursorAdvance(parsingStream, 1u);
	}

	const size_t readableSize = ParsingStreamRemainingSize(parsingStream);

	MemoryCopy(currentPosition, readableSize, value, lengthCopy);
}

unsigned char ParsingStreamReadAndCompare(ParsingStream* parsingStream, const void* value, const size_t length)
{
	const unsigned char* currentPosition = ParsingStreamCursorPosition(parsingStream);
	const size_t readableSize = ParsingStreamRemainingSize(parsingStream);

	const unsigned char result = MemoryCompare(currentPosition, readableSize, value, length);

	if(result)
	{
		ParsingStreamCursorAdvance(parsingStream, length);
	}

	return result;
}

size_t ParsingStreamWriteC(ParsingStream* parsingStream, const char value)
{
	return ParsingStreamWriteCU(parsingStream, value);
}

size_t ParsingStreamWriteCU(ParsingStream* parsingStream, const unsigned char value)
{
	const size_t dataSize = sizeof(unsigned char);

	ParsingStreamWriteD(parsingStream, &value, dataSize);

	return dataSize;
}

size_t ParsingStreamWriteS(ParsingStream* parsingStream, const short value, const Endian endian)
{
	return ParsingStreamWriteSU(parsingStream, value, endian);
}

size_t ParsingStreamWriteSU(ParsingStream* parsingStream, const unsigned short value, const Endian endian)
{
	const size_t dataSize = sizeof(unsigned short);
	unsigned short dataValue = value;

	EndianSwap(&dataValue, dataSize, EndianCurrentSystem, endian);

	ParsingStreamWriteD(parsingStream, &dataValue, dataSize);

	return dataSize;
}

size_t ParsingStreamWriteI(ParsingStream* parsingStream, const int value, const Endian endian)
{
	return ParsingStreamWriteIU(parsingStream, value, endian);
}

size_t ParsingStreamWriteIU(ParsingStream* parsingStream, const unsigned int value, const Endian endian)
{
	const size_t dataSize = sizeof(unsigned int);
	unsigned int dataValue = value;

	EndianSwap(&dataValue, dataSize, EndianCurrentSystem, endian);

	ParsingStreamWriteD(parsingStream, &dataValue, dataSize);

	return dataSize;
}

size_t ParsingStreamWriteLL(ParsingStream* parsingStream, const long long value, const Endian endian)
{
	return ParsingStreamWriteLU(parsingStream, value, endian);
}

size_t ParsingStreamWriteLU(ParsingStream* parsingStream, const unsigned long long value, const Endian endian)
{
	const size_t dataSize = sizeof(unsigned long long);
	unsigned long long dataValue = value;

	EndianSwap(value, dataSize, EndianCurrentSystem, endian);

	ParsingStreamWriteD(parsingStream, &dataValue, dataSize);

	return dataSize;
}

size_t ParsingStreamWriteD(ParsingStream* parsingStream, const void* value, const size_t length)
{
	const size_t writableSize = ParsingStreamRemainingSize(parsingStream);
	unsigned char* currentPosition = ParsingStreamCursorPosition(parsingStream);

	const size_t copyedBytes = MemoryCopy(value, length, currentPosition, writableSize);
	
	ParsingStreamCursorAdvance(parsingStream, copyedBytes);

	return copyedBytes;
}

size_t ParsingStreamWriteFill(ParsingStream* parsingStream, const unsigned char value, const size_t length)
{
	const size_t writableSize = ParsingStreamRemainingSize(parsingStream);
	unsigned char* beforePosition = ParsingStreamCursorPosition(parsingStream);
	const size_t write = MathMinimumI(writableSize, length);

	for (size_t i = 0; i < write; ++i)
	{
		beforePosition[i] = value;
	}

	ParsingStreamCursorAdvance(parsingStream, write);

	return write;
}

size_t ParsingStreamWrite(ParsingStream* parsingStream, const char* format, ...)
{
	const unsigned char* currentPosition = ParsingStreamCursorPosition(parsingStream);

	va_list args;
	va_start(args, format);

	const size_t writableSize = ParsingStreamRemainingSize(parsingStream);
	const int writtenBytes = vsprintf_s(currentPosition, writableSize, format, args);

	va_end(args);

	{
		const unsigned char sucessful = writtenBytes >= 0;

		if(!sucessful)
		{
			return 0;
		}
	}

	ParsingStreamCursorAdvance(parsingStream, writtenBytes);

	return writtenBytes;
}