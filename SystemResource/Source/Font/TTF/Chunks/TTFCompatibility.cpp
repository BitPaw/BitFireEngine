#include "TTFCompatibility.h"

BF::TTFCompatibility::TTFCompatibility()
{
	Version = 0;
	xAvgCharWidth = 0;
	usWeightClass = 0;
	usWidthClass = 0;
	fsType = 0;
	ySubscriptXSize = 0;
	ySubscriptYSize = 0;
	ySubscriptXOffset = 0;
	ySubscriptYOffset = 0;
	ySuperscriptXSize = 0;
	ySuperscriptYSize = 0;
	ySuperscriptXOffset = 0;
	ySuperscriptYOffset = 0;
	yStrikeoutSize = 0;
	yStrikeoutPosition = 0;
	sFamilyClass = 0;
	//TTFPanose Panose;
	ulUnicodeRange[0] = 0;
	ulUnicodeRange[1] = 0;
	ulUnicodeRange[2] = 0;
	ulUnicodeRange[3] = 0;
	achVendID[0] = 0;
	achVendID[1] = 0;
	achVendID[2] = 0;
	achVendID[3] = 0;
	fsSelection = 0;
	fsFirstCharIndex = 0;
	fsLastCharIndex = 0;


	sTypoAscender = 0;
	sTypoDescender = 0;
	sTypoLineGap = 0;
	usWinAscent = 0;
	usWinDescent = 0;
	ulCodePageRange1 = 0;
	ulCodePageRange2 = 0;
	sxHeight = 0;
	sCapHeight = 0;
	usDefaultChar = 0;
	usBreakChar = 0;
	usMaxContext = 0;
	usLowerPointSize = 0;
	usUpperPointSize = 0;
}