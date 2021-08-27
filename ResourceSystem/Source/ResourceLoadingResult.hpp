#pragma once

namespace BF
{
	enum class ResourceLoadingResult
	{
		Successful,

		FormatNotSupported,

		FileNotFound,
		OutOfMemory
	};
}