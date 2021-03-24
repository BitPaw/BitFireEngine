#pragma once

#include "DeflateCompressionType.h"

namespace BF
{
	class DeflateCompressedBlock
	{
		public:
		bool IsLastBlock;
		DeflateCompressionType CompressionType;
	};
}