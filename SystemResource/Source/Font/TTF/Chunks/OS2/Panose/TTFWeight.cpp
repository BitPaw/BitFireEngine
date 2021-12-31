#include "TTFWeight.h"

BF::TTFWeight BF::ConvertTTFWeight(unsigned char weight)
{
	switch (weight)
	{
		case 0:
			return BF::TTFWeight::Any;

		case 1:	
			return BF::TTFWeight::NoFit;

		case 2:
			return BF::TTFWeight::VeryLight;

		case 3:
			return BF::TTFWeight::Light;

		case 4:
			return BF::TTFWeight::Thin;

		case 5:
			return BF::TTFWeight::Book;

		case 6:
			return BF::TTFWeight::Medium;

		case 7:
			return BF::TTFWeight::Demi;

		case 8:
			return BF::TTFWeight::Bold;

		case 9:
			return BF::TTFWeight::Heavy;

		case 10:
			return BF::TTFWeight::Black;

		case 11:
			return BF::TTFWeight::Nord;

		default:
			return BF::TTFWeight::Invalid;
	}
}