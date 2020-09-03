#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::VertexBuffer(Mesh* mesh)
{
	ChangeMesh(mesh);
}

VertexBuffer::~VertexBuffer()
{
	const unsigned int amount = 1;

	glDeleteBuffers(amount, &_bufferID);
}

void VertexBuffer::BindBuffer()
{
	glBindVertexArray(_vertexArrayObjectID);
}

void VertexBuffer::UnBindBuffer()
{
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::ChangeMesh(Mesh* mesh)
{
	const unsigned int dimension = 4;//mesh->Dimension;
	const unsigned int sizeOfVertex = sizeof(float) * dimension;//sizeof(Vertex);
	const unsigned int size = mesh->AmountOfVertexes * sizeOfVertex;
	const unsigned int amount = 1;

	const unsigned int vertexSizeSingle = sizeof(float) * (dimension + 4);
	const unsigned int vertexSizeList = vertexSizeSingle * mesh->AmountOfVertexes;

	float* vertexData = mesh->GetVertexData();

	glGenVertexArrays(amount, &_vertexArrayObjectID);
	glBindVertexArray(_vertexArrayObjectID);

	glGenBuffers(amount, &_bufferID); // Get BufferID
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID); // Select Buffer
	glBufferData(GL_ARRAY_BUFFER, vertexSizeList, vertexData, GL_STATIC_DRAW); // 

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, vertexSizeSingle, 0);

	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSizeSingle, (void*)(4 * sizeof(float)));
	/*
	// Color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSizeSingle, (void*)(8 * sizeof(float)));

	// TextureCoordinate
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexSizeSingle, (void*)(12 * sizeof(float)))*/;

	glGenBuffers(amount, &_indiceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indiceBuffer); // Select
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->IndiceListSize * sizeof(unsigned int), mesh->Indices, GL_STATIC_DRAW);

	UnBindBuffer();
}
