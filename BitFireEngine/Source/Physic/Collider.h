#pragma once

#include "ColliderType.h"
#include "CollisionListener.h"

#include <Math/PXVector.h>

namespace BF
{
	class Collider
	{
		public:
		//Rectangle<float> BoundingBox;
		ColliderType Type;

		// CallBacks
		CollisionListener* OnCollisionCallBack;

		Collider(ColliderType type);

		virtual bool IsColliding(PXVector2F* const position) = 0;
		virtual bool IsColliding(PXVector3F* const position) = 0;

		bool IsInBoundingBox
		(
			PXVector3F ancerPosition,
			PXVector3F ancerSize,
			PXVector3F targetPosition,
			PXVector3F targetSize
		);
	};
}