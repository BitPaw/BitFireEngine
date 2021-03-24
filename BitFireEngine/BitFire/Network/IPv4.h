#pragma once

#include "../Utility/List.hpp"
#include "../Utility/AsciiString.h"

namespace BF
{
	class IPv4
	{
		private:
		List<unsigned char> _octetList;

		public:
		IPv4();
		IPv4(AsciiString ip);

		void SetAdress(AsciiString ip);
		static bool IsValidIP(AsciiString ip);
		AsciiString ToString();
	};
}