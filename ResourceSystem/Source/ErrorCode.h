#pragma once

namespace BF
{
	enum class ErrorCode
	{
		Undefined,

		NoError,

		NotSupported,

		FileNotFound,
		EmptyFileName,
		LoadingFailed,
		SavingFailed,

		OutOfMemory,

		Empty
	};
}