#include "CubeModel.h"

std::vector<unsigned int> GenerateDrawOrder(int vertexAmount)
{
	std::vector<unsigned int> drawOrder;
	bool bmode = false;
	unsigned int vertexOffset = 0;

	while (vertexAmount > 0)
	{
		if (bmode)
		{
			drawOrder.push_back(0 + vertexOffset);
			drawOrder.push_back(1 + vertexOffset);
			drawOrder.push_back(2 + vertexOffset);
		}
		else
		{
			drawOrder.push_back(2 + vertexOffset);
			drawOrder.push_back(3 + vertexOffset);
			drawOrder.push_back(0 + vertexOffset);
			vertexOffset++;
		}
	
		vertexAmount = vertexAmount - 3;

		bmode = !bmode;
	}

	return drawOrder;
}

CubeModel::CubeModel()
{
	ModelName = "Cube";

	std::vector<Vertex> vertexList;
	std::vector<unsigned int>* drawOrder;// = Shape.GetDrawOrderSteps();

	std::vector<unsigned int> drod;// = GenerateDrawOrder(8);
	//vertexList.reserve(Shape.GetCornerPointsAmout());



	
	// BOT
	drod.push_back(0);
	drod.push_back(1);
	drod.push_back(2);

	drod.push_back(2);
	drod.push_back(3);
	drod.push_back(0);



	drod.push_back(1);
	drod.push_back(2);
	drod.push_back(6);
	
	drod.push_back(6);
	drod.push_back(5);
	drod.push_back(1);


	drod.push_back(2);
	drod.push_back(3);
	drod.push_back(7);

	drod.push_back(7);
	drod.push_back(6);
	drod.push_back(2);


	drod.push_back(3);
	drod.push_back(0);
	drod.push_back(4);

	drod.push_back(4);
	drod.push_back(7);
	drod.push_back(3);


	drod.push_back(4);
	drod.push_back(5);
	drod.push_back(6);

	drod.push_back(6);
	drod.push_back(7);
	drod.push_back(4);


	drod.push_back(0);
	drod.push_back(1);
	drod.push_back(5);

	drod.push_back(5);
	drod.push_back(4);
	drod.push_back(0);

	float pos = 0.5;

	A = Vertex(Position(-pos, -pos, -pos), RGBA(1, 0, 0), Point(0, 0));
	B = Vertex(Position(pos, -pos, -pos), RGBA(0, 0, 1), Point(1, 0));
	C = Vertex(Position(pos, -pos, pos), RGBA(0, 1, 0), Point(1, 1));
	D = Vertex(Position(-pos, -pos, pos), RGBA(1, 1, 0), Point(0, 1));

	E = Vertex(Position(-pos, pos, -pos), RGBA(0.5f, 0.25f, 0.25f), Point(1, 1));
	F = Vertex(Position(pos, pos, -pos), RGBA(1, 0, 1), Point(1, 1));
	G = Vertex(Position(pos, pos, pos), RGBA(0, 1, 1), Point(1, 1));
	H = Vertex(Position(-pos, pos, pos), RGBA(1, 1, 1), Point(1, 1));

	vertexList.push_back(A);
	vertexList.push_back(B);
	vertexList.push_back(C);
	vertexList.push_back(D);

	vertexList.push_back(E);
	vertexList.push_back(F);
	vertexList.push_back(G); 
	vertexList.push_back(H);


	//vertexList.push_back(Vertex(Position(Shape.A), RGBA(1, 0, 0), Point(0, 0)));
	//vertexList.push_back(Vertex(Position(Shape.B), RGBA(0, 0, 1), Point(1, 0)));
	//vertexList.push_back(Vertex(Position(Shape.C), RGBA(0, 1, 0), Point(1, 1)));
	//vertexList.push_back(Vertex(Position(Shape.D), RGBA(1, 1, 0), Point(0, 1)));

	Mesh mesh = Mesh(vertexList, drod, 3);



	mesh.CalculateNormals();

	MeshListLengh++;
	MeshList = new Mesh[1]{ mesh };


	UpdateRenderSystemLink();

}