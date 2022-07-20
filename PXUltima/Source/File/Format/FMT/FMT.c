#include "FMT.h"

#include <File/ParsingStream.h>
#include <Memory/Memory.h>
#include <Container/ClusterInt.h>

#define FMTSignature {'f', 'm', 't', ' '}

ActionResult FMTParse(FMT* fmt, const void* data, const size_t dataSize, size_t* dataRead, const Endian endian)
{
	ParsingStream parsingStream;

	MemorySet(fmt, sizeof(FMT), 0);
	*dataRead = 0;

	ParsingStreamConstruct(&parsingStream, data, dataSize);

	// Check header signature
	{
		const unsigned char expectedValue[] = FMTSignature;

		ClusterInt fmtHeader;

		ParsingStreamReadD(&parsingStream, fmtHeader.Data, 4u);

		const unsigned char valid =
			expectedValue[0] == fmtHeader.A &&
			expectedValue[1] == fmtHeader.B &&
			expectedValue[2] == fmtHeader.C &&
			expectedValue[3] == fmtHeader.D;

		if(!valid)
		{
			return ResultInvalidHeaderSignature;
		}
	}

	ParsingStreamReadD(&parsingStream, &fmt->ChunkSize, endian);
	ParsingStreamReadD(&parsingStream, &fmt->AudioFormat, endian);
	ParsingStreamReadD(&parsingStream, &fmt->NumerOfChannels, endian);
	ParsingStreamReadD(&parsingStream, &fmt->SampleRate, endian);
	ParsingStreamReadD(&parsingStream, &fmt->ByteRate, endian);
	ParsingStreamReadD(&parsingStream, &fmt->BlockAllign, endian);
	ParsingStreamReadD(&parsingStream, &fmt->BitsPerSample, endian);

	*dataRead = parsingStream.DataCursor;

	return ResultSuccessful;
}
