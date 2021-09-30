#pragma once

#include "Form.h"

namespace BF
{
	class Cube : public Form
	{
		public:
		unsigned int VertexListSize = 24;
		float VertexList[24] =
		{
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f
		};
#if 1 

		unsigned int IndexListSize = 24;
		unsigned int IndexList[24] =
		{
			1,3,5,7,
			2,4,6,8,
			3,4,7,8,
			5,6,7,8,
			1,2,3,4,
			1,2,5,6
		};
#else
		unsigned int IndexListSize = 36;
		unsigned int IndexList[36] =
		{
			5,3,1,
			5,7,3,

			2,8,6,
			2,4,8,

			3,8,4,
			3,7,8,

			7,6,8,
			7,5,6,

			1,4,2,
			1,3,4,

			5,1,2,
			5,2,6
		};
#endif

		float Volume() override;
		float SurfaceArea() override;
		float Perimeter() override;
		bool IsPointInObject(float x, float y, float z);
	};
}