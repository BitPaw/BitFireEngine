#include "TTFKerningSubtable.h"

BF::TTFKerningSubtable::TTFKerningSubtable()
{
	Version = 0;
	Length = 0;
	Horizontal = 0;
	Minimum = 0;
	Cross = 0;
	Override = 0;
	Reserved = 0;
	Format = 0;
}

void BF::TTFKerningSubtable::ParseCoverageValue(unsigned short coverage)
{
	Horizontal = coverage & 0b0000000000000001;
	Minimum =   (coverage & 0b0000000000000010) >> 1;
	Cross =     (coverage & 0b0000000000000100) >> 2;
	Override =  (coverage & 0b0000000000001000) >> 3;
	Reserved =  (coverage & 0b0000000011110000) >> 4;
	Format =    (coverage & 0b1111111100000000) >> 8;
}