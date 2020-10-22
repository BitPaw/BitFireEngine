#pragma once

#include <string>

#include "Mesh.h"
#include "LinkedMesh.h"
#include "IModel.h"

#include "../../Mathematic/Geometry/Vector/Vector3.h"
#include "../../Mathematic/Geometry/Position.h"
#include "../../Color/RGBA.h"
#include "../../Utility/List.hpp"
//-----------------------------------------------------------------------------
namespace BF
{
	// Renderable Object used as core element for the rendersystem.
	class Model : public IModel
	{
	protected:
		void UpdateRenderSystemLink();
		Vector3 _currentPosition;

	public:
		unsigned int ModelID;

		std::string ModelName;

		LinkedMesh GlobalMesh;

		List<RGBA> ColorList;
		List<Mesh> MeshList;

		Model();
		Model(std::string name);

		~Model();	


		void MoveBy(Vector3 vector) override;		
		void MoveTo(Vector3 vector) override;

		/**
			Get the current position of this object in this worldspace.
			@return Current position.
		*/
		Vector3 CurrentPosition();

		
		void Orbit(Vector3 vector) override;
		void Rotate(Vector3 vector) override;
		void Scale(Vector3 vector) override;

		/**
			Returns the area of a circle with the specified radius.
			@param radius The radius of the circle.
			@return The area of the circle.
		*/
		void CalculateNormalVectors();


		void UseTexturePointAsColor();

		void PrintModelData();

		void UpdateGlobalMesh();
	};
}
//-----------------------------------------------------------------------------