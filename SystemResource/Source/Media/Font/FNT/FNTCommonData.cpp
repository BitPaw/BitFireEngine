#include "FNTCommonData.h"

BF::FNTCommonData::FNTCommonData()
{
	LineHeight = 95;
	Base = 71;
	ScaleWidth = 512;
	ScaleHeight = 512;
	AmountOfPages = 1;
	Packed = false;

	AlphaChanal = FNTChanalMode::InvalidMode;
	RedChanal = FNTChanalMode::InvalidMode;
	GreenChanal = FNTChanalMode::InvalidMode;
	BlueChanal = FNTChanalMode::InvalidMode;
}