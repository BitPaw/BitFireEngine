#pragma once

#include "FontFormat.h"

#include "../Resource.h"
#include "../File/FileActionResult.hpp"
#include "../Image/Image.h"

namespace BF
{
	class Font : public Resource
	{
		public:
		//---[ Data ]----------------------------------------------------------
		unsigned short CharacterSize;
		unsigned short SizeBetweenCharacters;
		unsigned short SizeBetweenLines;
		unsigned int AdditionalResourceListSize;
		char* AdditionalResourceList;
		Image* Texture;
		void* BitMapFont;		
		//---------------------------------------------------------------------

		//---[ Public-Functions ]----------------------------------------------
		static FontFormat FileFormatPeek(const char* filePath);
		FileActionResult Load(const char* filePath);	
		FileActionResult Save(const char* filePath, FontFormat fontFormat);
		//---------------------------------------------------------------------
	};
}