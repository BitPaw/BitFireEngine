#pragma once

#include <string>

#include "Mesh.h"
#include "../Resources/Model/WaveFront/WaveFront.h"
#include "LinkedMesh.h"

namespace BF
{
	class RenderModel
	{
	protected:
		void UpdateRenderSystemLink();

	public:
		// [Managed Extern] The RenderSystem Stores an ID if this Unit is Registered.
		int RenderID;

		// Should this Model be rendered?
		bool ShouldBeRendered;

		std::string ModelName;
		LinkedMesh GlobalMesh;
		List<Mesh> MeshList;

		RenderModel();
		RenderModel(std::string name);

		void LoadFromWaveFront(WaveFront& waveFront);
		void MoveWholeObject(Position position);

		void CalculateNormalVectors();

		void PrintModelData();


		void UpdateGlobalMesh();


		//Vertex* GetVertexInGlobalMesh(const unsigned int vertexID);
		//Point* GetTexturePointInGlobalMesh(const unsigned int vertexID);
		//Position* GetNormalInGlobalMesh(const unsigned int vertexID);
	};
}