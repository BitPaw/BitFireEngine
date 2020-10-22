#pragma once

#include <string>

#include "FNT.h"
#include "FNTInfo.h"
#include "FNTCharacter.h"
#include "FNTCommand.h"

#include "../../ILoader.h"
#include "../../../Utility/StringSplitter.h"

namespace BF 
{
	class FNTLoader : public ILoader
	{
	private:
		static FNTInfo ParseInfoLine(std::string line);
		static FNTCommonData ParseCommonDataLine(std::string line);
		static FNTPage ParsePageLine(std::string line);
		static unsigned int ParseCharacterCountLine(std::string line);
		static FNTCharacter ParseCharacterLine(std::string line);

	public:
		static FNT* LoadFromFile(std::string path);
	};
}