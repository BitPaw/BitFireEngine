#include "SBPText.h"
#include <Text/Text.h>

BF::SBPText::SBPText()
{
	Type = SBPTextType::Invalid;
	TextA = 0;
}

BF::SBPText::SBPText(const char* text)
{
	Type = SBPTextType::Narrow;
	TextA = text;
}

BF::SBPText::SBPText(const wchar_t* text)
{
	Type = SBPTextType::Wide;
	TextW = text;
}

size_t BF::SBPText::SizeInBytes() const
{
	switch(Type)
	{
		default:
		case BF::SBPTextType::Invalid:
			return 0;

		case BF::SBPTextType::Narrow:
			return Text::Length(TextA) + 1;

		case BF::SBPTextType::Wide:
			return (Text::Length(TextW) +1 )* 2u;
	}
}
