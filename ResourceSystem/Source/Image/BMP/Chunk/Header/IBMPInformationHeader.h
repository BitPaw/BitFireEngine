#pragma once

namespace BF
{
	class IBMPInformationHeader
	{
	public:
		// [4-Bytes] size of this header, in bytes(40)
		unsigned int HeaderSize;

		// [4-Bytes] bitmap width in pixels(signed integer)
		int Width;

		// [4-Bytes] bitmap height in pixels(signed integer)
		int Height;
	};
}