#pragma once

#include <string>

#include "BitMapFont.h"
#include "BitMapFontCharacter.h"
#include "BitMapFontCommand.h"

#include "../../../Utility/StringSplitter.h"
#include "BitMapFontInfo.h"

class BitMapFontLoader
{
private:
	static BitMapFontInfo ParseInfoLine(std::string line);
	static BitMapFontCommonData ParseCommonDataLine(std::string line);
	static BitMapFontPage ParsePageLine(std::string line);
	static unsigned int ParseCharacterCountLine(std::string line);
	static BitMapFontCharacter ParseCharacterLine(std::string line);

public:
	static BitMapFont LoadBitMapFont(std::string path);
};