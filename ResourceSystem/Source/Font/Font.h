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
		ResourceLoadingResult Load(const char* filePath);

		static FontFormat ParseFontFormat(const char* fileExtension);
		static bool IsFontFile(const char* fileExtension);
		//---------------------------------------------------------------------
	};
}