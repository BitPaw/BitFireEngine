#pragma once

namespace BF
{
	// Ordering or sequencing of bytes
	enum class Endian
	{
		// Left to Right. Left smallest value.
		Big,

		// Right to Left. Right smallest value.
		Little
	};
}