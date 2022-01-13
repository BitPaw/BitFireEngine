#pragma once

#include "../Geometry/Shape/Rectangle.h"
#include "ColliderType.h"
#include "../Geometry/Vector3.hpp"
#include "../Geometry/Vector2.hpp"
#include "CollisionListener.h"

namespace BF
{
	class Collider
	{
		public:
		Rectangle BoundingBox;
		ColliderType Type;

		// CallBacks
		CollisionListener* OnCollisionCallBack;

		Collider(ColliderType type);

		virtual bool IsColliding(Vector2<float> position) = 0;
		virtual bool IsColliding(Vector3<float> position) = 0;

		bool IsInBoundingBox
		(
			Vector3<float> ancerPosition,
			Vector3<float> ancerSize,
			Vector3<float> targetPosition,
			Vector3<float> targetSize
		);
	};
}