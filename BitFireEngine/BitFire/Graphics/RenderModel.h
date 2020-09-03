#pragma once

#include <string>
#include <vector>

#include "Mesh.h"
#include "../Resources/Model/WaveFront/WaveFront.h"

class RenderModel
{
public:
	RenderModel();
	RenderModel(std::string name, Mesh mesh);
	~RenderModel();

	std::string ModelName;
	std::vector<Mesh> VertexMeshList;

	void LoadFromWaveFront(WaveFront& waveFront);
};