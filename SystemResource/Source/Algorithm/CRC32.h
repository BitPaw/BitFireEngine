#pragma once

#include <cstddef>

namespace BF
{
	struct CRC32
	{
		public:
		static unsigned int Generate(const unsigned char* data, size_t length);
	};
}