#pragma once

#include "Shape.h"

#include "../Point.hpp"
#include "../Position.hpp"

namespace BF
{
	class Rectangle : public Shape
	{
		public:
		Rectangle();
		Rectangle(float width, float height);
		Rectangle(float x, float y, float width, float height);
		Rectangle(Point<float> a, Point<float> b);
		Rectangle(Point<float> a, Point<float> b, Point<float> c, Point<float> d);

		/// <summary>
		/// Left-Lower
		/// </summary>
		Point<float> PointA;

		/// <summary>
		/// Right-Lower
		/// </summary>
		Point<float> PointB;

		/// <summary>
		/// Right-Upper
		/// </summary>
		Point<float> PointC;

		/// <summary>
		/// Left-Upper
		/// </summary>
		Point<float> PointD;

		/// <summary>
		/// Width of the Rectangle
		/// </summary>
		/// <returns>Width</returns>
		float Width();

		/// <summary>
		/// Height of the Recktangle
		/// </summary>
		/// <returns>Height</returns>
		float Height();

		/// <summary>
		/// A = a*b
		/// </summary>
		/// <returns></returns>
		virtual float SurfaceArea() override;

		/// <summary>
		/// U = a + b + c + d
		/// </summary>
		/// <returns></returns>
		virtual float Perimeter() override;

		bool IsColliding(Rectangle* rectangle);

		Position<float> NormalDirection();

		void Set(float width, float height);
		void Set(float x, float y, float width, float height);
		void Set(Point<float> a, Point<float> b);
		void Set(Point<float> a, Point<float> b, Point<float> c, Point<float> d);

		List<Point<float>>* DrawPointList() override;
	};
}