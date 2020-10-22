#include "FNT.h"

BF::FNTCharacter BF::FNT::GetCharacterPosition(unsigned char character)
{
    FNTPage* page = &FontPages[0];
    FNTCharacter bitMapFontCharacterReturnValue;
    unsigned int size = page->Characters.Size.Value;

    bool isSameCharacter;
    unsigned char target;
    FNTCharacter* bitMapFontCharacter;

    for (unsigned int i = 0; i < size; i++)
    {
        bitMapFontCharacter = &page->Characters[i];
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
