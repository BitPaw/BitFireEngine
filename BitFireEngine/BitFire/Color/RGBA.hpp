#pragma once

#include "RGB.hpp"

#include "../Mathematic/Math.h"
#include "../Mathematic/Interpolate.h"

namespace BF
{
	template<class T>
	class RGBA : public RGB<T>
	{
		public:
		T Alpha;

		RGBA();
		RGBA(T red, T green, T blue);
		RGBA(T red, T green, T blue, T alpha);

		void SetColor(T red, T green, T blue) override;
		void SetColor(T red, T green, T blue, T alpha);

		static RGBA GetRandomeColor();
	};

	template<class T>
	inline RGBA<T>::RGBA()
	{
		SetColor(-1, -1, -1);
	}

	template<class T>
	inline RGBA<T>::RGBA(T red, T green, T blue)
	{
		SetColor(red, green, blue);
	}

	template<class T>
	inline RGBA<T>::RGBA(T red, T green, T blue, T alpha)
	{
		SetColor(red, green, blue, alpha);
	}

	template<class T>
	inline void RGBA<T>::SetColor(T red, T green, T blue)
	{
		SetColor(red, green, blue, -1);
	}

	template<class T>
	inline void RGBA<T>::SetColor(T red, T green, T blue, T alpha)
	{
		this->Red = red;
		this->Green = green;
		this->Blue = blue;
		Alpha = alpha;
	}

	template<class T>
	inline RGBA<T> RGBA<T>::GetRandomeColor()
	{
		T r = Math::RandomeNumber() % 255;
		T g = Math::RandomeNumber() % 255;
		T b = Math::RandomeNumber() % 255;

		r = Interpolate::Liniar(0, 1, 0, 255, r);
		g = Interpolate::Liniar(0, 1, 0, 255, g);
		b = Interpolate::Liniar(0, 1, 0, 255, b);

		return RGBA(r, g, b);
	}
}