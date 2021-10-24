#pragma once

namespace BF
{
	enum class FileActionResult
	{
		Successful,

		// Classic
		FileNotFound,
		OutOfMemory,

		//
		FileOpenFailure,
		FileCloseFailure,

		// Parsing
		FormatNotSupported,
		FormatNotAsExpected		
	};
}