#pragma once

#include "Collider.h"
#include "ColliderType.h"
#include <Math/Geometry/Vector3.hpp>

#define GravityForceSun 274
#define GravityForceMercury 3.7
#define GravityForceVenus 8.87
#define GravityForceEarth 9.807
#define GravityForceEarthMoon 1.62
#define GravityForceMars 3.721
#define GravityForceJupiter 24.79
#define GravityForceSaturn 10.44
#define GravityForceNeptune 11.15
#define GravityForceUranus 8.87
#define GravityForcePluto 0.62

namespace BF
{
	class GravityField : public Collider
	{
		public:	
		float PullForce;
		Vector3<float> PullDirection;
		Vector3<bool> IgnoreAxis;

		GravityField();
	};
}