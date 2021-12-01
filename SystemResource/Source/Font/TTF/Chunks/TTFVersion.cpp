#include "TTFVersion.h"

BF::TTFVersion::TTFVersion()
{
	Major = 0;
	Minor = 0;
	Type = TTFVersionType::Invalid;
}

void BF::TTFVersion::Check()
{
	Type = ConvertVersionType(Major, Minor);
}