#include "RIFF.h"

BF::RIFF::RIFF()
{
	ChunkID[0] = '?';
	ChunkID[1] = '?';
	ChunkID[2] = '?';
	ChunkID[3] = '?';
	ChunkSize = 0;
	Format[0] = '?';
	Format[1] = '?';
	Format[2] = '?';
	Format[3] = '?';
}