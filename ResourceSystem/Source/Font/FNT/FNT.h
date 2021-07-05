#pragma once

#include "FNTPage.h"
#include "FNTChanalMode.h"

#include "../Font.h"
#include "../../Container/AsciiString.h"

namespace BF
{
	class FNT
	{
		public:
		//---[ FontInfo ]------------------------------------------------------
		char Name[30]; // Name of this font. (synonym: face)
		unsigned int Size;// Size of the Letters int Pixel as height.
		bool Bold;// Is the text fat?
		bool Italic;// Is the text cursive?
		char CharSet[10];// The name of the OEM charset used (when not unicode). Like 'ANSI'.
		bool Unicode;// Is the charset in the unicode format?
		unsigned int StretchH;
		bool Smooth;// Set to 1 if smoothing was turned on.
		bool Supersampling; // Supersampling level used. 1 means no supersampling was used. (AA)
		unsigned int CharacterPadding[4]; // Padding for each character.
		unsigned int SpacerOffset[2];
		unsigned int OutlineThickness;// How thick is the line arount the Letter?
		//---------------------------------------------------------------------

		//---[FontCommonData]--------------------------------------------------	
		unsigned int LineHeight;	// This is the distance in pixels between each line of text.		
		unsigned int Base;// The number of pixels from the absolute top of the line to the base of the characters.		
		unsigned int ScaleWidth; // The width of the texture, normally used to scale the x pos of the character image.	
		unsigned int ScaleHeight;	// The height of the texture, normally used to scale the y pos of the character image.	
		unsigned int AmountOfPages;	// The number of texture pages included in the font.		
		bool Packed; // Set to 1 if the monochrome characters have been packed into each of the texture channels.In this case alphaChnl describes what is stored in each channel.

		FNTChanalMode AlphaChanal;
		FNTChanalMode RedChanal;
		FNTChanalMode GreenChanal;
		FNTChanalMode BlueChanal;
		//---------------------------------------------------------------------


		List<FNTPage> FontPages;

		FNTCharacter* GetCharacterPosition(unsigned char character);

		FNT();

		void Load(char* filePath);
		void Load(AsciiString& filePath);
		void Save(AsciiString& filePath);
		void Convert(Font& font);
		void PrintData();
	};
}