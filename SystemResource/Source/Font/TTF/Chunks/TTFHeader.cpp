#include "TTFHeader.h"

BF::TTFHeader::TTFHeader()
{
	CheckSumAdjustment = 0;
	MagicNumber = 0;
	Flags = 0;
	UnitsPerEM = 0;
	Created = 0;
	Modified = 0;
	Minimum[0] = 0;
	Minimum[1] = 0;
	Maximum[0] = 0;
	Maximum[1] = 0;
	MacStyle = 0;
	LowestRecPpem = 0;
	FontDirectionHint = 0;
	IndexToLocFormat = 0;
	GlyphDataFormat = 0;
}