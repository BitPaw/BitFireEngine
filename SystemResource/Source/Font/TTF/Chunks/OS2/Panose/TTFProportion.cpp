#include "TTFProportion.h"

BF::TTFProportion BF::ConvertTTFProportion(unsigned char proportion)
{
	switch (proportion)
	{
		case 0: return BF::TTFProportion::Any;
		case 1: return BF::TTFProportion::NoFit;
		case 2: return BF::TTFProportion::OldStyle;
		case 3: return BF::TTFProportion::Modern;
		case 4: return BF::TTFProportion::EvenWidth;
		case 5: return BF::TTFProportion::Expanded;
		case 6: return BF::TTFProportion::Condensed;
		case 7: return BF::TTFProportion::VeryExpanded;
		case 8: return BF::TTFProportion::VeryCondensed;
		case 9: return BF::TTFProportion::Monospaced;

		default:
			return BF::TTFProportion::Invalid;
	}
}