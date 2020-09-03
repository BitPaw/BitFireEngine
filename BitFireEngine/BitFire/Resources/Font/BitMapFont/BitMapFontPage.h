#pragma once

#include <string>
#include <vector>

#include "BitMapFontCharacter.h"

class BitMapFontPage
{
public:
	unsigned int PageID;
	std::string PageFileName;
	std::vector<BitMapFontCharacter> Characters;

	BitMapFontPage();
	BitMapFontPage(const unsigned int pageID, std::string pageFileName);
};