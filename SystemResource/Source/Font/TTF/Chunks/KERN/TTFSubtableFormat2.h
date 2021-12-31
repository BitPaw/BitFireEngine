#pragma once

namespace BF
{
	struct TTFSubtableFormat2
	{
		public:
		unsigned short RowWidth;// 	The width, in bytes, of a row in the table.
		unsigned short LeftClassOffset;// 	Offset from beginning of this subtable to left - hand class table.
		unsigned short RightClassOffset;// 	Offset from beginning of this subtable to right - hand class table.
		unsigned short KerningArrayOffset;// 	Offset from beginning of this subtable to the start of the kerning array.

		TTFSubtableFormat2();
	};
}