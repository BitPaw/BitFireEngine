#pragma once

#include "../../../Mathematic/Geometry/Point.hpp"
#include "../../../IO/File/TextFile.h"
#include "../../../IO/File/FileLoader.h"

namespace BF
{
	class FNTCharacter
	{
		public:
		unsigned char ID;

		// Position of the character image in the texture.
		Point<float> Position;

		// Size of the character image in the texture.
		Point<float> Size;

		// Offset from the position-center.
		Point<float> Offset;

		// How much the current position should be advanced after drawing the character.
		unsigned char XAdvance;

		// The texture page where the character image is found.
		unsigned int Page;

		// The texture channel where the character image is found (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels).
		unsigned int Chanal;

		FNTCharacter();
		FNTCharacter
		(
			const unsigned char id,
			const Point<float> startPosition,
			const Point<float> size,
			const Point<float> offset,
			const unsigned char xAdvance
		);
	};
}