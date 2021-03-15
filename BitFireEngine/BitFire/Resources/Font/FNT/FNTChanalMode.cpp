namespace BF
{
	enum class FNTChanalMode
	{
		//  Set to 0 if the channel holds the glyph data
		GlyphData,

		// 1 if it holds the outline
		Outline,

		//  2 if it holds the glyphand the outline
		GlyphAndOutline,

		// 3 if its set to zero
		SetToZero,

		// 4 if its set to one.
		SetToOne
	};
}