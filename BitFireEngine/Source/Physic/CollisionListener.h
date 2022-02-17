#pragma once

namespace BF
{
	struct Collider;

	struct CollisionListener
	{
		bool Enable = true;
		virtual void OnCollisionDetected(Collider* colliderPrimary, Collider* colliderSecondary) = 0;
	};
}