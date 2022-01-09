#pragma once

namespace BF
{
	struct FNTCharacter
	{
		public:
		int ID;		
		float Position[2]; // Position of the character image in the texture.
		float Size[2];	// Size of the character image in the texture.		
		float Offset[2];// Offset from the position-center.				
		int XAdvance; // How much the current position should be advanced after drawing the character.		
		int Page; // The texture page where the character image is found.		
		int Chanal;// The texture channel where the character image is found (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels).

		FNTCharacter();
		FNTCharacter
		(
			const unsigned char id,
			const float startPosition[2],
			const float size[2],
			const float offset[2],
			const unsigned char xAdvance
		);
	};
}