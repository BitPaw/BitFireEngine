#include "Vertex.h"

Vertex::Vertex() : Vertex(0, 0, 0)
{

}

Vertex::Vertex(float x, float y) : Vertex(x, y, 0)
{

}

Vertex::Vertex(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}
