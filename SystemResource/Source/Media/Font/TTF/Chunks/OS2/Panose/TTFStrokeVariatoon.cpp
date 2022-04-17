#include "TTFStrokeVariatoon.h"

BF::TTFStrokeVariatoon BF::ConvertTTFStrokeVariatoon(unsigned char strokeVariatoon)
{
	switch (strokeVariatoon)
	{
		case 0: 
			return BF::TTFStrokeVariatoon::Any;

		case 1: 
			return BF::TTFStrokeVariatoon::NoFit;

		case 2: 
			return BF::TTFStrokeVariatoon::GradualDiagonal;

		case 3: 
			return BF::TTFStrokeVariatoon::GradualTransitional;

		case 4: 
			return BF::TTFStrokeVariatoon::GradualVertical;

		case 5: 
			return BF::TTFStrokeVariatoon::GradualHorizontal;

		case 6: 
			return BF::TTFStrokeVariatoon::RapidVertical;

		case 7: 
			return BF::TTFStrokeVariatoon::RapidHorizontal;

		case 8: 
			return BF::TTFStrokeVariatoon::InstantVertical;

		default:
			return TTFStrokeVariatoon::Invalid;
	}
}