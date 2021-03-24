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
		static void ParseInfoLine(AsciiString& line, FNTInfo& fntInfo);
		static void ParseCommonDataLine(AsciiString& line, FNTCommonData& fntCommonData);
		static void ParsePageLine(AsciiString& line, FNTPage& fntPage);
		static unsigned int ParseCharacterCountLine(AsciiString& line);
		static void ParseCharacterLine(AsciiString& line, FNTCharacter& fntCharacter);

		public:
		static FNT* LoadFromFile(AsciiString& path);
	};
}