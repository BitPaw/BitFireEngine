#pragma once

#include "../Vector/Vector3.h"
#include "MatrixNxN.hpp"

namespace BF
{
	struct Matrix3x3
	{
		Matrix _data;
		
		public:
		Vector3 RowX;
		Vector3 RowY;
		Vector3 RowZ;
	};
}