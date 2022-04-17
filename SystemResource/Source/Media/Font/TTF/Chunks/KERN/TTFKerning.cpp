#include "TTFKerning.h"

BF::TTFKerning::TTFKerning()
{
	Version = 0;
	NumberOfSubtables = 0;
	KerningSubtableList = nullptr;
}

BF::TTFKerning::~TTFKerning()
{
	delete[] KerningSubtableList;
}
