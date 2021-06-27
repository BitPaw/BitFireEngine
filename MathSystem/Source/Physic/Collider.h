#pragma once

#include "../../../MathSystem/Source/Geometry/Point.hpp"
#include "../../../MathSystem/Source/Geometry/Position.hpp"

namespace BF
{
	class Collider
	{
		virtual bool IsColliding(Point<float> position) = 0;
		virtual bool IsColliding(Position<float> position) = 0;
	};
}