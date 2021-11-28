#pragma once

namespace BF
{
	enum class TTFSerifStyle
	{
		Invalid,

		Any,
		NoFit,
		Cove,
		ObtuseCove,
		SquareCove,
		ObtuseSquareCove,
		Square,
		Thin,
		Bone,
		Exaggerated,
		Triangle,
		NormalSans,
		ObtuseSans,
		PerpSans,
		Flared,
		Rounded
	};

	TTFSerifStyle ConvertTTFSerifStyle(unsigned char serifStyle);
}