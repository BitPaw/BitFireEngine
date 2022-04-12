#include "RIFF.h"

BF::RIFF::RIFF()
{
	ChunkID.A = '?';
	ChunkID.B = '?';
	ChunkID.C = '?';
	ChunkID.D = '?';
	ChunkSize = 0;
	Format[0] = '?';
	Format[1] = '?';
	Format[2] = '?';
	Format[3] = '?';
}