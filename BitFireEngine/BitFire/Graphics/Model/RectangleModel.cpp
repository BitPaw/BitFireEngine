#include "RectangleModel.h"

BF::RectangleModel::RectangleModel()
{
	ModelName = "Rectangle";
	MeshList.ReSize(1);

	Mesh* mesh = &MeshList[0];
	/*
	mesh->VertexList.ReSize(4);
	mesh->VertexList[0] = Vertex(Position(Shape.A), RGBA(1, 0, 0), Point(0, 0));
	mesh->VertexList[1] = Vertex(Position(Shape.B), RGBA(0, 0, 1), Point(1, 0));
	mesh->VertexList[2] = Vertex(Position(Shape.C), RGBA(0, 1, 0), Point(1, 1));
	mesh->VertexList[3] = Vertex(Position(Shape.D), RGBA(1, 1, 0), Point(0, 1));

	std::vector<unsigned int>* drawOrder = Shape.GetDrawOrderSteps();

	mesh->IndexList.ReSize(drawOrder->size());

	for (size_t i = 0; i < drawOrder->size(); i++)
	{
		mesh->IndexList[i] = (*drawOrder).at(i);
	}

	ShouldBeRendered = true;

	*/

	UpdateRenderSystemLink();
}