#pragma once

#include "Shape.h"
#include "../Vector2.hpp"

namespace BF
{
	class Square : public Shape<12, 4>
	{
		public:
		Square();
		Square(float sideLength);
		Square(Vector2<float> size);

		Vector2<float> PointA;
		Vector2<float> PointB;

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
		void Set(Vector2<float> size);
	};
}