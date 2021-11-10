#pragma once

#include "ColliderType.h"
#include "../Geometry/Vector3.hpp"
#include "../Geometry/Vector2.hpp"

namespace BF
{
	class Collider
	{
		public:
		Vector3<float> Position;
		ColliderType Type;

		Collider(ColliderType type);

		virtual bool IsColliding(Vector2<float> position) = 0;
		virtual bool IsColliding(Vector3<float> position) = 0;
	};
}