#include "FNT.h"

BF::FNTCharacter* BF::FNT::GetCharacterPosition(unsigned char character)
{
    FNTPage* page = &FontPages[0];
    unsigned int size = page->Characters.Size();

    for (unsigned int i = 0; i < size; i++)
    {
        FNTCharacter* bitMapFontCharacter = &page->Characters[i];
        unsigned char target = bitMapFontCharacter->ID;

        bool isSameCharacter = target == character;

        if (isSameCharacter)
        {
            return bitMapFontCharacter;
        }
    }

    return nullptr;
}

void BF::FNT::PrintData()
{
    printf(" +-------------------------------------------------------------------------+\n");
    printf(" | Font (%s) : %s\n", &FontInfo.CharSet[0], &FontInfo.Name[0]);
    printf(" +-------------------------------------------------------------------------+\n");
    printf(" | Size     : %4u | Smooth  : %3u |\n", FontInfo.Size, FontInfo.Smooth);
    printf(" | Bold     : %4s | AA      : %3u |\n", FontInfo.Bold ? "Yes" : "No", FontInfo.Supersampling);
    printf
    (
        " | Italic   : %4s | Padding : %u,%u,%u,%u |\n", 
        FontInfo.Italic ? "Yes" : "No", 
        FontInfo.CharacterPadding.Left,
        FontInfo.CharacterPadding.Top,
        FontInfo.CharacterPadding.Right,
        FontInfo.CharacterPadding.Bottom
    
    );
    printf(" | unicode  : %4s | Spacing : %u,%u |\n", FontInfo.Unicode ? "Yes" : "No", FontInfo.SpacerOffset.X, FontInfo.SpacerOffset.Y);
    printf(" | stretchH : %4u | Outline : %3u |\n", FontInfo.StretchH, FontInfo.OutlineThickness);


    for (unsigned int pageIndex = 0; pageIndex < FontPages.Size(); pageIndex++)
    {
        FNTPage* page = &FontPages[pageIndex];        

        //printf(" |          |       |       |       |       |       |       |       |\n");
        printf("\n");
        printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
        printf(" | Page <%u/%u> %s\n", pageIndex+1, FontPages.Size(), &page->PageFileName[0]);
        printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
        printf(" | Letter   | X-Pos | Y-Pos | Width | Height| X-Off | Y-Off | X-Step|\n");
        printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");

        for (unsigned int characterIndex = 0; characterIndex < page->Characters.Size(); characterIndex++)
        {
            FNTCharacter* character = &page->Characters[characterIndex];
           
            printf
            (
                " | %3u -> %c | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f | %5.1f |\n", 
                character->ID,
                character->ID, 
                character->Position.X, 
                character->Position.Y, 
                character->Size.X,
                character->Size.Y,                
                character->Offset.X,
                character->Offset.Y,
                character->XAdvance
            );
        }

        printf(" +----------+-------+-------+-------+-------+-------+-------+-------|\n");
    }
}
