#pragma once

namespace BF
{
	struct TTFKerningPair
	{
		public:
		unsigned short Left;// 	The glyph index for the left - hand glyph in the kerning pair.
		unsigned short Right;// 	The glyph index for the right - hand glyph in the kerning pair.
		short Value;// 	The kerning value for the above pair, in FUnits.If this value is greater than zero, the characters will be moved apart.If this value is less than zero, the character will be moved closer together.
	
		TTFKerningPair();
	};
}