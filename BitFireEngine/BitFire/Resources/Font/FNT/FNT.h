#pragma once

#include "FNTPage.h"
#include "FNTInfo.h"
#include "FNTCommonData.h"

#include "../Font.h"

namespace BF
{
	class FNT
	{
		public:
		FNTInfo FontInfo;
		FNTCommonData FontCommonData;

		List<FNTPage> FontPages;

		FNTCharacter* GetCharacterPosition(unsigned char character);
		
		void Load(AsciiString& filePath);
		void Save(AsciiString& filePath);
		void Convert(Font& font);
		void PrintData();
	};
}