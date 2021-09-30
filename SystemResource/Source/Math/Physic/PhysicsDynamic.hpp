#pragma once

#include "PhysicsStatic.hpp"
#include "../Geometry/Vector3.hpp"

namespace BF
{
	template<class NumberType>
	struct PhysicsDynamic : public PhysicsStatic<NumberType>
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

		PhysicsDynamic()
		{
			Mass = 0.3;
			EnablePhysics = false;
			EnableGravity = false;
			IsSolid = true;			
		}

		void ApplyGravity(Vector3<NumberType> gravity, NumberType deltaTime)
		{
			this->MatrixModel.Motion(Force, Velocity, Mass, gravity, deltaTime);
		}
	};
}