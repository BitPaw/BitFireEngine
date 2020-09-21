#pragma once

#include <string>

#include "Mesh.h"
#include "LinkedMesh.h"

#include "../Resources/Model/WaveFront/WaveFront.h"
#include "../Mathematic/Geometry/Vector/Vector3.h"
//-----------------------------------------------------------------------------
namespace BF
{
	// Renderable Object used as core element for the rendersystem.
	class RenderModel
	{
	protected:
		void UpdateRenderSystemLink();
		Vector3 _currentPosition;

	public:
		unsigned int ModelID;

		std::string ModelName;
		LinkedMesh GlobalMesh;
		List<Mesh> MeshList;

		RenderModel();
		RenderModel(std::string name);

		void LoadFromWaveFront(WaveFront& waveFront);

		/**
			Move object in a specific direction in this worldspace.
			@param Direction in which this object should be moved in.
		*/
		void Move(Vector3 vector);

		/**
			Move to specific location in this worldspace.
			@param Position where this object should be moved to.
		*/
		void MoveTo(Vector3 vector);

		/**
			Get the current position of this object in this worldspace.
			@return Current position.
		*/
		Vector3 CurrentPosition();

		/**
			Rotate the object around the worldspace.
			@param Rotation, how much each axis should be rotated.
		*/
		void Orbit(Vector3 vector);

		/**
			Rotate the object around itself.
			@param Rotation, how much each axis should be rotated.
		*/
		void Rotate(Vector3 vector);

		/**
			Change the size of this object in this worldspace.
			@param Scalefactor, how much each axis should be Scaled. 1 => no change.
		*/
		void ReSize(Vector3 vector);

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