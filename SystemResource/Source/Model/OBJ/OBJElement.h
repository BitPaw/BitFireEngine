#pragma once

#include "../../Container/AsciiString.h"
#include "../../Container/List.hpp"
#include "../../../../SystemResource/Source/Math/Geometry/Vector2.hpp"
#include "../../../../SystemResource/Source/Math/Geometry/Vector3.hpp"

#define OBJElementNameLength 50u

namespace BF
{
	struct OBJElementMaterialInfo
	{
		size_t MaterialIndex;
		size_t Size; // Size of buffer to use given material		
	};

	struct OBJElement
	{
		public:
		char Name[OBJElementNameLength];	
		float Smoothing;

		OBJElementMaterialInfo* MaterialInfo;
		size_t MaterialInfoSize;

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

		void Allocate(size_t vertexSize, size_t texturePointSize, size_t normalPointSize, size_t vertexParameterSize, size_t faceElementSize);
	};
}