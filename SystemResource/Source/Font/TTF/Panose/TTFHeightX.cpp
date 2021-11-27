#include "TTFHeightX.h"

BF::TTFHeightX BF::ConvertTTFHeightX(unsigned char heightX)
{
	switch (heightX)
	{
		case 0: return BF::TTFHeightX::Any;
		case 1: return BF::TTFHeightX::NoFit;
		case 2: return BF::TTFHeightX::ConstantSmall;
		case 3: return BF::TTFHeightX::ConstantStandard;
		case 4: return BF::TTFHeightX::ConstantLarge;
		case 5: return BF::TTFHeightX::DuckingSmall;
		case 6: return BF::TTFHeightX::DuckingStandard;
		case 7: return BF::TTFHeightX::DuckingLarge;

		default:
			return BF::TTFHeightX::Invalid;
	}
}