#pragma once

#include "../../../Mathematic/Geometry/Position.h"
#include "../../../Mathematic/Geometry/IndexPosition.h"

struct WaveFrontElement
{
public:
	char* Name;

	float Smoothing;

	// List of geometric vertices, with (x, y, z [,w]) coordinates, w is optional and defaults to 1.
	Position* VertexPositionList;
	unsigned int VertexPositonListSize;

	// List of texture coordinates, in (u, [,v ,w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0.
	Point* TextureCoordinateList;
	unsigned int TextureCoordinateListSize;

	// List of vertex normals in (x,y,z) form; normals might not be unit vectors.
	Position* VertexNormalPositionList;
	unsigned int VertexNormalPositionListSize;

	// Parameter space vertices in ( u [,v] [,w] ) form; free form geometry statement.
	Position* VertexParameterList;
	unsigned int VertexParameterListSize;

	// Polygonal face element.
	IndexPosition* FaceElementList;
	unsigned int FaceElementListSize;

	WaveFrontElement();
	~WaveFrontElement();

	void Allocate();
	void Deallocate();
};