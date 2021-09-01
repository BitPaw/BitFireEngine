#pragma once

#include "../../Container/AsciiString.h"
#include "../../Container/List.hpp"
#include "../../../../ResourceSystem/Source/Math/Geometry/Vector2.hpp"
#include "../../../../ResourceSystem/Source/Math/Geometry/Vector3.hpp"

namespace BF
{
	struct OBJElement
	{
		public:
		char Name[20];
		unsigned int MaterialListIndex;
		float Smoothing;

		// List of geometric vertices, with (x, y, z [,w]) coordinates, w is optional and defaults to 1.
		List<Vector3<float>> VertexPositionList;

		// List of texture coordinates, in (u, [,v ,w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0.
		List<Vector2<float>> TextureCoordinateList;

		// List of vertex normals in (x,y,z) form; normals might not be unit vectors.
		List<Vector3<float>> VertexNormalPositionList;

		// Parameter space vertices in ( u [,v] [,w] ) form; free form geometry statement.
		List<Vector3<float>> VertexParameterList;

		// Polygonal face element.
		List<Vector3<unsigned int>> FaceElementList;

		OBJElement();
	};
}