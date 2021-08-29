#pragma once

#include "../Geometry/Vector3.hpp"

namespace BF
{
	class PhysicalBody
	{
		public:
		Vector3<float> Velocity;
		Vector3<float> Force;
		float Mass;

		bool Enable;

		PhysicalBody();
	};
}