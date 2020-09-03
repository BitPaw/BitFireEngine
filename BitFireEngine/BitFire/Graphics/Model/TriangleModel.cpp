#include "TriangleModel.h"

TriangleModel::TriangleModel()
{
	ModelName = "Triangle";

	std::vector<Vertex> vertexList;
	std::vector<unsigned int>* drawOrder = Shape.GetDrawOrderSteps();

	vertexList.reserve(Shape.GetCornerPointsAmout());

	vertexList.push_back(Vertex(Position(Shape.A), RGBA(1, 0, 0), Point(0, 0)));
	vertexList.push_back(Vertex(Position(Shape.B), RGBA(0, 1, 0), Point(0.5f, 1)));
	vertexList.push_back(Vertex(Position(Shape.C), RGBA(0, 0, 1), Point(1, 0)));

	Mesh mesh = Mesh(vertexList, *drawOrder, 2);
	mesh.CalculateNormals();

	VertexMeshList.push_back(mesh);
}