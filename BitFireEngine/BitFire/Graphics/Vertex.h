#pragma once

#include <GLM/glm.hpp>
#include <GLM/geometric.hpp>

#include "../Mathematic/Geometry/Position.h"
#include "../Color/RGBA.h"

class Vertex
{
public:
	Position CurrentPosition;
	unsigned int ColorID;

	Vertex();
	Vertex(Position currentPosition);
	Vertex(Position currentPosition, const unsigned int colorID);
};