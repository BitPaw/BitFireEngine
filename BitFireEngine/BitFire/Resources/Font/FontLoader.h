#pragma once

#include "Font.h"
#include "IFont.h"
#include "FontFormat.h"

#include "FNT/FNTLoader.h"
#include "OTF/OTFLoader.h"
#include "TTF/TTFLoader.h"

#include "../../IO/File/TextFile.h"
#include "../../IO/Log/Log.h"

namespace BF
{
	class FontLoader
	{
		public:
		static Font* LoadFontFromFile(AsciiString& filePath);

		static FontFormat ParseFontFormat(AsciiString& fileExtension);
		static bool IsFontFile(AsciiString& fileExtension);

		static FNT* FNTToFont(Font* font);
		static OTF* OTFToFont(Font* font);
		static TTF* TTFToFont(Font* font);

		static Font* FontToFNT(FNT fnt);
		static Font* FontToOTF(OTF otf);
		static Font* FontToTTF(TTF ttf);
	};
}