#pragma once

#include "Position.h"

class Vertex
{
public:
	Position* CurrentPosition;
	Position* NormalizedPosition;
	Position* Color;
	Point* TexturePoint;

	Vertex();
	Vertex(Position* currentPosition);
	Vertex(Position* currentPosition, Position* normalizedPosition, Position* color ,Point* texturePoint);
	~Vertex();
};