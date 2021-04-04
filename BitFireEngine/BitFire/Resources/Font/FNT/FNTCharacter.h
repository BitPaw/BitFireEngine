#pragma once

#include "../../../Mathematic/Geometry/Point.hpp"

namespace BF
{
	class FNTCharacter
	{
		public:
		unsigned char ID;		
		Point<float> Position; // Position of the character image in the texture.
		Point<float> Size;	// Size of the character image in the texture.		
		Point<float> Offset;// Offset from the position-center.				
		unsigned char XAdvance; // How much the current position should be advanced after drawing the character.		
		unsigned int Page; // The texture page where the character image is found.		
		unsigned int Chanal;// The texture channel where the character image is found (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels).

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