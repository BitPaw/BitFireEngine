#include "RIFF.h"

BF::RIFF::RIFF()
{
	ChunkSize = 0;
}

BF::RIFF::RIFF(unsigned int chunkID, unsigned int chunkSize, unsigned int format)
{
	ChunkSize = chunkSize;
}