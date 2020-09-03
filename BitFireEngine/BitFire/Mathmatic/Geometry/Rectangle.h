#pragma once

#include "Vertex.h"
#include "RenderObject.h"

class Rectangle : public RenderObject
{
public:
	Rectangle();
	Rectangle(float xA, float yA, float xB, float yB, float xC, float yC, float xD, float yD);
	Rectangle(Vertex a, Vertex b, Vertex c, Vertex d);
	Rectangle(Vertex* vertex, unsigned int nr);
};