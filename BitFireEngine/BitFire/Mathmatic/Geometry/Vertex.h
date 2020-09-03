#pragma once

#include "Position.h"

class Vertex
{
public:
	Position* CurrentPosition;
	Position* NormalizedPosition;
	Point* Color;

	Vertex();
	Vertex(Position* currentPosition);
	Vertex(Position* currentPosition, Position* normalizedPosition, Point* color);
	~Vertex();
};