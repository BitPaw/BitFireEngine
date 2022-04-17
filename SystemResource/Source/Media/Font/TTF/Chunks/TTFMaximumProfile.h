#pragma once

#include "TTFVersion.h"

namespace BF
{
	struct TTFMaximumProfile
	{
		public:
		TTFVersion Version;
		unsigned short NumberOfGlyphs; // the number of glyphs in the font
		unsigned short PointsMaximal; // points in non - compound glyph
		unsigned short ContoursMaximal; // contours in non - compound glyph
		unsigned short ComponentPointsMaximal; //points in compound glyph
		unsigned short ComponentContoursMaximal; //	contours in compound glyph
		unsigned short ZonesMaximal; // set to 2
		unsigned short TwilightPointsMaximal;//points used in Twilight Zone(Z0)
		unsigned short StorageMaximal; // number of Storage Area locations
		unsigned short FunctionDefsMaximal; // number of FDEFs
		unsigned short InstructionDefsMaximal; // number of IDEFs
		unsigned short StackElementsMaximal; // maximum stack depth
		unsigned short SizeOfInstructionsMaximal; // byte count for glyph instructions
		unsigned short ComponentElementsMaximal; // number of glyphs referenced at top level
		unsigned short ComponentDepthMaximal; // levels of recursion, set to 0 if font has only simple glyphs

		TTFMaximumProfile();
	};
}