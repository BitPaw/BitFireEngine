#pragma once

#include "../../../../Mathematic/Geometry/Point.hpp"

namespace BF
{
	struct PNGPrimaryChromaticities
	{
		public:
		Point<unsigned int> White;
		Point<unsigned int> Red;
		Point<unsigned int> Green;
		Point<unsigned int> Blue;
	};
}