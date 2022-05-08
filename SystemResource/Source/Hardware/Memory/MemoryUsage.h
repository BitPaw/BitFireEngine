#pragma once

#include <cstddef>

namespace BF
{
	struct MemoryUsage
	{
		public:
		size_t PercentInUse;
		size_t PhysicalTotal;
		size_t PhysicalAvailable;
		size_t VirtualTotal;
		size_t VirtualAvailable;
		size_t PageFileTotal;
		size_t PageFileAvailable;
		size_t ExtendedVirtualAvailable;
	};
}
