#pragma once

#include "../Utility/AsciiString.h"

namespace BF
{
	class ISBN
	{
		public:
		AsciiString _isbn;

		ISBN(AsciiString isbn);

		bool IsValid();
	};
}