#pragma once

#include "FontFormat.h"

#include <Resource.h>
#include <Error/ActionResult.h>
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

		static FontFormat FileFormatPeek(const char* filePath);
		static FontFormat FileFormatPeek(const wchar_t* filePath);

		ActionResult Load(const char* filePath);
		ActionResult Load(const wchar_t* filePath);
		ActionResult Load(const unsigned char* fileData, const size_t fileDataSize, const FontFormat fontFormat);

		ActionResult Save(const wchar_t* filePath, FontFormat fontFormat);
		//---------------------------------------------------------------------
	};
}