#include "Vertex.h"

Vertex::Vertex() : Vertex(nullptr, nullptr, nullptr, nullptr)
{

}

Vertex::Vertex(Position* currentPosition) : Vertex(currentPosition, nullptr, nullptr, nullptr)
{

}

Vertex::Vertex(Position* currentPosition, Position* normalizedPosition, Position* color, Point* texturePoint)
{
	CurrentPosition = currentPosition;
	NormalizedPosition = normalizedPosition;
	Color = color;
	TexturePoint = texturePoint;
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