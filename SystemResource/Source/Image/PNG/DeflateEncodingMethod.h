#pragma once

namespace BF
{
	enum class DeflateEncodingMethod
	{
		Invalid,

		LiteralRaw,
		HuffmanStatic,
		HuffmanDynamic,
		Reserverd
	};
}