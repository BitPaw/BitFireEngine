#include "RectangleModel.h"

BF::RectangleModel::RectangleModel()
{
	ModelName = "Rectangle";
	MeshList.ReSize(1);

	Mesh* mesh = &MeshList[0];

	// Vertex
	{
		mesh->VertexList.ReSize(Shape.CornerPoints);
		List<Vertex>* vertexList = &mesh->VertexList;

		A = Vertex(Shape.A, 0);
		B = Vertex(Shape.B, 1);
		C = Vertex(Shape.C, 2);
		D = Vertex(Shape.D, 3);

		(*vertexList)[0] = A;
		(*vertexList)[1] = B;
		(*vertexList)[2] = C;
		(*vertexList)[3] = D;
	}


	mesh->ColorList.ReSize(Shape.CornerPoints);
	mesh->ColorList[0] = RGBA(1, 0, 0);
	mesh->ColorList[1] = RGBA(0, 0, 1);
	mesh->ColorList[2] = RGBA(0, 1, 0);
	mesh->ColorList[3] = RGBA(0, 1, 1);

	// Positions
	{
		//Point(0, 0));
		//Point(1, 0));
		//Point(1, 1));
		//Point(0, 1));
	}

	List<MeshIndexData>* indexList = &mesh->IndexList;
	(*indexList).ReSize(6);

	(*indexList)[0] = MeshIndexData(0, 0, 0);
	(*indexList)[1] = MeshIndexData(1, 0, 0);
	(*indexList)[2] = MeshIndexData(2, 0, 0);
	(*indexList)[3] = MeshIndexData(2, 0, 0);
	(*indexList)[4] = MeshIndexData(3, 0, 0);
	(*indexList)[5] = MeshIndexData(0, 0, 0);

	//CalculateNormalVectors();
	UpdateGlobalMesh();

	UpdateRenderSystemLink();
}