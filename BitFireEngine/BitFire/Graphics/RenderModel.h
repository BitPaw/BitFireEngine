#pragma once

#include <string>

#include "Mesh.h"
#include "LinkedMesh.h"

#include "../Resources/Model/WaveFront/WaveFront.h"
#include "../Mathematic/Geometry/Vector/Vector3.h"

namespace BF
{
	class RenderModel
	{
	protected:
		void UpdateRenderSystemLink();

	public:
		std::string ModelName;
		LinkedMesh GlobalMesh;
		List<Mesh> MeshList;

		RenderModel();
		RenderModel(std::string name);

		void LoadFromWaveFront(WaveFront& waveFront);

		//
		void MoveInDirection(Vector3 vector);

		void CalculateNormalVectors();

		void PrintModelData();

		void UpdateGlobalMesh();
	};
}