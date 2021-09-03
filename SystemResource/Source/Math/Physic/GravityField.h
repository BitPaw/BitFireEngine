#pragma once

#include "Collider.h"
#include "../Geometry/Vector3.hpp"

namespace BF
{
	class GravityField : public Collider
	{
		public:
		Vector3<float> Force;
	};
}