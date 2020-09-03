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
	unsigned char Dimension;

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	Mesh();
	Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, unsigned char dimension);
	~Mesh();

	void CalculateNormals();
	void GenerateArrayData();

	ListFloat* GetVertexData();
	ListUInt* GetIndiceData();
};

