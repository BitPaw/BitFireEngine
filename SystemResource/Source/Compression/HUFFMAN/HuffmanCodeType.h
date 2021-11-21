#pragma once

namespace BF
{
	enum class HuffmanCodeType
	{
		InvalidCode,

		Literal,
		Length,
		EndOfBlock
	};

	HuffmanCodeType HuffmanCodeTypeFromCode(unsigned short code);
}