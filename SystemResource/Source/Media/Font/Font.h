#pragma once

#include "FontFormat.h"

#include <Resource.h>
#include <File/FileActionResult.hpp>
#include <Media/Image/Image.h>

namespace BF
{
	class Font : public Resource
	{
		public:
		//---[ Data ]----------------------------------------------------------
		unsigned short CharacterSize;
		unsigned short SizeBetweenCharacters;
		unsigned short SizeBetweenLines;
		size_t AdditionalResourceListSize;
		char** AdditionalResourceList;
		Image* Texture;
		void* BitMapFont;		
		//---------------------------------------------------------------------

		//---[ Public-Functions ]----------------------------------------------
		size_t FullSizeInMemory();
		static FontFormat FileFormatPeek(const wchar_t* filePath);

		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath, FontFormat fontFormat);
		//---------------------------------------------------------------------
	};
}