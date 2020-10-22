#pragma once

#include <string>

#include "FNTPage.h"
#include "FNTInfo.h"
#include "FNTCommonData.h"

#include "../IFont.h"

namespace BF
{
	class FNT : public IFont
	{
	public:
		FNTInfo FontInfo;
		FNTCommonData FontCommon;

		List<FNTPage> FontPages;

		FNTCharacter GetCharacterPosition(unsigned char character);
	};
}