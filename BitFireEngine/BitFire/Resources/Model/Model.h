#pragma once

#include "Mesh.h"
#include "LinkedMesh.h"
#include "IModel.h"
#include "ModelRenderInformation.h"

#include "../Resource.h"

#include "../../Mathematic/Geometry/Position.hpp"
#include "../../Utility/List.hpp"
#include "../../Utility/LinkedList.hpp"
#include "../../Color/RGBA.hpp"
//-----------------------------------------------------------------------------
namespace BF
{
	// Renderable Object used as core element for the rendersystem.
	class Model : public Resource, public IModel
	{
	protected:
		Position<float> _currentPosition;
		Position<float> _currentRotation;

	public:
		ModelRenderInformation RenderInformation;

		AsciiString ModelName;

		LinkedMesh GlobalMesh;
		List<RGBA<float>> ColorList;
		List<Mesh> MeshList;		

		Model();
		Model(AsciiString& name);

		void Move(float x, float y, float z) override;
		void Move(Position<float> position) override;
		void MoveTo(float x, float y, float z) override;
		void MoveTo(Position<float> position) override;		

		void Rotate(float x, float y, float z) override;
		void Rotate(Position<float> rotation) override;
		void RotateTo(float x, float y, float z) override;
		void RotateTo(Position<float> rotation) override;

		void Orbit(float x, float y, float z) override;
		void Orbit(Position<float> rotation) override;
		void Orbit(Position<float> rotation, Position<float> ancerPosition) override;

		void Scale(float x, float y, float z) override;
		void Scale(Position<float> scaleFactor) override;



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
	};
}
//-----------------------------------------------------------------------------