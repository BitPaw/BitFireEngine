#pragma once

namespace BF
{
	enum class PlatformID
	{
		Invalid,

		Unicode,// Various
		Macintosh,// Script manager code
		ISO,// ISO encoding[deprecated]
		Windows,// Windows encoding
		Custom
	};

	PlatformID ConvertPlatformID(unsigned char platformID);
}
