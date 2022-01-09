#pragma once

#include "FNTChanalMode.h"

namespace BF
{
	struct FNTCommonData
	{
		public:
		int LineHeight;	// This is the distance in pixels between each line of text.		
		int Base;// The number of pixels from the absolute top of the line to the base of the characters.		
		int ScaleWidth; // The width of the texture, normally used to scale the x pos of the character image.	
		int ScaleHeight;	// The height of the texture, normally used to scale the y pos of the character image.	
		int AmountOfPages;	// The number of texture pages included in the font.	
		bool Packed; // Set to 1 if the monochrome characters have been packed into each of the texture channels.In this case alphaChnl describes what is stored in each channel.

		FNTChanalMode AlphaChanal;
		FNTChanalMode RedChanal;
		FNTChanalMode GreenChanal;
		FNTChanalMode BlueChanal;

		FNTCommonData();
	};
}