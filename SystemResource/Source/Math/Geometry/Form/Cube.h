#pragma once

#include "Form.h"

namespace BF
{
	class Cube : public Form<24, 24>
	{
		public:
		Cube();		

		float Volume() override;
		float SurfaceArea() override;
		float Perimeter() override;
		bool IsPointInObject(float x, float y, float z);
	};
}