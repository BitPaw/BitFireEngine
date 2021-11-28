#pragma once

namespace BF
{
	enum class TTFWeight
	{
		Invalid,

		Any,
		NoFit,
		VeryLight,
		Light,
		Thin,
		Book,
		Medium,
		Demi,
		Bold,
		Heavy,
		Black,
		Nord
	};

	TTFWeight ConvertTTFWeight(unsigned char weight);
}