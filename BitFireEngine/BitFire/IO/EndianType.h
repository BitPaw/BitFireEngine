#pragma once

// Ordering or sequencing of bytes
enum class EndianType
{
	// Left to Right. Left smallest value.
	Big,

	// Right to Left. Right smallest value.
	Little
};