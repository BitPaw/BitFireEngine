#pragma once

#include "Shape.h"

#include "../Vector2.hpp"
#include "../Vector3.hpp"

namespace BF
{
	class Rectangle : public Shape<12,4>
	{
		public:
		Rectangle();
		Rectangle(float width, float height);
		Rectangle(float x, float y, float width, float height);
		Rectangle(Vector2<float> a, Vector2<float> b);
		Rectangle(Vector2<float> a, Vector2<float> b, Vector2<float> c, Vector2<float> d);

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

		Vector3<float> NormalDirection();

		void Set(float width, float height);
		void Set(float x, float y, float width, float height);
		void Set(Vector2<float> a, Vector2<float> b);
		void Set(Vector2<float> a, Vector2<float> b, Vector2<float> c, Vector2<float> d);
	};
}