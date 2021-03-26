#include "PNGChunkTypeBlock.h"

bool BF::PNGChunkTypeBlock::IsEssential()
{
	unsigned char byte = Value.ByteData[0];
	bool IsAncillary = byte >= 'A' && byte <= 'Z';

	return IsAncillary;
}

bool BF::PNGChunkTypeBlock::IsRegisteredStandard()
{
	unsigned char byte = Value.ByteData[2];
	bool IsRegistered = byte >= 'A' && byte <= 'Z';

	return IsRegistered;
}

bool BF::PNGChunkTypeBlock::IsSafeToCopy()
{
	unsigned char byte = Value.ByteData[3];
	bool IsSaveToCopy = byte >= 'a' && byte <= 'z';

	return IsSaveToCopy;
}
