#include "FMT.h"

#include <File/ByteStream.h>

#define FMTSignature {'f', 'm', 't', ' '}

BF::FMT::FMT()
{
	ChunkSize = 0;
	AudioFormat = 0;
	NumerOfChannels = 0;
	SampleRate = 0;
	ByteRate = 0;
	BlockAllign = 0;
	BitsPerSample = 0;
}

size_t BF::FMT::Parse(const unsigned char* data, const size_t dataSize, const Endian endian)
{
	ByteStream dataStream(data, dataSize);

	// Check header signature
	{
		const Byte__ expectedValue[] = FMTSignature;

		ClusterInt fmtHeader;

		dataStream.Read(fmtHeader.Data, 4u);
	
		const bool valid = 
			expectedValue[0] == fmtHeader.A &&
			expectedValue[1] == fmtHeader.B &&
			expectedValue[2] == fmtHeader.C &&
			expectedValue[3] == fmtHeader.D;

		if(!valid)
		{
			return 0;
		}
	}

	dataStream.Read(ChunkSize, endian);
	dataStream.Read(AudioFormat, endian);
	dataStream.Read(NumerOfChannels, endian);
	dataStream.Read(SampleRate, endian);
	dataStream.Read(ByteRate, endian);
	dataStream.Read(BlockAllign, endian);
	dataStream.Read(BitsPerSample, endian);

	return dataStream.DataCursor;
}