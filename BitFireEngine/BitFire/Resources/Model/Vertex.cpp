#include "Vertex.h"

BF::Vertex::Vertex() : Vertex(Position())
{

}

BF::Vertex::Vertex(Position currentPosition) : Vertex(currentPosition, 0)
{

}

BF::Vertex::Vertex(Position currentPosition, const unsigned int colorID)
{
	CurrentPosition = currentPosition;
	ColorID = colorID;
}