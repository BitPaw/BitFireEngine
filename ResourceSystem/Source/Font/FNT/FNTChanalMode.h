namespace BF
{
	enum class FNTChanalMode
	{		
		GlyphData,		// 0 if the channel holds the glyph data
		Outline, 		// 1 if it holds the outline		
		GlyphAndOutline,// 2 if it holds the glyphand the outline		
		SetToZero,		// 3 if its set to zero		
		SetToOne		// 4 if its set to one.
	};
}