#pragma once

#include "Shape.h"

namespace BF
{
	class Square : public Shape
	{
		public:
		Square();
		Square(float sideLength);
		Square(Point<float> size);

		Point<float> PointA;
		Point<float> PointB;

		float SideLength();

		/// <summary>
		/// A = a^2
		/// </summary>
		/// <returns></returns>
		virtual float SurfaceArea() override;

		/// <summary>
		/// U = a + b + c
		/// </summary>
		/// <returns></returns>
		virtual float Perimeter() override;

		void Set(float sideLength);
		void Set(Point<float> size);
	};
}