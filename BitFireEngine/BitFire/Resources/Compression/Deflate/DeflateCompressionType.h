#pragma once

namespace BF
{
	enum class DeflateCompressionType
	{
		None,
		FixedHuffmanCodes,
		DynamicHuffmanCodes,

		// Yet undefined, error if used.
		Reserved
	};
}