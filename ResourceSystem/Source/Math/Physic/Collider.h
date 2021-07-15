#pragma once

#include "../Geometry/Vector2.hpp"
#include "../Geometry/Vector3.hpp"

namespace BF
{
	class Collider
	{
		virtual bool IsColliding(Point<float> position) = 0;
		virtual bool IsColliding(Position<float> position) = 0;
	};
}