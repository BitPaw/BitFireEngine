#pragma once

#include <string>

#include "FNTCharacter.h"

namespace BF
{
	struct FNTPage
	{
	public:
		unsigned int PageID;
		std::string PageFileName;
		List<FNTCharacter> Characters;

		FNTPage();
		FNTPage(const unsigned int pageID, std::string pageFileName);
	};
}