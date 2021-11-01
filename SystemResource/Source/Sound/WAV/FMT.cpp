#include "FMT.h"

BF::FMT::FMT()
{
	ChunkID[0] = '?';
	ChunkID[1] = '?';
	ChunkID[2] = '?';
	ChunkID[3] = '?';
	ChunkSize = 0;
	AudioFormat = 0;
	NumerOfChannels = 0;
	SampleRate = 0;
	ByteRate = 0;
	BlockAllign = 0;
	BitsPerSample = 0;
}