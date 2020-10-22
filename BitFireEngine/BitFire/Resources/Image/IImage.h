#pragma once

#include <string>

#include "../../Utility/List.hpp"

namespace BF
{
	struct IImage
	{
		public:
		unsigned int Height;
		unsigned int Width;

		IImage();
	};
}