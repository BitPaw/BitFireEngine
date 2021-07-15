#pragma once

#include "../Math/Geometry/Vector3.hpp"

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