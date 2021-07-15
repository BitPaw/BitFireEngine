#pragma once

#include "../../Utility/Table.hpp"

namespace BF
{
	template<class Numbertype>
	class Matrix2x2
	{
		private:
		Table<Numbertype> _matrixData;

		public:
		Matrix2x2()
		{
			_matrixData.ReSize(2, 2);
		}

		Matrix2x2(Numbertype xx, Numbertype yx, Numbertype xy, Numbertype yy) : Matrix2x2()
		{
			Set(xx, yx, xy, yy);
		}

		List<Numbertype>& operator[](int index)
		{
			return _matrixData[index];
		}

		Matrix2x2<Numbertype> operator+(Matrix2x2 matrix)
		{
			Matrix2x2 newMatrix(*this);

			newMatrix.Add(matrix);

			return newMatrix;
		}

		Matrix2x2<Numbertype> operator-(Matrix2x2 matrix)
		{
			return Matrix2x2<Numbertype>(*this).Substract(matrix);
		}	

		Matrix2x2<Numbertype> operator*(Numbertype number)
		{	
			return Matrix2x2<Numbertype>(*this).Multiply(number);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="a">Left-Upper</param>
		/// <param name="b">Right-Upper</param>
		/// <param name="c">Left-lower</param>
		/// <param name="d">Right-lower</param>
		void Set(Numbertype a, Numbertype b, Numbertype c, Numbertype d)
		{
			_matrixData[0][0] = a;  
			_matrixData[1][0] = b; 
			_matrixData[0][1] = c;  
			_matrixData[1][1] = d; 
		}

		void Add(Matrix2x2<Numbertype> matrix)
		{
			_matrixData[0][0] += matrix[0][0];
			_matrixData[1][0] += matrix[1][0];
			_matrixData[0][1] += matrix[0][1];
			_matrixData[1][1] += matrix[1][1];
		}

		void Substract(Matrix2x2<Numbertype> matrix)
		{
			_matrixData[0][0] -= matrix[0][0];
			_matrixData[1][0] -= matrix[1][0];
			_matrixData[0][1] -= matrix[0][1];
			_matrixData[1][1] -= matrix[1][1];
		}

		void Multiply(Numbertype number)
		{
			_matrixData[0][0] *= number;
			_matrixData[1][0] *= number;
			_matrixData[0][1] *= number;
			_matrixData[1][1] *= number;
		}

		Numbertype Determinate()
		{
			// ad - bc
			 return _matrixData[0][0] * _matrixData[1][1] - _matrixData[1][0] * _matrixData[0][1];
		}
	};
}