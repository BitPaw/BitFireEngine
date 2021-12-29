#pragma once

#include "../Geometry/Shape/Rectangle.h"
#include "ColliderType.h"
#include "../Geometry/Vector3.hpp"
#include "../Geometry/Vector2.hpp"

namespace BF
{
	class Collider
	{
		public:
		Rectangle BoundingBox;
		ColliderType Type;

		Collider(ColliderType type);

		virtual bool IsColliding(Vector2<float> position) = 0;
		virtual bool IsColliding(Vector3<float> position) = 0;

		Vector3<float> Position();
	};
}