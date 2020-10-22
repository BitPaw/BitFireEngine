#pragma once

#include <string>

#include "Font.h"
#include "IFont.h"
#include "FontFormat.h"

#include "FNT/FNTLoader.h"
#include "OTF/OTFLoader.h"
#include "TTF/TTFLoader.h"

#include "../../IO/File/TextFile.h"
#include "../../IO/Message/MessageSystem.h"

namespace BF
{
	class FontLoader
	{
		public:
		IFont* LoadFontFromFile(std::string filePath);

		FNT* FNTToFont(Font* font);
		OTF* OTFToFont(Font* font);
		TTF* TTFToFont(Font* font);

		Font* FontToFNT(FNT fnt);
		Font* FontToOTF(OTF otf);
		Font* FontToTTF(TTF ttf);
	};
}