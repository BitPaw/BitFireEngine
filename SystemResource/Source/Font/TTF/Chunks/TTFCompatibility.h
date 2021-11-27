#pragma once

#include "TTFVersion.h"
#include "../Panose/TTFPanose.h"

namespace BF
{
	struct TTFCompatibility
	{
		public:
		// Base
		unsigned short Version;// table version number(set to 0)
		short xAvgCharWidth;// average weighted advance width of lower case lettersand space
		unsigned short usWeightClass;// visual weight(degree of blackness or thickness) of stroke in glyphs
		unsigned short usWidthClass;//relative change from the normal aspect ratio(width to height ratio) as specified by a font designer for the glyphs in the font
		short fsType;// characteristicsand properties of this font(set undefined bits to zero)
		short ySubscriptXSize;// recommended horizontal size in pixels for subscripts
		short ySubscriptYSize;// recommended vertical size in pixels for subscripts
		short ySubscriptXOffset;// recommended horizontal offset for subscripts
		short ySubscriptYOffset;//recommended vertical offset form the baseline for subscripts
		short ySuperscriptXSize;//recommended horizontal size in pixels for superscripts
		short ySuperscriptYSize;// recommended vertical size in pixels for superscripts
		short ySuperscriptXOffset;//recommended horizontal offset for superscripts
		short ySuperscriptYOffset;//recommended vertical offset from the baseline for superscripts
		short yStrikeoutSize;// width of the strikeout stroke
		short yStrikeoutPosition;// position of the strikeout stroke relative to the baseline
		short sFamilyClass;//classification of font - family design.
		TTFPanose Panose;//10 byte series of number used to describe the visual characteristics of a given typeface
		unsigned int ulUnicodeRange[4];//Field is split into two bit fields of 96 and 36 bits each.The low 96 bits are used to specify the Unicode blocks encompassed by the font file.The high 32 bits are used to specify the character or script sets covered by the font file.Bit assignments are pending.Set to 0
		char achVendID[4];//four character identifier for the font vendor
		unsigned short fsSelection;//2 - byte bit field containing information concerning the nature of the font patterns
		unsigned short fsFirstCharIndex;//The minimum Unicode index in this font.
		unsigned short fsLastCharIndex;//The maximum Unicode index in this font.

		// Additional Fields

		short sTypoAscender;//The typographic ascender for this font.This is not necessarily the same as the ascender value in the 'hhea' table.
		short sTypoDescender;// The typographic descender for this font.This is not necessarily the same as the descender value in the 'hhea' table.
		short sTypoLineGap;//The typographic line gap for this font.This is not necessarily the same as the line gap value in the 'hhea' table.
		unsigned short usWinAscent;//The ascender metric for Windows.usWinAscent is computed as the yMax for all characters in the Windows ANSI character set.
		unsigned short usWinDescent;//The descender metric for Windows.usWinDescent is computed as the - yMin for all characters in the Windows ANSI character set.
		unsigned int ulCodePageRange1;//Bits 0 - 31
		unsigned int ulCodePageRange2;//Bits 32 - 63
		short sxHeight;//The distance between the baseline and the approximate height of non - ascending lowercase letters measured in FUnits.
		short sCapHeight;//The distance between the baseline and the approximate height of uppercase letters measured in FUnits.
		unsigned short usDefaultChar;// The default character displayed by Windows to represent an unsupported character. (Typically this should be 0.)
		unsigned short usBreakChar;//The break character used by Windows.
		unsigned short usMaxContext;//The maximum length of a target glyph OpenType context for any feature in this font.
		unsigned short usLowerPointSize;//Proposed for version 5 The lowest size(in twentieths of a typographic point), at which the font starts to be used.This is an inclusive value.
		unsigned short usUpperPointSize;//Proposed for version 5 The highest size(in twentieths of a typographic point), at which the font starts to be used.This is an exclusive value.Use 0xFFFFU to indicate no upper limit.
	
		TTFCompatibility();
	};
}