#include "TTFSerifStyle.h"

BF::TTFSerifStyle BF::ConvertTTFSerifStyle(unsigned char serifStyle)
{
	switch (serifStyle)
	{
		case 0: return BF::TTFSerifStyle::Any;
		case 1:	return BF::TTFSerifStyle::NoFit;
		case 2:	return BF::TTFSerifStyle::Cove;
		case 3:	return BF::TTFSerifStyle::ObtuseCove;
		case 4:	return BF::TTFSerifStyle::SquareCove;
		case 5:	return BF::TTFSerifStyle::ObtuseSquareCove;
		case 6:	return BF::TTFSerifStyle::Square;
		case 7:	return BF::TTFSerifStyle::Thin;
		case 8:	return BF::TTFSerifStyle::Bone;
		case 9:	return BF::TTFSerifStyle::Exaggerated;
		case 10: return BF::TTFSerifStyle::Triangle;
		case 11: return BF::TTFSerifStyle::NormalSans;
		case 12: return BF::TTFSerifStyle::ObtuseSans;
		case 13: return BF::TTFSerifStyle::PerpSans;
		case 14: return BF::TTFSerifStyle::Flared;
		case 15: return BF::TTFSerifStyle::Rounded;

		default:
			return BF::TTFSerifStyle::Invalid;
	}
}
