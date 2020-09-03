#include "BitMapFont.h"

BitMapFont::BitMapFont(const unsigned int amountOfCharacters)
{
	AmountOfCharacters = amountOfCharacters;

	BitMapFontCharacterList = new BitMapFontCharacter[amountOfCharacters];
}

BitMapFont::~BitMapFont()
{
	for (size_t i = 0; i < AmountOfCharacters; i++)
	{
		delete &BitMapFontCharacterList[i];
	}
}
