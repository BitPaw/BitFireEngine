#pragma once

#include "../../SystemResource/Source/Game/Sprite.h"
#include "../../SystemResource/Source/Math/Physic/CollisionListener.h"

namespace BF
{
	class Sign : public Sprite, public CollisionListener
	{
		public:
		bool Interactable;
		
		Sign()
		{
			Interactable = false;

			OnCollisionCallBack = this;
		}


		void OnCollisionDetected(Collider* colliderPrimary, Collider* colliderSecondary)
		{
			Interactable = true;
		}
	};
}