#pragma once

#include "Shape.h"

#include "../Vector2.hpp"
#include "../Vector3.hpp"

namespace BF
{
	class Triangle : public Shape<9,3>
	{
		public:	
		Triangle();
		Triangle(float xA, float yA, float xB, float yB, float xC, float yC);
		Triangle(Vector2<float> a, Vector2<float> b, Vector2<float> c);

		Vector2<float> PointA;
		Vector2<float> PointB;
		Vector2<float> PointC;

		float Height();
		float Width();	

		float LengthOfSideA();
		float LengthOfSideB();
		float LengthOfSideC();

		Vector3<float> NormalDirection();

		float DegreeAlpha();
		float DegreeBeta();
		float DegreeGamma();

		/// <summary>
		/// A = (Width * Height) / 2
		/// </summary>
		/// <returns></returns>
		virtual float SurfaceArea() override;

		/// <summary>
		/// U = a + b + c
		/// </summary>
		/// <returns></returns>
		virtual float Perimeter() override;

		void Set(float xA, float yA, float xB, float yB, float xC, float yC);
		void Set(Vector2<float> a, Vector2<float> b, Vector2<float> c);
	};
}