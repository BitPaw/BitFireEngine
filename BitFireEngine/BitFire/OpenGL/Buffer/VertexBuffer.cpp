#include "VertexBuffer.h"
#include <stdio.h>

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
	ListFloat* vertexData = mesh->GetVertexData();
	ListUInt* indiceData = mesh->GetIndiceData();
		
	if (vertexData->Lengh == 0 || indiceData->Lengh == 0)
	{
		throw std::exception("Invalid Mesh Data");
	}

	/*
	for (size_t i = 0; i < vertexData->Lengh; i++)
	{
		Vertex* vertex = vertexData->Data[i];

		Position* pos = &vertex->NormalizedPosition;


		printf("%f. %f, %f\n", pos->X, pos->Y, pos->Z);
	}*/

	vertexData = mesh->GetVertexData();

	glGenVertexArrays(1, &_vertexArrayObjectID);
	glBindVertexArray(_vertexArrayObjectID);

	glGenBuffers(1, &_bufferID); // Get BufferID
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID); // Select Buffer
	glBufferData(GL_ARRAY_BUFFER, vertexData->SizeInBytesDataBlock, vertexData->Data, GL_STATIC_DRAW); // 


	//(void*)(4 * sizeof(float)

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertexData->SizeInBytesSingleBlock, 0);

	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexData->SizeInBytesSingleBlock, (void*)(sizeof(float) * (4)));
	
	// Color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, vertexData->SizeInBytesSingleBlock, (void*)(sizeof(float) * (8)));

	
	// TextureCoordinate
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, vertexData->SizeInBytesSingleBlock, (void*)(sizeof(float) * (12)));

	glGenBuffers(1, &_indiceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indiceBuffer); // Select
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceData->SizeInBytes, indiceData->Data, GL_STATIC_DRAW);

	UnBindBuffer();
}
