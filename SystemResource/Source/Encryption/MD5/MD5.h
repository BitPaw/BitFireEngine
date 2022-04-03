#pragma once

#define MD5Length 16

namespace BF
{
	// Message-Digest Algorithm 5
	class MD5
	{
		private:
		unsigned int CalculatePerRoundShift(const unsigned int value);

		public:
		static size_t Encrypt(const char* input, const size_t inputSize, char* output, const size_t outputSize);
		static size_t Decrypt(const char* input, const size_t inputSize, char* output, const size_t outputSize);
	};
}