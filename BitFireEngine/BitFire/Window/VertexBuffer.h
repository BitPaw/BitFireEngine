#pragma once

#include <GLEW/glew.h>
#include "../Mathmatic/Geometry/Vertex.h"
#include "../Mathmatic/Geometry/Mesh.h"

class VertexBuffer
{
private:
	unsigned int _bufferID;
	unsigned int _indiceBuffer;
	unsigned int _vertexArrayObjectID;

public:

	VertexBuffer(Mesh* mesh);
	~VertexBuffer();

	void BindBuffer();
	void UnBindBuffer();
};