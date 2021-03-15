#pragma once

#include <glm/glm.hpp>
#include <glm/geometric.hpp>

#include "../../Mathematic/Geometry/Position.hpp"

namespace BF
{
	class Vertex
	{
		public:
		Position<float> CurrentPosition;
		unsigned int ColorID;

		Vertex();
		Vertex(Position<float> currentPosition);
		Vertex(Position<float> currentPosition, const unsigned int colorID);
	};
}