#include "Mesh.h"
#include "../Interpolate.h"


void Mesh::GenerateVertexData()
{
	unsigned int dynamicIndex = 0;
	unsigned int colorValues = 4;
	unsigned int size = AmountOfVertexes * ((Dimension + colorValues) /*+ 4 + 2*/);
	Dimension = 4;

	_vertexData = new float[size];

	for (unsigned int i = 0; i < AmountOfVertexes; i++)
	{
		Vertex* vertex = &VertexList[i];

		// positions
		_vertexData[dynamicIndex++] = vertex->CurrentPosition->X;
		_vertexData[dynamicIndex++] = vertex->CurrentPosition->Y;
		_vertexData[dynamicIndex++] = vertex->CurrentPosition->Z;
		_vertexData[dynamicIndex++] = 1; // W
	
		// Normals
		//_vertexData[dynamicIndex++] = vertex->NormalizedPosition->X;
		//_vertexData[dynamicIndex++] = vertex->NormalizedPosition->Y;
		//_vertexData[dynamicIndex++] = vertex->NormalizedPosition->Z;
		//_vertexData[dynamicIndex++] = 1; // W

		// Color
		if (vertex->Color == nullptr)
		{
			_vertexData[dynamicIndex++] = 1; // Red
			_vertexData[dynamicIndex++] = 1; // Green
			_vertexData[dynamicIndex++] = 1; // Blue
			_vertexData[dynamicIndex++] = 1; // Alpha
		}
		else
		{			
			_vertexData[dynamicIndex++] = vertex->Color->X; // Red
			_vertexData[dynamicIndex++] = vertex->Color->Y; // Green
			_vertexData[dynamicIndex++] = vertex->Color->Z; // Blue
			_vertexData[dynamicIndex++] = 1; // Alpha
		}

		// Texture
		//_vertexData[dynamicIndex++] = 0;
		//_vertexData[dynamicIndex++] = 0;
	}
}

Mesh::Mesh() : Mesh(nullptr, 0, nullptr, 0, 0)
{

}

Mesh::Mesh(Vertex* vertexList, unsigned int nrVertexes, unsigned int* indices, unsigned int nrIndices, unsigned char dimension)
{
	Dimension = dimension;
	VertexList = vertexList;
	VertexListSize = nrVertexes * 3;
	AmountOfVertexes = nrVertexes;
	Indices = indices;
	IndiceListSize = nrIndices;

	GenerateVertexData();
}

Mesh::~Mesh()
{
	delete[] _vertexData;

	for (unsigned int i = 0; i < VertexListSize; i++)
	{
		delete &VertexList[i];
	}

	for (unsigned int i = 0; i < IndiceListSize; i++)
	{
		delete &Indices[i];
	}
}

float* Mesh::GetVertexData()
{
	return _vertexData;
}

unsigned int* Mesh::GetIndices()
{
	return Indices;
}