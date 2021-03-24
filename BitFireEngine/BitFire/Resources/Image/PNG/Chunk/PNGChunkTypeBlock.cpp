#include "PNGChunkTypeBlock.h"

bool BF::PNGChunkTypeBlock::IsEssential()
{
	unsigned char byte = Value.ByteA;
	bool IsAncillary = byte >= 'A' && byte <= 'Z';

	return IsAncillary;
}

bool BF::PNGChunkTypeBlock::IsRegisteredStandard()
{
	unsigned char byte = Value.ByteB;
	bool IsRegistered = byte >= 'A' && byte <= 'Z';

	return IsRegistered;
}

bool BF::PNGChunkTypeBlock::IsSafeToCopy()
{
	unsigned char byte = Value.ByteA;
	bool IsSaveToCopy = byte >= 'a' && byte <= 'z';

	return IsSaveToCopy;
}
