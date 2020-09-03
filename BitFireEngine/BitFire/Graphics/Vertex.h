#pragma once

#include <GLM/glm.hpp>
#include <GLM/geometric.hpp>

#include "../Mathematic/Geometry/Position.h"
#include "../Color/RGBA.h"

class Vertex
{
public:
	Position CurrentPosition;
	Position NormalizedPosition;
	RGBA Color;
	Point TexturePoint;

	Vertex();
	Vertex(Position currentPosition);
	Vertex(Position currentPosition, RGBA color);
	Vertex(Position currentPosition, RGBA color, Point texturePoint);
	Vertex(Position currentPosition, Position normalizedPosition, RGBA color, Point texturePoint);
};