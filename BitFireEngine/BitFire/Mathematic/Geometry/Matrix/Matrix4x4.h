#pragma once

#include "../Vector/Vector4.h"

namespace BF
{
	struct Matrix4x4
	{
	public:
		Vector4 RowX;
		Vector4 RowY;
		Vector4 RowZ;
		Vector4 RowW;
	};
}