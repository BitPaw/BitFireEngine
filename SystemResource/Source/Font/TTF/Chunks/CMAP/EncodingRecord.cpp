#include "EncodingRecord.h"

BF::TTF::CMAP::EncodingRecord::EncodingRecord()
{
	Platform = PlatformID::Invalid;
	Encoding = EncodingID::Invalid;
	SubtableOffset = 0;
}
