#pragma once

namespace BF
{
	struct Adler32
	{
		public:
		static unsigned int Check(unsigned char* data, size_t length);
	};
}