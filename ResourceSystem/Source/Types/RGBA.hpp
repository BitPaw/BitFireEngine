#pragma once

#include "RGB.hpp"

#include "../../../MathSystem/Source/Math.h"
#include "../../../MathSystem/Source/Interpolate.h"

namespace BF
{
	template<class T>
	class RGBA : public RGB<T>
	{
		public:
		T Alpha;

		RGBA()
		{
			SetColor(-1, -1, -1);
		}
		RGBA(T red, T green, T blue)
		{
			SetColor(red, green, blue);
		}
		RGBA(T red, T green, T blue, T alpha)
		{
			SetColor(red, green, blue, alpha);
		}

		void SetColor(T red, T green, T blue) override
		{
			SetColor(red, green, blue, -1);
		}

		void SetColor(T red, T green, T blue, T alpha)
		{
			this->Red = red;
			this->Green = green;
			this->Blue = blue;
			Alpha = alpha;
		}

		static RGBA GetRandomeColor()
		{
			T r = Math::RandomeNumber() % 255;
			T g = Math::RandomeNumber() % 255;
			T b = Math::RandomeNumber() % 255;

			r = Interpolate::Liniar(0, 1, 0, 255, r);
			g = Interpolate::Liniar(0, 1, 0, 255, g);
			b = Interpolate::Liniar(0, 1, 0, 255, b);

			return RGBA(r, g, b);
		}
	};
}