#pragma once

#include <string>

#include "../../../Mathematic/Geometry/Position.h"
#include "../../../Mathematic/Geometry/IndexPosition.h"
#include "../../../Utility/List.hpp"

namespace BF
{
	struct OBJElement
	{
	public:
		std::string Name;

		unsigned int MaterialID = -1;
		float Smoothing;

		// List of geometric vertices, with (x, y, z [,w]) coordinates, w is optional and defaults to 1.
		List<Position> VertexPositionList;

		// List of texture coordinates, in (u, [,v ,w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0.
		List<Point> TextureCoordinateList;

		// List of vertex normals in (x,y,z) form; normals might not be unit vectors.
		List<Position> VertexNormalPositionList;

		// Parameter space vertices in ( u [,v] [,w] ) form; free form geometry statement.
		List<Position> VertexParameterList;

		// Polygonal face element.
		List<IndexPosition> FaceElementList;

		OBJElement();
	};
}