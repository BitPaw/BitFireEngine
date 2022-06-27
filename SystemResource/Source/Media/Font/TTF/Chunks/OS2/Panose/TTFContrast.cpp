#include "TTFContrast.h"

BF::TTFContrast BF::ConvertTTFContrast(unsigned char contrast)
{
	switch (contrast)
	{
		case 0: return BF::TTFContrast::Any;
		case 1: return BF::TTFContrast::NoFit;
		case 2: return BF::TTFContrast::NoneContrast;
		case 3:	return BF::TTFContrast::VeryLow;
		case 4:	return BF::TTFContrast::Low;
		case 5:	return BF::TTFContrast::MediumLow;
		case 6: return BF::TTFContrast::Medium;
		case 7: return BF::TTFContrast::MediumHigh;
		case 8: return BF::TTFContrast::High;
		case 9:	return BF::TTFContrast::VeryHigh;

		default:
			return BF::TTFContrast::Invalid;
	}
}
