#pragma once

namespace BF
{
	enum class SBPResult
	{
		Invalid,

		PackageSendingFailure,

		// Nobody is listening for a result
		PackageSendSucessfulButNoResponder,

		PackageAnswered,
		PackageTimeout,

		PackageDetectedRegistered,
		PackageDetectedCustom,

		InvalidHeader
	};
}