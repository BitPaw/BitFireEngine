#pragma once

#include "../../../MathSystem/Source/Geometry/Position.hpp"

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