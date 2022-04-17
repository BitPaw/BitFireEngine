#include "TTFSubtableFormat0.h"

BF::TTFSubtableFormat0::TTFSubtableFormat0()
{
	NumberOfPairs = 0;
	SearchRange = 0;
	EntrySelector = 0;
	RangeShift = 0;

	KerningPairList = nullptr;
}

BF::TTFSubtableFormat0::~TTFSubtableFormat0()
{
	delete[] KerningPairList;
}
