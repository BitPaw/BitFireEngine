#pragma once

#include "Shape.h"

#include "../Position.hpp"

namespace BF
{
	class Triangle : public Shape
	{
		public:	
		Triangle();
		Triangle(float xA, float yA, float xB, float yB, float xC, float yC);
		Triangle(Point<float> a, Point<float> b, Point<float> c);

		Point<float> PointA;
		Point<float> PointB;
		Point<float> PointC;

		float Height();
		float Width();	

		float LengthOfSideA();
		float LengthOfSideB();
		float LengthOfSideC();

		Position<float> NormalDirection();

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
		void Set(Point<float> a, Point<float> b, Point<float> c);
	};
}