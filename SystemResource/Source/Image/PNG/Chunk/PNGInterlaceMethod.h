#pragma once

namespace BF
{
	enum class PNGInterlaceMethod
	{
		Invalid,

		NoInterlace,
		ADAM7Interlace		
	};

	PNGInterlaceMethod ConvertPNGInterlaceMethod(unsigned char interlaceMethod);
	unsigned char ConvertPNGInterlaceMethod(PNGInterlaceMethod interlaceMethod);
}