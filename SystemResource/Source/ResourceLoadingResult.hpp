#pragma once

namespace BF
{
	enum class ResourceLoadingResult
	{
		Successful,

		FormatNotSupported,
		FormatInvalid,

		FileNotFound,
		OutOfMemory
	};
}