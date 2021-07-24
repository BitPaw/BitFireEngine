#pragma once

#include "../Resource.h"
#include "../ErrorCode.h"
#include "FontFormat.h"
#include "../Image/Image.h"

namespace BF
{
	class Font : public Resource
	{
	public:
		//---[ Data ]----------------------------------------------------------
		AsciiString Name;
		unsigned short CharacterSize;
		unsigned short SizeBetweenCharacters;
		unsigned short SizeBetweenLines;
		List<AsciiString> AdditionalResourceList;
		Image* Texture;
		void* BitMapFont;		
		//---------------------------------------------------------------------

		//---[ Public-Functions ]----------------------------------------------
		ErrorCode Load(const char* filePath);

		static FontFormat ParseFontFormat(const char* fileExtension);
		static bool IsFontFile(const char* fileExtension);
		//---------------------------------------------------------------------
	};
}