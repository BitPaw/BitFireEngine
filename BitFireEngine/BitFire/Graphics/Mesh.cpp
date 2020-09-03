#include "Mesh.h"


void Mesh::GenerateArrayData()
{
	// Indice Data List - Creation
	{
		unsigned int indiceListSize = IndexListSize;

		_indiceData.Data = new unsigned int[indiceListSize];
		_indiceData.Lengh = indiceListSize;
		_indiceData.SizeInBytes = indiceListSize * sizeof(unsigned int);

		for (unsigned int i = 0; i < indiceListSize; i++)
		{
			_indiceData.Data[i] = IndexList[i];
		}
	}

	// Vertex
	{
		unsigned int dynamicIndex = 0;
		unsigned int blockSize = (4 + 4 + 4 + 2);

		_vertexData.Lengh = VertexListSize * blockSize;
		_vertexData.Data = new float[_vertexData.Lengh];
		_vertexData.SizeInBytesSingleBlock = sizeof(float) * blockSize;
		_vertexData.SizeInBytesDataBlock = sizeof(float) * _vertexData.Lengh;

		float* vList = _vertexData.Data;

		//printf("Creating Data Array. Length=%u\n", _vertexData.Lengh);

		for (unsigned int i = 0; i < VertexListSize; i++)
		{
			Vertex* vertex = &VertexList[i];
			Position* position = &vertex->CurrentPosition;
			Position* normal = &vertex->NormalizedPosition;
			Point* point = &vertex->TexturePoint;
			RGBA* color = &vertex->Color;

			//printf("[ID=%u]\n", i);
			//printf("Position: <%.2f | %.2f | %.2f>\n", position->X, position->Y, position->Z);
			//printf("Normal  : <%.2f | %.2f | %.2f>\n", normal->X, normal->Y, normal->Z);
			//printf("Point   : <%.2f | %.2f>\n", point->X, point->Y);
			//printf("Color   : <%.2f | %.2f | %.2f | %.2f>\n\n", color->Red, color->Green, color->Blue, color->Alpha);

			// positions
			vList[dynamicIndex++] = position->X;
			vList[dynamicIndex++] = position->Y;
			vList[dynamicIndex++] = position->Z;
			vList[dynamicIndex++] = 1; // W

			// Normals
			vList[dynamicIndex++] = normal->X;
			vList[dynamicIndex++] = normal->Y;
			vList[dynamicIndex++] = normal->Z;
			vList[dynamicIndex++] = 1; // W

			// Color
			vList[dynamicIndex++] = color->Red;
			vList[dynamicIndex++] = color->Green;
			vList[dynamicIndex++] = color->Blue;
			vList[dynamicIndex++] = color->Alpha;

			// Texture
			vList[dynamicIndex++] = point->X;
			vList[dynamicIndex++] = point->Y;
		}
	}
	/*
	for (size_t i = 0; i < _vertexData.Lengh; i++)
	{
		//printf("[ID=%u/%u] %f\n", i, _vertexData.Lengh ,_vertexData.Data[i]);
	}
	*/
}

Mesh::Mesh()
{
	Dimension = 0;
	VertexListSize = 0;
	IndexListSize = 0;

	VertexList = nullptr;
	IndexList = nullptr;
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, unsigned char dimension)
{
	Dimension = dimension;
	VertexListSize = vertices.size();
	IndexListSize = indices.size();

	VertexList = new Vertex[VertexListSize];
	IndexList = new unsigned int[IndexListSize];

	for (unsigned int i = 0; i < VertexListSize; i++)
	{
		VertexList[i] = vertices.at(i);
	}

	for (unsigned int i = 0; i < IndexListSize; i++)
	{
		IndexList[i] = indices.at(i);
	}
}

Mesh::~Mesh()
{
	/*
	size_t size;

	//delete[] _vertexData.Data;
	//delete[] _indiceData.Data;

	// Delete vertices
	//size = Vertices.size();

	for (size_t i = 0; i < size; i++)
	{
		//delete &Vertices[i];
	}

	//size = Indices.size();

	for (size_t i = 0; i < size; i++)
	{
		//delete &Indices[i];
	}
	*/
}

void Mesh::CalculateNormals()
{
	unsigned int size = IndexListSize;

	for (unsigned int i = 0; i < size; i += 3)
	{
		unsigned int indexA = IndexList[i];
		unsigned int indexB = IndexList[i + 1];
		unsigned int indexC = IndexList[i + 2];

		Vertex* vertexA = &VertexList[indexA];
		Vertex* vertexB = &VertexList[indexB];
		Vertex* vertexC = &VertexList[indexC];

		Position* aPos = &vertexA->CurrentPosition;
		Position* bPos = &vertexB->CurrentPosition;
		Position* cPos = &vertexC->CurrentPosition;

		glm::vec3 a(aPos->X, aPos->Y, aPos->Z);
		glm::vec3 b(bPos->X, bPos->Y, bPos->Z);
		glm::vec3 c(cPos->X, cPos->Y, cPos->Z);

		glm::vec3 nA = glm::cross(a, b);
		glm::vec3 nB = glm::cross(b, c);
		glm::vec3 nC = glm::cross(c, a);

		vertexA->NormalizedPosition = Position(nA.x, nA.y, nA.z);
		vertexB->NormalizedPosition = Position(nB.x, nB.y, nB.z);
		vertexC->NormalizedPosition = Position(nC.x, nC.y, nC.z);
	}
}

ListFloat* Mesh::GetVertexData()
{
	return &_vertexData;
}

ListUInt* Mesh::GetIndiceData()
{
	return &_indiceData;
}