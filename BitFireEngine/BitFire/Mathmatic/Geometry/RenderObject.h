#pragma once

#include "Mesh.h"

class RenderObject
{
protected:
	//Mesh* _mesh;
	RenderObject();
	RenderObject(Mesh* mesh);
	~RenderObject();

public:	
	Mesh* _mesh;
	//Mesh GetRenderMesh();
};

