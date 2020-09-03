#pragma once

#include "Vertex.h"

class Mesh
{
private:
	float* _vertexData;

	void GenerateVertexData();

public:
	unsigned char Dimension;

	Vertex* VertexList;
	unsigned int VertexListSize;
	unsigned int AmountOfVertexes;

	unsigned int* Indices;
	unsigned int IndiceListSize;

	Mesh();
	Mesh(Vertex* vertexList, unsigned int nrVertexes, unsigned int* Indices, unsigned int nrIndices, unsigned char dimension);
	~Mesh();

	float* GetVertexData();
	unsigned int* GetIndices();
};

