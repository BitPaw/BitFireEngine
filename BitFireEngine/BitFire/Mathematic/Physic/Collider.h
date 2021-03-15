#pragma once

#include "../../Mathematic/Geometry/Point.hpp"
#include "../../Mathematic/Geometry/Position.hpp"

namespace BF
{
	class Collider
	{
		virtual bool IsColliding(Point<float> position) = 0;
		virtual bool IsColliding(Position<float> position) = 0;
	};
}