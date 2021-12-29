#pragma once

#include "../Vector2.hpp"
#include "../Vector3.hpp"

namespace BF
{
	class Rectangle
	{
		public:
		Vector2<float> Position;
		Vector2<float> Size;

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
		float SurfaceArea();

		/// <summary>
		/// U = a + b + c + d
		/// </summary>
		/// <returns></returns>
		float Perimeter();

		bool IsColliding(Rectangle* rectangle);

		Vector3<float> NormalDirection();

		void Set(float width, float height);
		void Set(float x, float y, float width, float height);
		void Set(Vector2<float> position, Vector2<float> size);

		void GenerateVertexData(float* vertexData, size_t vertexDataSize, unsigned int* indexData, size_t indexDataSize);
	};
}