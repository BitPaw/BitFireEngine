#pragma once

namespace BF
{
	enum class ResourceLoadMode
	{
		// Just loads resource and do nothing else with it.
		Passthrough,

		// Loads reource and leaves it inactive for later use.
		LoadToCache,

		// Loads resource and registers it directly to the GPU.
		LoadToCacheAndUse,
	};
}