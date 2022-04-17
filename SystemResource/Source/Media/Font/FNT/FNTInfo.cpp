#include "FNTInfo.h"

BF::FNTInfo::FNTInfo()
{
	Name[0] = 0;
	Size = 70;
	Bold = false;
	Italic = false;
	CharSet[0] = 0;
	Unicode = false;
	StretchH = 100;
	Smooth = 1;
	Supersampling = 1;
	CharacterPadding[0] = 0;
	CharacterPadding[1] = 0;
	CharacterPadding[2] = 0;
	CharacterPadding[3] = 0;
	SpacerOffset[0] = 0;
	SpacerOffset[1] = 0;
	OutlineThickness = 0;
}
