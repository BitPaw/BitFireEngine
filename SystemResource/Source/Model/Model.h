#pragma once

#include "Mesh.h"
#include "LinkedMesh.h"
#include "Material.h"
#include "../Resource.h"

#include "ModelType.h"
#include "../Math/Geometry/Shape/Shape.h"

#include "../Math/Geometry/Vector3.hpp"
#include "../Math/Geometry/Vector4.hpp"
#include "../Math/Geometry/Shape/Shape.h"
#include "../Math/Geometry/Matrix4x4.hpp"

namespace BF
{
	class Model : public Resource
	{
		public:
		size_t MaterialListSize;
		Material* MaterialList;

		size_t MeshListSize;
		Mesh* MeshList;

		Model();

		void PrintModelData();
		
		static ModelType FileFormatPeek(const wchar_t* filePath);

		size_t FullSizeInMemory();
		FileActionResult Load(const wchar_t* filePath);

		void ConvertFrom(float* vertexList, size_t vertexListSize, unsigned int* indexList, size_t indexListSize, float textureScaleX = 1, float textureScaleY = 1, bool rawPositions = false);
	};
}