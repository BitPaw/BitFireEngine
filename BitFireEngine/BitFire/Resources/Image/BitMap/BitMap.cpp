#include "BitMap.h"

BitMap::BitMap()
{
	Header = BitMapFileHeader();
	InformationHeaderType = BitMapInformationHeaderType::UnkownOrInvalid;
	InformationHeader = nullptr;
}

BitMap::~BitMap()
{
	if (InformationHeader != nullptr)
	{
		//delete InformationHeader;
	}
}