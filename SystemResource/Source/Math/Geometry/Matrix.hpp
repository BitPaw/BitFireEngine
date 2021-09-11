#pragma once

namespace BF
{
	template<class Numbertype, unsigned int Width, unsigned int Height>
	struct Matrix
	{
		public:
		Numbertype Data[Width * Height];
	};
}