#pragma once

#include "ColliderType.h"
#include "CollisionListener.h"

#include <Math/Geometry/Vector2.hpp>
#include <Math/Geometry/Vector3.hpp>
#include <Math/Geometry/Rectangle.hpp>

namespace BF
{
	class Collider
	{
		public:
		Rectangle<float> BoundingBox;
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