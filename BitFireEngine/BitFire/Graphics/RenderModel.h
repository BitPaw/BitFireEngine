#pragma once

#include <string>
#include <vector>

#include "Mesh.h"
#include "../Resources/Model/WaveFront/WaveFront.h"

class RenderModel
{
protected:
	void UpdateRenderSystemLink();

public:
	// [Managed Extern] The RenderSystem Stores an ID if this Unit is Registered.
	int RenderID;


	// Should this Model be rendered?
	bool ShouldBeRendered;

	RenderModel();
	RenderModel(std::string name, Mesh mesh);
	~RenderModel();

	std::string ModelName;
	std::vector<Mesh> VertexMeshList;

	void LoadFromWaveFront(WaveFront& waveFront);
	void MoveWholeObject(Position position);
};