#pragma once

#include "../Resource.h"
#include "../ErrorCode.h"
#include "FontFormat.h"
#include "../../Mathematic/Geometry/Shape/Rectangle.h"
#include "../../Utility/Dictionary.hpp"
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
		ErrorCode Load(AsciiString& filePath);

		static FontFormat ParseFontFormat(AsciiString& fileExtension);
		static bool IsFontFile(AsciiString& fileExtension);
		//---------------------------------------------------------------------
	};
}