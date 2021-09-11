#pragma once

#include "../Resource.h"
#include "../ResourceLoadingResult.hpp"
#include "FontFormat.h"
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
		ResourceLoadingResult Load(const char* filePath);	
		//---------------------------------------------------------------------
	};
}