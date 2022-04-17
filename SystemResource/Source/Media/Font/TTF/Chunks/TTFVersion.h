#pragma once

#include "TTFVersionType.h"

namespace BF
{
	struct TTFVersion
	{
		public:
		unsigned short Major;
		unsigned short Minor;
		TTFVersionType Type;

		TTFVersion();

		void Check();
	};
}