#pragma once

#include "../Geometry/Vector3.hpp"

namespace BF
{
	template<class NumberType>
	struct PhysicalBody
	{
		public:
		Vector3<NumberType> Velocity;
		Vector3<NumberType> Force;
		NumberType Mass;
		// Frriction static / dynamic
		// elastistity / boncyness

		bool EnablePhysics;
		bool EnableGravity;
		bool IsSolid;

		PhysicalBody()
		{
			Mass = 0.3;
			EnablePhysics = false;
			EnableGravity = false;
			IsSolid = true;
		}
	};
}