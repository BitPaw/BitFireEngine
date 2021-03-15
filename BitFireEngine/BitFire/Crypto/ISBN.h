#pragma once

#include "../Utility/ASCIIString.h"

namespace BF
{
	class ISBN
	{
		public:
		ASCIIString _isbn;

		ISBN(ASCIIString isbn);

		bool IsValid();
	};
}