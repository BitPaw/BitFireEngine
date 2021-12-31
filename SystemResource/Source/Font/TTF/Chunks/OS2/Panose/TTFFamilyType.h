#pragma once

namespace BF
{
	enum class TTFFamilyType
	{
		Invalid,

		Any,
		NoFit,
		TextAndDisplay,
		Script,
		Decorative,
		Pictorial
	};

	TTFFamilyType ConvertTTFFamilyType(unsigned char familyType);
}