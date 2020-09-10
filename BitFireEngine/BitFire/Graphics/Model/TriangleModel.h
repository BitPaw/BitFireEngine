#pragma once

#include "../RenderModel.h"
#include "../../Mathematic/Geometry/Shape/Triangle.h"

namespace BF
{
	class TriangleModel : public RenderModel
	{
	public:
		Triangle Shape;

		TriangleModel();
	};
}