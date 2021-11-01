#pragma once

#include "GravityField.h"
#include "../Geometry/Form/Cube.h"

namespace BF
{
	class GravityCube : public GravityField, public Cube
	{
		public:
		virtual bool IsColliding(Vector2<float> position) override;
		virtual bool IsColliding(Vector3<float> position) override;
	};
}