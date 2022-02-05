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
#include "../Math/Physic/Collider.h"

namespace BF
{
	// Renderable Object used as core element for the rendersystem.
	class Model : public Resource, public PhysicsDynamic<float>, public Collider
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

		void PrintModelData();
		
		static ModelType FileFormatPeek(const wchar_t* filePath);
		FileActionResult Load() override;
		FileActionResult Load(const wchar_t* filePath);

		void Position(Vector3<float> position);
		Vector3<float> Position();

		void ConvertFrom(float* vertexList, size_t vertexListSize, unsigned int* indexList, size_t indexListSize, RenderMode renderMode, float textureScaleX = 1, float textureScaleY = 1, bool rawPositions = false);
	
		void BoundingBoxUpdate();

		virtual size_t FullSizeInMemory() override;

		virtual bool IsColliding(Vector2<float> position) { return false; };
		virtual bool IsColliding(Vector3<float> position) { return false; };
	};
}