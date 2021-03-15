#pragma once
#include "FNTChanalMode.cpp"

namespace BF
{
	struct FNTCommonData
	{
		public:
		// This is the distance in pixels between each line of text.
		unsigned char LineHeight;
		// The number of pixels from the absolute top of the line to the base of the characters.
		unsigned char Base;
		// The width of the texture, normally used to scale the x pos of the character image.
		unsigned char ScaleWidth;
		// The height of the texture, normally used to scale the y pos of the character image.
		unsigned char ScaleHeight;

		// The number of texture pages included in the font.
		unsigned char AmountOfPages;

		// Set to 1 if the monochrome characters have been packed into each of the texture channels.In this case alphaChnl describes what is stored in each channel.
		bool Packed;
		
		FNTChanalMode AlphaChanal;
		FNTChanalMode RedChanal;
		FNTChanalMode GreenChanal;
		FNTChanalMode BlueChanal;

		FNTCommonData();
	};
}