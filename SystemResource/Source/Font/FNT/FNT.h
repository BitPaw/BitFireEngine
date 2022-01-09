#pragma once

#include "FNTPage.h"
#include "FNTChanalMode.h"

#include "FNTInfo.h"
#include "FNTCommonData.h"

#include "../IFontFormat.hpp"

namespace BF
{
	struct FNT : public IFontFormat
	{
		public:
		FNTInfo Info; 
		FNTCommonData CommonData;

		size_t FontPageListSize;
		FNTPage* FontPageList;

		FNTCharacter* GetCharacterPosition(unsigned char character);

		FNT();
		~FNT();



		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Font& font);
		FileActionResult ConvertFrom(Font& font);
		void PrintData();
	};
}