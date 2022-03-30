#include "PNGChunk.h"

void BF::PNGChunk::Check()
{
	// Ancillary bit : bit 5 of first byte
	// 0 (uppercase) = critical, 1 (lowercase) = ancillary.
	IsEssential = !((ChunkTypeRaw.Data[0] & 0b00100000) >> 5);

	// Private bit: bit 5 of second byte
	// Must be 0 (uppercase)in files conforming to this version of PNG.
	IsRegisteredStandard = !((ChunkTypeRaw.Data[1] & 0b00100000) >> 5);

	// Safe-to-copy bit: bit 5 of fourth byte
	// 0 (uppercase) = unsafe to copy, 1 (lowercase) = safe to copy.
	IsSafeToCopy = !((ChunkTypeRaw.Data[3] & 0b00100000) >> 5);

	ChunkType = ConvertChunkType(ChunkTypeRaw);
}

BF::PNGChunk::PNGChunk()
{
	IsEssential = false;
	IsRegisteredStandard = false;
	IsSafeToCopy = false;	
	Lengh = 0;
	ChunkTypeRaw.A = '#';
	ChunkTypeRaw.B = '#';
	ChunkTypeRaw.C = '#';
	ChunkTypeRaw.D = '#';
	ChunkType = PNGChunkType::Invalid;
	ChunkData = nullptr;
	CRCOK = false;
	CRC = 0;
}