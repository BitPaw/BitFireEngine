#pragma once

#include "../Physic/CollisionListener.h"
#include "../Physic/Collider.h"

#include <Graphic/Graphic.h>

namespace BF
{
	class Sign : /*public Sprite, */ public CollisionListener
	{
		public:
		bool Interactable;
		
		Sign()
		{
			Interactable = false;

			//OnCollisionCallBack = this;
		}


		void OnCollisionDetected(Collider* colliderPrimary, Collider* colliderSecondary)
		{
			Interactable = true;
		}
	};
}