#pragma once

#include "BitMapFontCharacter.h"

class BitMapFont
{
public:
	unsigned int AmountOfCharacters;
	BitMapFontCharacter* BitMapFontCharacterList;

	BitMapFont(const unsigned int amountOfCharacters);
	~BitMapFont();
};