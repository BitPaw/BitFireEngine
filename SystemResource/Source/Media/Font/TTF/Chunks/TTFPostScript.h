#pragma once

#include "TTFVersion.h"

namespace BF
{
	struct TTFPostScript
	{
		// 0x00010000 for version 1.0
		// 0x00020000 for version 2.0
		// 0x00025000 for version 2.5 (deprecated)
		// 0x00030000 for version 3.0
		TTFVersion Version;

		//Fixed 	italicAngle;// 	Italic angle in counter - clockwise degrees from the vertical.Zero for upright text, negative for text that leans to the right(forward).
		//FWord 	underlinePosition;// 	This is the suggested distance of the top of the underline from the baseline(negative values indicate below baseline).
		// The PostScript definition of this FontInfo dictionary key(the y coordinate of the center of the stroke) is not used for historical reasons.The value of the PostScript key may be calculated by subtracting half the underlineThickness from the value of this field.
		//FWord 	underlineThickness;// 	Suggested values for the underline thickness.In general, the underline thickness should match the thickness of the underscore character(U + 005F LOW LINE), and should also match the strikeout thickness, which is specified in the OS / 2 table.
		unsigned int  isFixedPitch;// 	Set to 0 if the font is proportionally spaced, non - zero if the font is not proportionally spaced(i.e.monospaced).
		unsigned int  minMemType42;// 	Minimum memory usage when an OpenType font is downloaded.
		unsigned int  maxMemType42;// 	Maximum memory usage when an OpenType font is downloaded.
		unsigned int  minMemType1;// 	Minimum memory usage when an OpenType font is downloaded as a Type 1 font.
		unsigned int maxMemType1;// 	Maximum memory usage when an OpenType font is downloaded as a Type 1 font.

		// Version 1.0

		// Version 2.0
		unsigned short NumberOfGlyphs; // Number of glyphs(this should be the same as numGlyphs in 'maxp' table).
		unsigned short* GlyphNameIndex; // (NumberOfGlyphs) Array of indices into the string data.See below for details.
		char* StringData; // (variable) Storage for the string data.

		// Version 2.5
		// uint16 	numGlyphs 	Number of glyphs
		char* Offset; // (numGlyphs) Difference between graphic indexand standard order of glyph

		// Version 3.0
	};
}