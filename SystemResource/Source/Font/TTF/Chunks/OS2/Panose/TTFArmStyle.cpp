#include "TTFArmStyle.h"

BF::TTFArmStyle BF::ConvertTTFArmStyle(unsigned char armStyle)
{
	switch (armStyle)
	{
		case 0: return BF::TTFArmStyle::Any;
		case 1: return BF::TTFArmStyle::NoFit;
		case 2: return BF::TTFArmStyle::StraightArmsHorizontal;
		case 3: return BF::TTFArmStyle::StraightArmsWedge;
		case 4: return BF::TTFArmStyle::StraightArmsVertical;
		case 5: return BF::TTFArmStyle::StraightArmsSingleSerif;
		case 6: return BF::TTFArmStyle::StraightArmsDoubleSerif;
		case 7: return BF::TTFArmStyle::NonStraightArmsHorizontal;
		case 8: return BF::TTFArmStyle::NonStraightArmsWedge;
		case 9: return BF::TTFArmStyle::NonStraightArmsVertical;
		case 10: return BF::TTFArmStyle::NonStraightArmsSingleSerif;
		case 11: return BF::TTFArmStyle::NonStraightArmsDoubleSerif;

		default:
			return BF::TTFArmStyle::Invalid;
	}
}