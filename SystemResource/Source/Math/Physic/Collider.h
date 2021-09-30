#pragma once

#include "../Geometry/Vector2.hpp"
#include "../Geometry/Vector3.hpp"
#include "ColliderType.h"

namespace BF
{
	class Collider
	{
		public:
		ColliderType Type;

		Collider(ColliderType type);

		virtual bool IsColliding(Vector2<float> position) = 0;
		virtual bool IsColliding(Vector3<float> position) = 0;
	};
}