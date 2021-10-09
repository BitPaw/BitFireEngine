#pragma once

#include "FNTPage.h"
#include "FNTChanalMode.h"

#include "FNTInfo.h"
#include "FNTCommonData.h"

#include "../IFontFormat.hpp"

namespace BF
{
	class FNT : public IFontFormat
	{
		public:
		FNTInfo Info; 
		FNTCommonData CommonData;

		size_t FontPageListSize;
		FNTPage* FontPageList;

		FNTCharacter* GetCharacterPosition(unsigned char character);

		FNT();
		~FNT();

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Font& font);
		FileActionResult ConvertFrom(Font& font);
		void PrintData();
	};
}