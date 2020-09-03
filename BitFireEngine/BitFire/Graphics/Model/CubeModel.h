#pragma once

#include "../Vertex.h"
#include "../RenderModel.h"
#include "../../Mathematic/Geometry/Form/Cube.h"

class CubeModel : public RenderModel
{
	public:
		Cube Form;

		Vertex A;
		Vertex B;
		Vertex C;
		Vertex D;

		Vertex E;
		Vertex F;
		Vertex G;
		Vertex H;

		CubeModel();
};