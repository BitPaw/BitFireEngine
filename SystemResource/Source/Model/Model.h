#pragma once

#include "Mesh.h"
#include "LinkedMesh.h"
#include "Material.h"
#include "../Resource.h"

#include "ModelType.h"

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
		ActionResult Load(const wchar_t* filePath);

		void ConvertFrom(float* vertexList, size_t vertexListSize, unsigned int* indexList, size_t indexListSize, float textureScaleX = 1, float textureScaleY = 1, bool rawPositions = false);
	};
}