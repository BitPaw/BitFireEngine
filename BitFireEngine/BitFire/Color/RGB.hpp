#pragma once

namespace BF
{
	template<class T>
	class RGB
	{
		public:
		T Red;
		T Green;
		T Blue;

		RGB();
		RGB(T red, T green, T blue);

		virtual void SetColor(T red, T green, T blue);
	};

	template<class T>
	inline RGB<T>::RGB()
	{
		RGB(-1,-1,-1);
	}

	template<class T>
	inline RGB<T>::RGB(T red, T green, T blue)
	{
		SetColor(red, green, blue);
	}

	template<class T>
	inline void RGB<T>::SetColor(T red, T green, T blue)
	{
		Red = red;
		Green = green;
		Blue = blue;
	}
}