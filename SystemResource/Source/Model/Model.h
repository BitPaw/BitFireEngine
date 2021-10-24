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
#include "../Math/Physic/PhysicsDynamic.hpp"

namespace BF
{
	// Renderable Object used as core element for the rendersystem.
	class Model : public Resource, public PhysicsDynamic<float>
	{
		public:
		bool ShouldItBeRendered;

		size_t MaterialListSize;
		Material* MaterialList;

		size_t MeshListSize;
		Mesh* MeshList;

		Model* SharedModel;
		MeshRenderInfo SharedRenderInfoOverride;

		Model();
		Model(const char* modelName);

		void PrintModelData();
		
		static ModelType FileFormatPeek(const char* filePath);
		FileActionResult Load();
		FileActionResult Load(const char* filePath);

		void ConvertFrom(float* vertexList, size_t vertexListSize, unsigned int* indexList, size_t indexListSize, RenderMode renderMode, float textureScale = 1, bool rawPositions = false);
	};
}