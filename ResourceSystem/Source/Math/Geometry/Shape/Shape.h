#pragma once

namespace BF
{
	class Shape
	{	
		public:
		virtual float SurfaceArea() = 0;
		virtual float Perimeter() = 0;
	};
}