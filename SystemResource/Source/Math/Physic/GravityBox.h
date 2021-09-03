#pragma once

#include "GravityField.h"

namespace BF
{
	class GravityBox : public GravityField
	{
		public:
		virtual bool IsColliding(Vector2<float> position) override;
		virtual bool IsColliding(Vector3<float> position) override;
	};
}