#pragma once

namespace BF
{
	class ZLIB
	{
		public:
		static void Unpack(unsigned char* inputData, size_t inputDataSize, unsigned char** outputData, size_t& outputDataSize);
	};
}