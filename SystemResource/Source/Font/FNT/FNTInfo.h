#pragma once

#define FontNameSize 30u
#define CharSetNameSize 10u

namespace BF
{
	struct FNTInfo
	{
		public:
		char Name[FontNameSize]; // Name of this font. (synonym: face)
		unsigned int Size;// Size of the Letters int Pixel as height.
		bool Bold;// Is the text fat?
		bool Italic;// Is the text cursive?
		char CharSet[CharSetNameSize];// The name of the OEM charset used (when not unicode). Like 'ANSI'.
		bool Unicode;// Is the charset in the unicode format?
		unsigned int StretchH;
		bool Smooth;// Set to 1 if smoothing was turned on.
		bool Supersampling; // Supersampling level used. 1 means no supersampling was used. (AA)
		unsigned int CharacterPadding[4]; // Padding for each character.
		unsigned int SpacerOffset[2];
		unsigned int OutlineThickness;// How thick is the line arount the Letter?

		FNTInfo();
	};
}