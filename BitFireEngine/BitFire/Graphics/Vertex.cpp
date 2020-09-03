#include "Vertex.h"

Vertex::Vertex() : Vertex(Position())
{

}

Vertex::Vertex(Position currentPosition) : Vertex(currentPosition, Position(), RGBA(), Point())
{

}

Vertex::Vertex(Position currentPosition, RGBA color) : Vertex(currentPosition, Position(), color, Point(currentPosition.X, currentPosition.Y))
{
	
}

Vertex::Vertex(Position currentPosition, RGBA color, Point texturePoint) : Vertex(currentPosition, Position(), color, texturePoint)
{

}

Vertex::Vertex(Position currentPosition, Position normalizedPosition, RGBA color, Point texturePoint)
{
	CurrentPosition = currentPosition;
	NormalizedPosition = normalizedPosition;
	Color = color;
	TexturePoint = texturePoint;
}