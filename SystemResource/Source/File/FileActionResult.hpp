#pragma once

namespace BF
{
	enum class FileActionResult
	{
		Successful,

		EmptyPath,

		// Classic
		FileNotFound,
		OutOfMemory,
		FileEmpty,

		//
		FileOpenFailure,
		FileCloseFailure,

		// Parsing
		InvalidHeaderSignature,
		InvalidVersion,

		FormatNotSupported,
		FormatNotAsExpected		
	};
}