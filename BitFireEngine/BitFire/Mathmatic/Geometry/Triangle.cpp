#include "Triangle.h"

Triangle::Triangle() : Triangle(-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f)
{
	
}

Triangle::Triangle(float xA, float yA, float xB, float yB, float xC, float yC) : Triangle(Vertex(new Position(xA, yA)), Vertex(new Position(xB, yB)), Vertex(new Position(xC, yC)))
{
	
}

Triangle::Triangle(Vertex a, Vertex b, Vertex c) : Triangle(new Vertex[3]{ a, b, c })
{

}

Triangle::Triangle(Vertex* vertexList) : RenderObject("Triangle", new Mesh(vertexList, 3, new unsigned int[3] {0,1,2}, 3,2))
{

}
