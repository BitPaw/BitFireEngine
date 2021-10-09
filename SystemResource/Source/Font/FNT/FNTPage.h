#pragma once

#include "FNTCharacter.h"

#define FNTPageFileNameSize 30

namespace BF
{
	struct FNTPage
	{
		public:
		unsigned int PageID;
		char PageFileName[FNTPageFileNameSize];
		size_t CharacteListSize;
		FNTCharacter* CharacteList;

		FNTPage();
		~FNTPage();
	};
}