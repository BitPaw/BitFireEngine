#pragma once

#include "Mesh.h"
#include "LinkedMesh.h"
#include "ModelRenderInformation.h"
#include "Material.h"
#include "../Resource.h"

#include "ModelType.h"

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
		ModelRenderInformation RenderInformation;

		LinkedMesh GlobalMesh;
		List<Vector4<float>> ColorList;	
		List<Material> MaterialList;

		List<Mesh> MeshList;

		Model();
		Model(const char* modelName);

		bool DirectMorth = true;

		/**
	Move object in a specific direction in this worldspace.
	@param Direction in which this object should be moved in.
*/
		void Move(float x, float y, float z);
		void Move(Vector3<float> position);

		/**
		Move to specific location in this worldspace.
		@param Position where this object should be moved to.
	*/
		void MoveTo(float x, float y, float z);
		void MoveTo(Vector3<float> position);

		/**
			Rotate the object around itself.
			@param Rotation, how much each axis should be rotated.
		*/
		void Rotate(float x, float y, float z);
		void Rotate(Vector3<float> rotation);

		/**
	Rotate the object around the worldspace.
	@param Rotation, how much each axis should be rotated.
*/
		void Orbit(float x, float y, float z);
		void Orbit(Vector3<float> rotation);

		/**
			Rotate the object around the worldspace.
			@param Rotation, how much each axis should be rotated.
		*/
		void Orbit(Vector3<float> rotation, Vector3<float> ancerPosition);

		/**
		Change the size of this object in this worldspace.
		@param Scalefactor, how much each axis should be Scaled. 1 => no change.
		*/
		void Scale(float x, float y, float z);
		void Scale(Vector3<float> scaleFactor);

		// Image
		void ScaleTexturePoints(float x, float y);
		void ScaleTexturePoints(Vector2<float> scale);

		void UseTexturePointAsColor();


		/**
			Returns the area of a circle with the specified radius.
			@param radius The radius of the circle.
			@return The area of the circle.
		*/
		void CalculateNormalVectors();
		void UpdateGlobalMesh();


		void PrintModelData();
		
		static ModelType FileFormatPeek(const char* filePath);
		FileActionResult Load();
		FileActionResult Load(const char* filePath);
		void ConvertFrom(Shape& shape);
	};
}