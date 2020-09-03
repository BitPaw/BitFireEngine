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

BF::CubeModel::CubeModel()
{	
	ModelName = "Cube";
	MeshList.ReSize(1);

	Mesh* mesh = &MeshList[0];


	// Vertex
	{
		float pos = 0.5;

		mesh->VertexList.ReSize(8);
		List<Vertex>* vertexList = &mesh->VertexList;
	
		A = Vertex(Position(-pos, -pos, -pos), 0);
		B = Vertex(Position(pos, -pos, -pos), 1);
		C = Vertex(Position(pos, -pos, pos), 2);
		D = Vertex(Position(-pos, -pos, pos), 3);
		E = Vertex(Position(-pos, pos, -pos), 4);
		F = Vertex(Position(pos, pos, -pos), 5);
		G = Vertex(Position(pos, pos, pos), 6);
		H = Vertex(Position(-pos, pos, pos), 7);

		(*vertexList)[0] = A;
		(*vertexList)[1] = B;
		(*vertexList)[2] = C;
		(*vertexList)[3] = D;

		(*vertexList)[4] = E;
		(*vertexList)[5] = F;
		(*vertexList)[6] = G;
		(*vertexList)[7] = H;
	}


	mesh->ColorList.ReSize(8);
	mesh->ColorList[0] = RGBA(1, 0, 0);
	mesh->ColorList[1] = RGBA(0, 0, 1);
	mesh->ColorList[2] = RGBA(0, 1, 0);
	mesh->ColorList[3] = RGBA(1, 1, 0);
	mesh->ColorList[4] = RGBA(1, 0, 1);
	mesh->ColorList[5] = RGBA(0.25f, 0.25f, 0.25f);
	mesh->ColorList[6] = RGBA(0, 1, 1);
	mesh->ColorList[7] = RGBA(1, 1, 1);


	// Positions
	{
	

	

		//Point(0, 0));
		//Point(1, 0));
		//Point(1, 1));
		//Point(0, 1));

		
		
	
	}


	List<MeshIndexData>* indexList = &mesh->IndexList;
	(*indexList).ReSize(36);

	(*indexList)[0] = MeshIndexData(0, 0, 0);
	(*indexList)[1] = MeshIndexData(1, 0, 0);
	(*indexList)[2] = MeshIndexData(2, 0, 0);

	(*indexList)[3] = MeshIndexData(2, 0, 0);
	(*indexList)[4] = MeshIndexData(3, 0, 0);
	(*indexList)[5] = MeshIndexData(0, 0, 0);

	(*indexList)[6] = MeshIndexData(1, 0, 0);
	(*indexList)[7] = MeshIndexData(2, 0, 0);
	(*indexList)[8] = MeshIndexData(6, 0, 0);

	(*indexList)[9] = MeshIndexData(6, 0, 0);
	(*indexList)[10] = MeshIndexData(5, 0, 0);
	(*indexList)[11] = MeshIndexData(1, 0, 0);

	(*indexList)[12] = MeshIndexData(2, 0, 0);
	(*indexList)[13] = MeshIndexData(3, 0, 0);
	(*indexList)[14] = MeshIndexData(7, 0, 0);

	(*indexList)[15] = MeshIndexData(7, 0, 0);
	(*indexList)[16] = MeshIndexData(6, 0, 0);
	(*indexList)[17] = MeshIndexData(2, 0, 0);

	(*indexList)[18] = MeshIndexData(3, 0, 0);
	(*indexList)[19] = MeshIndexData(0, 0, 0);
	(*indexList)[20] = MeshIndexData(4, 0, 0);

	(*indexList)[21] = MeshIndexData(4, 0, 0);
	(*indexList)[22] = MeshIndexData(7, 0, 0);
	(*indexList)[23] = MeshIndexData(3, 0, 0);

	(*indexList)[24] = MeshIndexData(4, 0, 0);
	(*indexList)[25] = MeshIndexData(5, 0, 0);
	(*indexList)[26] = MeshIndexData(6, 0, 0);

	(*indexList)[27] = MeshIndexData(6, 0, 0);
	(*indexList)[28] = MeshIndexData(7, 0, 0);
	(*indexList)[29] = MeshIndexData(4, 0, 0);

	(*indexList)[30] = MeshIndexData(0, 0, 0);
	(*indexList)[31] = MeshIndexData(1, 0, 0);
	(*indexList)[32] = MeshIndexData(5, 0, 0);

	(*indexList)[33] = MeshIndexData(5, 0, 0);
	(*indexList)[34] = MeshIndexData(4, 0, 0);
	(*indexList)[35] = MeshIndexData(0, 0, 0);

	CalculateNormalVectors();
	UpdateGlobalMesh();

	UpdateRenderSystemLink();
}