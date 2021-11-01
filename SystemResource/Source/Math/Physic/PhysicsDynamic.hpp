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
		NumberType Friction;
		// Frriction static / dynamic
		// elastistity / boncyness

		bool EnablePhysics;
		bool EnableGravity;
		bool IsSolid;

		PhysicsDynamic()
		{
			Mass = 0.3;
			Friction = 1;
			EnablePhysics = false;
			EnableGravity = false;
			IsSolid = true;			
		}

		void ApplyGravity(Vector3<NumberType> gravityDircetion, NumberType gravityForce, NumberType deltaTime)
		{
			// TODO: Rewrite code

			// Force = Mass * Acceleration

			assert(Mass > 0);
			assert(gravityForce > 0);

			Force += gravityDircetion * gravityForce;

			// Acceleration = Force / Mass
			Vector3<NumberType> acceleration = (Force / Mass);

			Velocity += acceleration;
			Force.Set(0, 0, 0);

			// Friction = -1 * FrictionFector * N *** Velocity-Normalized
			NumberType friction = 1;
			NumberType normalForce = Mass;
			Vector3<NumberType> FrictionDirection = Vector3<NumberType>::Normalize(Velocity) * -1 * friction * normalForce;

			//Velocity -= FrictionDirection;


			// Fake friction
			Velocity *= 0.75f;

			this->MatrixModel.Move(Velocity);

		}
	};
}