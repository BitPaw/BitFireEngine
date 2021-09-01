#pragma once

#include "Shape.h"
#include "../../Math.h"
#include "../Vector2.hpp"

namespace BF
{
	class Circle : public Shape
	{
		public:
		Circle();
		Circle(float radius);
		Circle(float midPointx, float midPointy, float cornerPointx, float cornerPointy);
		Circle(Vector2<float> midPoint, Vector2<float> cornerPoint);

		Vector2<float> MiddlePoint;
		Vector2<float> CornerPoint;

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
		void Set(Vector2<float> midPoint, Vector2<float> cornerPoint);
	};
}