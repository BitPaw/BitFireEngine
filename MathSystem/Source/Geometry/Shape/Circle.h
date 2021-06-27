#pragma once

#include "Shape.h"
#include "../../Math.h"

namespace BF
{
	class Circle : public Shape
	{
		public:
		Circle();
		Circle(float radius);
		Circle(float midPointx, float midPointy, float cornerPointx, float cornerPointy);
		Circle(Point<float> midPoint, Point<float> cornerPoint);

		Point<float> MiddlePoint;
		Point<float> CornerPoint;

		/// <summary>
		/// Half distance of the diameter.
		/// </summary>
		/// <returns></returns>
		float Radius();

		/// <summary>
		/// Width of the circle.
		/// </summary>
		/// <returns></returns>
		float Diameter();

		/// <summary>
		/// A = PI * r^2
		/// </summary>
		/// <returns></returns>
		virtual float SurfaceArea() override;

		/// <summary>
		/// U = 2 * PI  * r
		/// </summary>
		/// <returns></returns>
		virtual float Perimeter() override;

		void Set(float radius);
		void Set(float midPointx, float midPointy, float cornerPointx, float cornerPointy);
		void Set(Point<float> midPoint, Point<float> cornerPoint);
	};
}