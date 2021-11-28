#include "TTFLetterform.h"

BF::TTFLetterform BF::ConvertTTFLetterform(unsigned char letterform)
{
	switch (letterform)
	{
		case 0: return BF::TTFLetterform::Any;
		case 1: return BF::TTFLetterform::NoFit;
		case 2: return BF::TTFLetterform::NormalContact;
		case 3: return BF::TTFLetterform::NormalWeighted;
		case 4: return BF::TTFLetterform::NormalBoxed;
		case 5: return BF::TTFLetterform::NormalFlattened;
		case 6: return BF::TTFLetterform::NormalRounded;
		case 7: return BF::TTFLetterform::NormalOffCenter;
		case 8: return BF::TTFLetterform::NormalSquare;
		case 9: return BF::TTFLetterform::ObliqueContact;
		case 10: return BF::TTFLetterform::ObliqueWeighted;
		case 11: return BF::TTFLetterform::ObliqueBoxed;
		case 12: return BF::TTFLetterform::ObliqueFlattened;
		case 13: return BF::TTFLetterform::ObliqueRounded;
		case 14: return BF::TTFLetterform::ObliqueOffCenter;
		case 15: return BF::TTFLetterform::ObliqueSquare;

		default:
			return BF::TTFLetterform::Invalid;
	}
}