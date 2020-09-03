#pragma once

#include <GLEW/glew.h>
#include "../../Graphics/Mesh.h"

class VertexBuffer
{
private:
	unsigned int _bufferID;
	unsigned int _indiceBuffer;
	unsigned int _vertexArrayObjectID;

public:

	VertexBuffer();
	VertexBuffer(Mesh* mesh);
	~VertexBuffer();

	void BindBuffer();
	void UnBindBuffer();

	void ChangeMesh(Mesh* mesh);
};