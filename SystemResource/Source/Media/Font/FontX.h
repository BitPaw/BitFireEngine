#pragma once

#include <Error/ActionResult.h>
#include <File/Font.h>

namespace BF
{
	class FontX : public Font
	{
		public:
		//---[ Public-Functions ]----------------------------------------------
		size_t FullSizeInMemory();

		ActionResult Load(const char* filePath);
		ActionResult Load(const wchar_t* filePath);
		ActionResult Load(const unsigned char* fileData, const size_t fileDataSize, const FontFileFormat fontFormat);

		ActionResult Save(const wchar_t* filePath, FontFileFormat fontFormat);
		//---------------------------------------------------------------------
	};
}