#pragma once

namespace BF
{
	enum class ZLIBCompressionLevel
	{
		InvalidCompressionLevel,

		Default,

		Slowest,

		Fast,
		Fastest	
	};

	ZLIBCompressionLevel ConvertCompressionLevel(unsigned char compressionLevel);
	unsigned char ConvertCompressionLevel(ZLIBCompressionLevel compressionLevel);
}