#pragma once

namespace BF
{
	class RGB8Bit
	{
	public:
		unsigned char Red;
		unsigned char Green;
		unsigned char Blue;

		RGB8Bit();
		RGB8Bit(const unsigned char red, const unsigned char green, const unsigned char blue);
	};
}