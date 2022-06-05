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

		FNTCharacter* GetCharacterPosition(const unsigned char character);

		FNT();
		~FNT();

		FileActionResult Load(const char* filePath);
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Font& font);
		FileActionResult ConvertFrom(Font& font);
		void PrintData();
	};
}