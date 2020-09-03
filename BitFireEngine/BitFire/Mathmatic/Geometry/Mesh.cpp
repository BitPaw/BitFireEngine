#include "Mesh.h"

Mesh::Mesh() : Mesh(nullptr, 0, nullptr, 0)
{

}

Mesh::Mesh(Vertex* vertexList, unsigned int nrVertexes, unsigned int* indices, unsigned int nrIndices)
{
	VertexList = vertexList;
	AmountOfVertexes = nrVertexes;
	Indices = indices;
	AmountOfIndices = nrIndices;
}

Mesh::~Mesh()
{
	for (unsigned int i = 0; i < AmountOfVertexes; i++)
	{
		delete &VertexList[i];
	}

	for (unsigned int i = 0; i < AmountOfIndices; i++)
	{
		delete &Indices[i];
	}
}

float* Mesh::GetVertexData()
{
	unsigned int dynamicIndex = 0;
	float* data = new float[AmountOfVertexes * 2];

	for (unsigned int i = 0; i < AmountOfVertexes; i++)
	{
		Vertex x = VertexList[i];

		data[dynamicIndex++] = x.X;
		data[dynamicIndex++] = x.Y;
	}

	return data;
}

unsigned int* Mesh::GetIndices()
{
	return Indices;
}