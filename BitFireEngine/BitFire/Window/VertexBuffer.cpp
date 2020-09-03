#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Mesh* mesh)
{
	const unsigned int dimension = 4;// mesh->Dimension;
	const unsigned int sizeOfVertex = sizeof(float) * dimension*4;//sizeof(Vertex);
	const unsigned int size = mesh->AmountOfVertexes * sizeOfVertex;
	const unsigned int amount = 1;

	glGenVertexArrays(amount, &_vertexArrayObjectID);
	glBindVertexArray(_vertexArrayObjectID);

	glGenBuffers(amount, &_bufferID); // Get BufferID
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID); // Select Buffer
	glBufferData(GL_ARRAY_BUFFER, size, mesh->GetVertexData(), GL_STATIC_DRAW); // 
			
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, sizeOfVertex, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	glGenBuffers(amount, &_indiceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indiceBuffer); // Select
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->IndiceListSize * sizeof(unsigned int), mesh->Indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
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
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
