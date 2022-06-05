#include "SBPText.h"
#include <Text/Text.h>

BF::SBPText::SBPText()
{
	Type = SBPTextTypeInvalid;
	TextA = 0;
}

BF::SBPText::SBPText(const char* text)
{
	Type = SBPTextTypeNarrow;
	TextA = text;
}

BF::SBPText::SBPText(const wchar_t* text)
{
	Type = SBPTextTypeWide;
	TextW = text;
}

size_t BF::SBPText::SizeInBytes() const
{
	switch(Type)
	{
		default:
		case SBPTextTypeInvalid:
			return 0;

		case SBPTextTypeNarrow:
			return Text::Length(TextA) + 1;

		case SBPTextTypeWide:
			return (Text::Length(TextW) +1 )* 2u;
	}
}
