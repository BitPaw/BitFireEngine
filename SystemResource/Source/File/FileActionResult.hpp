#pragma once

namespace BF
{
	enum class FileActionResult
	{
		Successful,

		// Classic
		FileNotFound,
		OutOfMemory,
		FileEmpty,

		//
		FileOpenFailure,
		FileCloseFailure,

		// Parsing
		FormatNotSupported,
		FormatNotAsExpected		
	};
}