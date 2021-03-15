#pragma once

#include "Form.h"

#include "../Position.hpp"

namespace BF
{
	class Cube : public Form
	{
		public:
		Cube();

		Position<float> PositionA;
		Position<float> PositionB;
		Position<float> PositionC;
		Position<float> PositionD;

		Position<float> PositionE;
		Position<float> PositionF;
		Position<float> PositionG;
		Position<float> PositionH;

		float Volume() override;
		float SurfaceArea() override;
		float Perimeter() override;

		virtual List<Point<float>>* DrawPointList() override;
	};
}