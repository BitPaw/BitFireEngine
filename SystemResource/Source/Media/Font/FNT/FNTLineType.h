#pragma once

namespace BF
{
	enum class FNTLineType
	{
		Unkown,

		Info,
		Common,
		Page,
		CharacterCount,
		CharacterDefinition
	};

	FNTLineType ConvertFNTLineType(const unsigned char* line);
}