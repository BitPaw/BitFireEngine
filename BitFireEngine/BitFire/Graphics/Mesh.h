#pragma once

#include <vector>
#include <iostream>

#include "Vertex.h"

#include "../Utility/ListFloat.h"
#include "../Utility/ListUInt.h"

class Mesh
{
private:
	ListFloat _vertexData;
	ListUInt _indiceData;


public:
	unsigned int StartIndex;

	unsigned char Dimension;


	// Raw - Data-----------------------------
	Vertex* VertexList;
	unsigned int VertexListSize;

	unsigned int* IndexList;
	unsigned int IndexListSize;
	//------------------------------------------

	Mesh();
	Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, unsigned char dimension);
	~Mesh();

	void CalculateNormals();
	void GenerateArrayData();

	ListFloat* GetVertexData();
	ListUInt* GetIndiceData();
};