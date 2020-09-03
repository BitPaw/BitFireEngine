#pragma once

#include <string>
#include <vector>

#include "BitMapFontInfo.h"
#include "BitMapFontCommonData.h"
#include "BitMapFontPage.h"

class BitMapFont
{
public:
	BitMapFontInfo FontInfo;
	BitMapFontCommonData FontCommon;

	std::vector<BitMapFontPage> FontPages;

	BitMapFontCharacter GetCharacterPosition(unsigned char character);
};