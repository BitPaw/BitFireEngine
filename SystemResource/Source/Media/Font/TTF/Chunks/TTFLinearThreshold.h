#pragma once

namespace BF
{
	struct TTFLinearThreshold
	{
		public:
		unsigned short Version; // Version number(starts at 0).
		unsigned short NumberOfGlyphs; // Number of glyphs(from “numGlyphs” in 'maxp' table).
		unsigned char* PelsHeightList; // The vertical pel height at which the glyph can be assumed to scale linearly.On a per glyph basis.
	
		TTFLinearThreshold();
	};
}