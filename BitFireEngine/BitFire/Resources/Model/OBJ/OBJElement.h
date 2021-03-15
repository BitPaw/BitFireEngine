#pragma once

#include "../../../Utility/ASCIIString.h"
#include "../../../Utility/List.hpp"
#include "../../../Mathematic/Geometry/Position.hpp"

namespace BF
{
	struct OBJElement
	{
		public:
		ASCIIString Name;

		unsigned int MaterialID = -1;
		float Smoothing;

		// List of geometric vertices, with (x, y, z [,w]) coordinates, w is optional and defaults to 1.
		List<Position<float>> VertexPositionList;

		// List of texture coordinates, in (u, [,v ,w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0.
		List<Point<float>> TextureCoordinateList;

		// List of vertex normals in (x,y,z) form; normals might not be unit vectors.
		List<Position<float>> VertexNormalPositionList;

		// Parameter space vertices in ( u [,v] [,w] ) form; free form geometry statement.
		List<Position<float>> VertexParameterList;

		// Polygonal face element.
		List<Position<unsigned int>> FaceElementList;

		OBJElement();
	};
}