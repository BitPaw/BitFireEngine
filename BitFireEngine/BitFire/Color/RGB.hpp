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

		RGB()
		{
			SetColor(-1, -1, -1);
		}

		RGB(T red, T green, T blue)
		{
			SetColor(red, green, blue);
		}

		virtual void SetColor(T red, T green, T blue)
		{
			Red = red;
			Green = green;
			Blue = blue;		
		}
	};
}