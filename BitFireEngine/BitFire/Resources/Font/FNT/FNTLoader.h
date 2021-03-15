#pragma once

#include "FNT.h"
#include "FNTInfo.h"
#include "FNTCharacter.h"
#include "FNTCommand.h"

#include "../../ILoader.h"

namespace BF
{
	class FNTLoader : public ILoader
	{
		private:
		static void ParseInfoLine(ASCIIString& line, FNTInfo& fntInfo);
		static void ParseCommonDataLine(ASCIIString& line, FNTCommonData& fntCommonData);
		static void ParsePageLine(ASCIIString& line, FNTPage& fntPage);
		static unsigned int ParseCharacterCountLine(ASCIIString& line);
		static void ParseCharacterLine(ASCIIString& line, FNTCharacter& fntCharacter);

		public:
		static FNT* LoadFromFile(ASCIIString& path);
	};
}