#pragma once

#include <string>
#include "../../../UI/Padding.h"
#include "../../../Mathematic/Geometry/Point.h"

namespace BF
{
	class FNTInfo
	{
	public:
		std::string Name;
		unsigned int Size;
		bool Bold;
		bool Italic;
		std::string	CharSet;
		bool Unicode;
		unsigned int StretchH;
		unsigned int Smooth;
		bool AA;
		Padding CharacterPadding;
		Point SpacerOffset;

		FNTInfo();
	};
}