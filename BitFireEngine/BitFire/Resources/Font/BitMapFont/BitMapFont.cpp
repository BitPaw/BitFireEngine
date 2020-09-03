#include "BitMapFont.h"

BitMapFontCharacter BitMapFont::GetCharacterPosition(unsigned char character)
{
    BitMapFontPage* page = &FontPages.at(0);
    BitMapFontCharacter bitMapFontCharacterReturnValue;
    unsigned int size = page->Characters.size();

    bool isSameCharacter;
    unsigned char target;
    BitMapFontCharacter* bitMapFontCharacter;

    for (unsigned int i = 0; i < size; i++)
    {
        bitMapFontCharacter = &page->Characters.at(i);
        target = bitMapFontCharacter->ID;

        isSameCharacter = target == character;

        if (isSameCharacter)
        {
            bitMapFontCharacterReturnValue = *bitMapFontCharacter;

            break;
        }
    }

    return bitMapFontCharacterReturnValue;
}
