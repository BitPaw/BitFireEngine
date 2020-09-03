#pragma once

#include "Vertex.h"

class Mesh
{
public:
	unsigned int AmountOfVertexes;
	unsigned int AmountOfIndices;

	Vertex* VertexList;
	unsigned int* Indices;

	Mesh();
	Mesh(Vertex* vertexList, unsigned int nrVertexes, unsigned int* Indices, unsigned int nrIndices);
	~Mesh();

	float* GetVertexData();
	unsigned int* GetIndices();
};

