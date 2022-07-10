#pragma once

#include <Container/ClusterInt.h>

namespace BF
{
	struct SBPDataPackage
	{
		ClusterInt SymbolID;

		virtual size_t Parse(const void* inputData, const size_t inputDataSize) = 0;
		virtual size_t Serialize(void* outputData, const size_t outputDataSize) const = 0;
	};
}