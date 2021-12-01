#include "EncodingRecord.h"

BF::EncodingRecord::EncodingRecord()
{
	Platform = PlatformID::Invalid;
	Encoding = EncodingID::Invalid;
	SubtableOffset = 0;
}
