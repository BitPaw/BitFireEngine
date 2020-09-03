#include "Vertex.h"

Vertex::Vertex()
{
	CurrentPosition = nullptr;
	NormalizedPosition = nullptr;
	Color = nullptr;
}

Vertex::Vertex(Position* currentPosition) : Vertex(currentPosition, nullptr, nullptr)
{

}

Vertex::Vertex(Position* currentPosition, Position* normalizedPosition, Point* color)
{
	CurrentPosition = currentPosition;
	NormalizedPosition = normalizedPosition;
	Color = color;
}

Vertex::~Vertex()
{
	if (CurrentPosition != nullptr)
	{
		//delete CurrentPosition;
	}

	if (NormalizedPosition != nullptr)
	{
		//delete NormalizedPosition;
	}

	if (Color != nullptr)
	{
		//delete Color;
	}
}