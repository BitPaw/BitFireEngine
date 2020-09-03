#pragma once

#include <string>
#include "Mesh.h"
#include "Point.h"
#include "../../IO/FileLoader.h"


class RenderObject
{
protected:
	//Mesh* _mesh;


public:	
	RenderObject();
	RenderObject(const char* name, Mesh* mesh);
	~RenderObject();

	const char* Name;
	Mesh* _mesh;
	//Mesh GetRenderMesh();

	void SetName(const char* name);
};

