#pragma once

namespace BF
{
	class Interpolate
	{
		public:
		static float Liniar(const float yMinimum, const float yMaximum, const float xMinimum, const float xMaximum, const float xValue);
		static float Normalize(const float minimum, const float maximum, const float value);
		static unsigned int LiniarClampAsRGBColor(const float minimum, const float maximum, const float value);
	};
}