#pragma once

#include "Mesh.h"
#include "LinkedMesh.h"
#include "ModelRenderInformation.h"
#include "Material.h"
#include "../Resource.h"

#include "ModelType.h"

#include "../Math/Geometry/Vector3.hpp"
#include "../Math/Geometry/Vector4.hpp"
#include "../Math/Geometry/Position.hpp"
#include "../Math/Geometry/Shape/Shape.h"
#include "../Math/Geometry/Matrix4x4.hpp"

namespace BF
{
	// Renderable Object used as core element for the rendersystem.
	class Model : public Resource
	{
		public:
		ModelRenderInformation RenderInformation;

		AsciiString ModelName;

		Matrix4x4<float> ModelMatrix;

		LinkedMesh GlobalMesh;
		List<Vector4<float>> ColorList;
		List<Mesh> MeshList;
		List<Material> MaterialList;

		Model();
		Model(AsciiString& name);

		bool DirectMorth = true;

		/**
	Move object in a specific direction in this worldspace.
	@param Direction in which this object should be moved in.
*/
		void Move(float x, float y, float z);
		void Move(Position<float> position);

		/**
		Move to specific location in this worldspace.
		@param Position where this object should be moved to.
	*/
		void MoveTo(float x, float y, float z);
		void MoveTo(Position<float> position);

		/**
			Rotate the object around itself.
			@param Rotation, how much each axis should be rotated.
		*/
		void Rotate(float x, float y, float z);
		void Rotate(Position<float> rotation);
		void RotateTo(float x, float y, float z);
		void RotateTo(Position<float> rotation);

		/**
	Rotate the object around the worldspace.
	@param Rotation, how much each axis should be rotated.
*/
		void Orbit(float x, float y, float z);
		void Orbit(Position<float> rotation);

		/**
			Rotate the object around the worldspace.
			@param Rotation, how much each axis should be rotated.
		*/
		void Orbit(Position<float> rotation, Position<float> ancerPosition);

		/**
		Change the size of this object in this worldspace.
		@param Scalefactor, how much each axis should be Scaled. 1 => no change.
		*/
		void Scale(float x, float y, float z);
		void Scale(Position<float> scaleFactor);

		// Image
		void ScaleTexturePoints(float x, float y);
		void ScaleTexturePoints(Point<float> scale);

		/**
			Get the current position of this object in this worldspace.
			@return Current position.
		*/
		Position<float> CurrentPosition();

		Position<float> CurrentRotation();

		void UseTexturePointAsColor();


		/**
			Returns the area of a circle with the specified radius.
			@param radius The radius of the circle.
			@return The area of the circle.
		*/
		void CalculateNormalVectors();
		void UpdateGlobalMesh();


		void PrintModelData();
		void PrintCurrentPosition();
		void PrintCurrentRotation();

		
		static ModelType CheckFileExtension(const char* fileExtension);
		ErrorCode Load(const char* filePath);
		void ConvertFrom(Shape& shape);
	};
}