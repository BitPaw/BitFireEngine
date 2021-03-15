#pragma once

#include "../Utility/List.hpp"
#include "../Utility/ASCIIString.h"

namespace BF
{
	class IPv4
	{
		private:
		List<unsigned char> _octetList;

		public:
		IPv4();
		IPv4(ASCIIString ip);

		void SetAdress(ASCIIString ip);
		static bool IsValidIP(ASCIIString ip);
		ASCIIString ToString();
	};
}