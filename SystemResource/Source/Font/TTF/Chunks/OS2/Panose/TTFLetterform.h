#pragma once

namespace BF
{
	enum class TTFLetterform
	{
		Invalid,

		Any,
		NoFit,
		NormalContact,
		NormalWeighted,
		NormalBoxed,
		NormalFlattened,
		NormalRounded,
		NormalOffCenter,
		NormalSquare,
		ObliqueContact,
		ObliqueWeighted,
		ObliqueBoxed,
		ObliqueFlattened,
		ObliqueRounded,
		ObliqueOffCenter,
		ObliqueSquare
	};

	TTFLetterform ConvertTTFLetterform(unsigned char letterform);
}