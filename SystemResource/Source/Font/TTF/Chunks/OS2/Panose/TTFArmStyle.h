#pragma once

namespace BF
{
	enum class TTFArmStyle
	{
		Invalid,

		Any,
		NoFit,
		StraightArmsHorizontal,
		StraightArmsWedge,
		StraightArmsVertical,
		StraightArmsSingleSerif,
		StraightArmsDoubleSerif,
		NonStraightArmsHorizontal,
		NonStraightArmsWedge,
		NonStraightArmsVertical,
		NonStraightArmsSingleSerif,
		NonStraightArmsDoubleSerif
	};

	TTFArmStyle ConvertTTFArmStyle(unsigned char armStyle);
}