#pragma once

namespace BF
{
	template<const unsigned int VertexSize, const unsigned int IndexSize>
	class Shape
	{	
		public:
		unsigned int VertexListSize = VertexSize;
		float VertexList[VertexSize];
		unsigned int IndexListSize = IndexSize;
		unsigned int IndexList[IndexSize];

		virtual float SurfaceArea() = 0;
		virtual float Perimeter() = 0;
	};
}