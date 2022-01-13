#pragma once

namespace BF
{
	struct Collider;

	struct CollisionListener
	{
		virtual void OnCollisionDetected(Collider* colliderPrimary, Collider* colliderSecondary) = 0;
	};
}