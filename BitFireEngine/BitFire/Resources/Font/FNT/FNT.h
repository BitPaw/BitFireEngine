#pragma once

#include <string>

#include "FNTPage.h"
#include "FNTInfo.h"
#include "FNTCommonData.h"

#include "../Font.h"

namespace BF
{
	class FNT : public Font
	{
		public:
		FNTInfo FontInfo;
		FNTCommonData FontCommon;

		List<FNTPage> FontPages;

		FNTCharacter* GetCharacterPosition(unsigned char character);
		void PrintData();
	};
}