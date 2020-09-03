#pragma once

#include "../RenderModel.h"
#include "../../Mathematic/Geometry/Shape/Rectangle.h"

namespace BF
{
	class RectangleModel : public RenderModel
	{
	public:
		Rectangle Shape;

		RectangleModel();
	};
}