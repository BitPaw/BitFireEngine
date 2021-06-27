#include "Vertex.h"

BF::Vertex::Vertex() : Vertex(Position<float>())
{

}

BF::Vertex::Vertex(Position<float> currentPosition) : Vertex(currentPosition, 0)
{

}

BF::Vertex::Vertex(Position<float> currentPosition, const unsigned int colorID)
{
	CurrentPosition = currentPosition;
	ColorID = colorID;
}