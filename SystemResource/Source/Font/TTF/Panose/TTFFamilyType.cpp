#include "TTFFamilyType.h"

BF::TTFFamilyType BF::ConvertTTFFamilyType(unsigned char familyType)
{
	switch (familyType)
	{
		case 0: return BF::TTFFamilyType::Any;
		case 1:	return BF::TTFFamilyType::NoFit;
		case 2: return BF::TTFFamilyType::TextAndDisplay;
		case 3: return BF::TTFFamilyType::Script;
		case 4: return BF::TTFFamilyType::Decorative;
		case 5: return BF::TTFFamilyType::Pictorial;

		default:
			return BF::TTFFamilyType::Invalid;
	}
}