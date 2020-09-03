#include "BitMapFontInfo.h"

BitMapFontInfo::BitMapFontInfo()
{
	Name = "[N/A]";
	Size = 70;
	Bold = false;
	Italic = false;
	CharSet = "";
	Unicode = false;
	StretchH = 100;
	Smooth = 1;
	AA = 1;
	CharacterPadding = Padding(3);
	SpacerOffset = Point();
}
