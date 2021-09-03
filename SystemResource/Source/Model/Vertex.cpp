#include "Vertex.h"

BF::Vertex::Vertex() : Vertex(Vector3<float>())
{

}

BF::Vertex::Vertex(Vector3<float> currentPosition) : Vertex(currentPosition, 0)
{

}

BF::Vertex::Vertex(Vector3<float> currentPosition, const unsigned int colorID)
{
	CurrentPosition = currentPosition;
	ColorID = colorID;
}