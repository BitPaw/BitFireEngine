#include "Rectangle.h"

Rectangle::Rectangle() : Rectangle(-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f)
{

}

Rectangle::Rectangle(float xA, float yA, float xB, float yB, float xC, float yC, float xD, float yD) : Rectangle(Vertex(xA, yA), Vertex(xB, yB), Vertex(xC, yC), Vertex(xD, yD))
{

}

Rectangle::Rectangle(Vertex a, Vertex b, Vertex c, Vertex d) : Rectangle(new Vertex[4]{a, b, c, d}, 4)
{

}

Rectangle::Rectangle(Vertex* vertex, unsigned int nr) : RenderObject("Rectangle", new Mesh(vertex, nr, new unsigned int[6] { 0, 1, 2, 2, 3, 0 }, 6))
{

}