#include "Mesh.h"
#include "../Interpolate.h"

bool rising = true;
float wFactor;

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
}

Mesh::~Mesh()
{
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
	unsigned int dynamicIndex = 0;
	unsigned int colorValues = 4;
	Dimension = 4;

	float* data = new float[AmountOfVertexes * (Dimension + colorValues)];
	
	for (unsigned int i = 0; i < AmountOfVertexes; i++)
	{
		Vertex* vertex = &VertexList[i];

		data[dynamicIndex++] = vertex->CurrentPosition->X;
		data[dynamicIndex++] = vertex->CurrentPosition->Y;

		if (Dimension >= 3)
		{
			data[dynamicIndex++] = 0;// vertex->CurrentPosition->Z;
		}	

		if (Dimension >= 4)
		{
			data[dynamicIndex++] = 1; // W
		}

		if (vertex->Color != nullptr)
		{
			data[dynamicIndex++] = vertex->Color->X; // Red
			data[dynamicIndex++] = vertex->Color->Y; // Green
			data[dynamicIndex++] = vertex->Color->Z; // Blue
			data[dynamicIndex++] = 1; // Alpha
		}
		else
		{
			data[dynamicIndex++] = 1; // Red
			data[dynamicIndex++] = 1; // Green
			data[dynamicIndex++] = 1; // Blue
			data[dynamicIndex++] = 1; // Alpha
		}

	


		/*

		switch (i)
		{
		case 0:
			data[dynamicIndex++] = 1; // Red
			data[dynamicIndex++] = 0; // Green
			data[dynamicIndex++] = 0; // Blue
			data[dynamicIndex++] = 1; // Alpha
			break;

		case 1:
			data[dynamicIndex++] = 0; // Red
			data[dynamicIndex++] = 1; // Green
			data[dynamicIndex++] = 0; // Blue
			data[dynamicIndex++] = 1; // Alpha
			break;

		case 2:
			data[dynamicIndex++] = 0; // Red
			data[dynamicIndex++] = 0; // Green
			data[dynamicIndex++] = 1; // Blue
			data[dynamicIndex++] = 1; // Alpha
			break;

		case 3:
			data[dynamicIndex++] = 1; // Red
			data[dynamicIndex++] = 1; // Green
			data[dynamicIndex++] = 0; // Blue
			data[dynamicIndex++] = 1; // Alpha
			break;

		}
		*/

		//data[dynamicIndex++] = 1; // Red
		//data[dynamicIndex++] = 0; // Green
		//data[dynamicIndex++] = 0; // Blue
		//data[dynamicIndex++] = 1; // Alpha
	}
	

	return data;
}

unsigned int* Mesh::GetIndices()
{
	return Indices;
}