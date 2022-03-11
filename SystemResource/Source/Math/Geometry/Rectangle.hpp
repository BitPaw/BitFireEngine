#pragma once

namespace BF
{
	template<typename NumberType>
	class Rectangle
	{
		public:		
		NumberType X;
		NumberType Y;		
		NumberType Width;
		NumberType Height;

		Rectangle()
		{
			Set(0, 0, 0, 0);	
		}

		Rectangle(const NumberType width, const NumberType height)
		{
			Set(width, height);
		}

		Rectangle(const NumberType x, const NumberType y, const NumberType width, const NumberType height)
		{
			Set(x, y, width, height);
		}

		constexpr void Set(const NumberType width, const NumberType height)
		{
			Set(0, 0, width, height);
		}

		constexpr void Set(const NumberType x, const NumberType y, const NumberType width, const NumberType height)
		{
			X = x;
			Y = y;
			Width = width;
			Height = height;
		}

		constexpr bool Contain(const NumberType x, const NumberType y) const
		{
			return !(x < X || y < Y || x >= (X + Width) || y >= (Y + Height));
		}

		constexpr bool Contain(const NumberType x, const NumberType y, const NumberType width, const NumberType height) const
		{
			const bool isInX = (x >= X) && (x + width < X + Width);
			const bool isInY = (y >= Y) && (y + height < Y + Height);

			return isInX && isInY;
		}

		constexpr bool Overlap(const NumberType x, const NumberType y, const NumberType width, const NumberType height) const
		{
			return (X < x + width && X + Width >= x && Y < y + height && Y + Height >= height);
		}

		/// <summary>
		/// A = a*b
		/// </summary>
		/// <returns></returns>
		NumberType SurfaceArea()
		{
			return 0;
		}
		
		/// <summary>
		/// U = a + b + c + d
		/// </summary>
		/// <returns></returns>
		NumberType Perimeter()
		{
			return 0;
		}		
	};
}