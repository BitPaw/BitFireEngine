#pragma once

#include "GravityField.h"
#include "../Geometry/Matrix4x4.hpp"

namespace BF
{
	class GravityCube : public GravityField
	{
		public:
		virtual bool IsColliding(Vector2<float> position) override;
		virtual bool IsColliding(Vector3<float> position) override;

		bool IsColliding
		(
			Vector3<float> ancerPosition,
			Vector3<float> ancerSize,
			Vector3<float> targetPosition,
			Vector3<float> targetSize
		);
	};
}