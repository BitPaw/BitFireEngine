#pragma once

#include <glm/glm.hpp>
#include <glm/geometric.hpp>

#include "../../Mathematic/Geometry/Position.h"

namespace BF
{
	class Vertex
	{
		public:
		Position CurrentPosition;
		unsigned int ColorID;

		Vertex();
		Vertex(Position currentPosition);
		Vertex(Position currentPosition, const unsigned int colorID);
	};
}