#pragma once

#include "FNTCharacter.h"

namespace BF
{
	struct FNTPage
	{
		public:
		unsigned int PageID;
		AsciiString PageFileName;
		List<FNTCharacter> Characters;

		FNTPage();
		FNTPage(const unsigned int pageID, AsciiString& pageFileName);
	};
}