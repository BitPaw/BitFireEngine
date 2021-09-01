#pragma once

#include "../Math/Geometry/Vector3.hpp"

namespace BF
{
	class Vertex
	{
		public:
		Vector3<float> CurrentPosition;
		unsigned int ColorID;

		Vertex();
		Vertex(Vector3<float> currentPosition);
		Vertex(Vector3<float> currentPosition, const unsigned int colorID);
	};
}