#pragma once

namespace BF
{
	enum class ZLIBCompressionMethod
	{
		Invalid,

		Deflate,
		Reserved
	};

	ZLIBCompressionMethod ConvertCompressionMethod(unsigned char compressionMethod);
	unsigned char ConvertCompressionMethod(ZLIBCompressionMethod compressionMethod);

	const char* CompressionMethodToString(ZLIBCompressionMethod compressionMethod);
}