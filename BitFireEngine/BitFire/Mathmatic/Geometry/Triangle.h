#pragma once

#include "Mesh.h"
#include "RenderObject.h"

class Triangle : public RenderObject
{
public:
	Triangle();
	Triangle(float xA, float yA, float xB, float yB, float xC, float yC);
	Triangle(Vertex a, Vertex b, Vertex c);
	Triangle(Vertex* vertexList);
};

