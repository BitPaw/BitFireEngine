#pragma once

namespace BF
{
	enum class FileActionResult
	{
		Invalid,

		Successful,

		EmptyPath,

		// Classic
		FileNotFound,
		OutOfMemory,
		FileEmpty,

		//
		FileOpenFailure,
		FileCloseFailure,
		FileReadFailure,
		FileCopyFailure,

		FileMemoryMappingFailed,

		// Parsing
		InvalidHeaderSignature,
		InvalidVersion,

		FormatNotSupported,
		FormatNotAsExpected		
	};
}