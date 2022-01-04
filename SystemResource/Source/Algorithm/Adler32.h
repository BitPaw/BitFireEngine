#pragma once

#include <cstddef>

namespace BF
{
	struct Adler32
	{
		public:
		unsigned int Value;
		bool IsValid;

		Adler32();
		Adler32(unsigned int value);

		static unsigned int Check(unsigned char* data, size_t length);
		static unsigned int Create(size_t adler, const unsigned char* data, size_t length);
	};
}