#ifndef ParsingStreamInclude
#define ParsingStreamInclude

#include <stddef.h>

#include "Endian.h"

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct ParsingStream_
	{
		unsigned char* Data;
		size_t DataSize;
		size_t DataCursor;
	}
	ParsingStream;


	extern void ParsingStreamConstruct(ParsingStream* parsingStream, void* data, const size_t dataSize);
	//extern void ParsingStreamAllocate(ParsingStream* parsingStream, const size_t dataSize);
	extern void ParsingStreamClear(ParsingStream* parsingStream);

	extern size_t ParsingStreamRemainingSize(ParsingStream* parsingStream);
	extern unsigned char ParsingStreamIsAtEnd(ParsingStream* parsingStream);

	extern unsigned char* ParsingStreamCursorPosition(ParsingStream* parsingStream);
	extern void ParsingStreamCursorToBeginning(ParsingStream* parsingStream);
	extern void ParsingStreamCursorAdvance(ParsingStream* parsingStream, const size_t steps);
	extern void ParsingStreamCursorRewind(ParsingStream* parsingStream, const size_t steps);
	extern void ParsingStreamCursorToEnd(ParsingStream* parsingStream);



	extern size_t ParsingStreamReadNextLineInto(ParsingStream* parsingStream, void* exportBuffer, const size_t exportBufferSize);


	extern size_t ParsingStreamSkipEndOfLineCharacters(ParsingStream* parsingStream);
	extern size_t ParsingStreamSkipEmptySpace(ParsingStream* parsingStream);

	// Skips current block thats seperated with spaces.
	// Example : '|' is the cursor.
	// Before : |AAAA  BBBB CCC
	// After :  AAAA |BBBB CCC
	extern size_t ParsingStreamSkipBlock(ParsingStream* parsingStream);
	extern size_t ParsingStreamSkipLine(ParsingStream* parsingStream);


	extern size_t ParsingStreamReadC(ParsingStream* parsingStream, char* value);
	extern size_t ParsingStreamReadCU(ParsingStream* parsingStream, unsigned char* value);
	extern size_t ParsingStreamReadS(ParsingStream* parsingStream, short* value, const Endian endian);
	extern size_t ParsingStreamReadSU(ParsingStream* parsingStream, unsigned short* value, const Endian endian);
	extern size_t ParsingStreamReadI(ParsingStream* parsingStream, int* value, const  Endian endian);
	extern size_t ParsingStreamReadIU(ParsingStream* parsingStream, unsigned int* value, const Endian endian);
	extern size_t ParsingStreamReadLL(ParsingStream* parsingStream, long long* value, const Endian endian);
	extern size_t ParsingStreamReadULL(ParsingStream* parsingStream, unsigned long long* value, const  Endian endian);
	extern size_t ParsingStreamReadD(ParsingStream* parsingStream, void* value, const size_t length);
	extern void ParsingStreamReadUntil(ParsingStream* parsingStream, void* value, const size_t length, const char character);

	// Additional check how many bytes are read.
	// Slower version of Read(), this function can't fail.
	//size_t ReadSafe(Byte__* value, const size_t length);


	unsigned char ParsingStreamReadAndCompare(ParsingStream* parsingStream, const void* value, const size_t length);
	//unsigned char ParsingStreamReadAndCompareC(ParsingStream* parsingStream, const char value);
	//unsigned char ParsingStreamReadAndCompareIU(ParsingStream* parsingStream, const unsigned int value);

	extern size_t ParsingStreamWriteC(ParsingStream* parsingStream, const char value);
	extern size_t ParsingStreamWriteCU(ParsingStream* parsingStream, const unsigned char value);
	extern size_t ParsingStreamWriteS(ParsingStream* parsingStream, const short value, const Endian endian);
	extern size_t ParsingStreamWriteSU(ParsingStream* parsingStream, const unsigned short value, const Endian endian);
	extern size_t ParsingStreamWriteI(ParsingStream* parsingStream, const int value, const Endian endian);
	extern size_t ParsingStreamWriteIU(ParsingStream* parsingStream, const unsigned int value, const Endian endian);
	extern size_t ParsingStreamWriteLL(ParsingStream* parsingStream, const long long value, const Endian endian);
	extern size_t ParsingStreamWriteLU(ParsingStream* parsingStream, const unsigned long long value, const Endian endian);
	extern size_t ParsingStreamWriteD(ParsingStream* parsingStream, const void* value, const size_t length);
	extern size_t ParsingStreamWrite(ParsingStream* parsingStream, const char* format, ...);

#endif

#ifdef __cplusplus
}
#endif