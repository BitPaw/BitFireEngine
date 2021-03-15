#include "FNTInfo.h"

BF::FNTInfo::FNTInfo()
{
	Name = "[N/A]";
	Size = 70;
	Bold = false;
	Italic = false;
	CharSet = "";
	Unicode = false;
	StretchH = 100;
	Smooth = 1;
	Supersampling = 1;
	CharacterPadding.Set(0);
	SpacerOffset.Set(0, 0);
}
