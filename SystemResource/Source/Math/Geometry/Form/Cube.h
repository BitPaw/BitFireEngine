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

		static bool IsPointInObject
		(
			float ancerPositionX,
			float ancerPositionY,
			float ancerPositionZ,
			float ancerSizeX,
			float ancerSizeY,
			float ancerSizeZ,
			float targetPositionX,
			float targetPositionY,
			float targetPositionZ,
			float targetSizeX,
			float targetSizeY,
			float targetSizeZ
		);

		static bool IsInLinar(float ancerPosition, float ancerSize, float targetPosition, float targetSize);
	};
}