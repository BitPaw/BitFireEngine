#include "Vertex.h"

Vertex::Vertex() : Vertex(Position())
{

}

Vertex::Vertex(Position currentPosition) : Vertex(currentPosition, 0)
{

}

Vertex::Vertex(Position currentPosition, const unsigned int colorID)
{
	CurrentPosition = currentPosition;
	ColorID = colorID;
}