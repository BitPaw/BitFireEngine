#pragma once

namespace BF
{
	enum class FileActionResult
	{
		Successful,

		// Classic
		FileNotFound,
		OutOfMemory,

		// Parsing
		FormatNotSupported,
		FormatNotAsExpected		
	};
}