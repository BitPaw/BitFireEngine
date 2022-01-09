#pragma once

#include <cstddef>
#include "FNTCharacter.h"

#define FNTPageFileNameSize 50

namespace BF
{
	struct FNTPage
	{
		public:
		int PageID;
		char PageFileName[FNTPageFileNameSize];
		size_t CharacteListSize;
		FNTCharacter* CharacteList;

		FNTPage();
		~FNTPage();
	};
}