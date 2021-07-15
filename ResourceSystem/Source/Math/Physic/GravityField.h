#pragma once

#include "Collider.h"
#include "../Geometry/Position.hpp"

namespace BF
{
	class GravityField : public Collider
	{
		public:
		Position<float> Force;
	};
}