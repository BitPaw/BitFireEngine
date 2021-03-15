#pragma once

#include "../Point.hpp"
#include "../../../Utility/List.hpp"

namespace BF
{
	class Shape
	{	
		public:
		virtual float SurfaceArea() = 0;
		virtual float Perimeter() = 0;
		virtual List<Point<float>>* DrawPointList() = 0;
	};
}