#include "TTFMidline.h"

BF::TTFMidline BF::ConvertTTFMidline(unsigned char midline)
{
	switch (midline)
	{
		case 0:	return BF::TTFMidline::Any;
		case 1: return BF::TTFMidline::NoFit;
		case 2: return BF::TTFMidline::StandardTrimmed;
		case 3: return BF::TTFMidline::StandardPointed;
		case 4: return BF::TTFMidline::StandardSerifed;
		case 5: return BF::TTFMidline::HighTrimmed;
		case 6: return BF::TTFMidline::HighPointed;
		case 7: return BF::TTFMidline::HighSerifed;
		case 8: return BF::TTFMidline::ConstantTrimmed;
		case 9: return BF::TTFMidline::ConstantPointed;
		case 10: return BF::TTFMidline::ConstantSerifed;
		case 11: return BF::TTFMidline::LowTrimmed;
		case 12: return BF::TTFMidline::LowPointed;
		case 13: return BF::TTFMidline::LowSerifed;

		default:
			return BF::TTFMidline::Invalid;
	}
}