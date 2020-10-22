#include "BMPFileHeader.h"

BF::BMPFileHeader::BMPFileHeader()
{
	SizeOfFile = -1;
	DataOffset = -1;
	ActualSizeOfFile = -1;
	Type = BMPType::UnkownOrInavlid;
}
