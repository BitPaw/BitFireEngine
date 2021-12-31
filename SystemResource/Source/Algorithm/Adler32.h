#pragma once

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
	};
}