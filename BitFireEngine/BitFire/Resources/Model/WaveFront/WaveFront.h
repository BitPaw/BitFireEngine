#pragma once

#include <string>
#include <vector>

#include "../../../Mathematic/Geometry/Position.h"
#include "../../../Mathematic/Geometry/IndexPosition.h"

/// <summary>
/// [.OBJ] Wavefront - 3D model format
/// </summary>
class WaveFront
{
public:
	std::string Name;

	// List of geometric vertices, with (x, y, z [,w]) coordinates, w is optional and defaults to 1.
	std::vector<Position> VectorPositions;

	// List of texture coordinates, in (u, [,v ,w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0.
	std::vector<Point> TextureCoordinates;

	// List of vertex normals in (x,y,z) form; normals might not be unit vectors.
	std::vector<Position> VectorNormalPositions;
	
	// Parameter space vertices in ( u [,v] [,w] ) form; free form geometry statement.
	std::vector<Position> VectorParameter;

	// Polygonal face element.
	std::vector<IndexPosition> FaceElements;
};