#pragma once

#include "../Geometry/Matrix4x4.hpp"

namespace BF
{
	template<class NumberType>
	struct PhysicsStatic
	{
		public:
		Matrix4x4<float> MatrixModel;
	};
}