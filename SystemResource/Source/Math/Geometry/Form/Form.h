#pragma once

#include "../Shape/Shape.h"

namespace BF
{
	template<const unsigned int VertexSize, const unsigned int IndexSize>
	class Form : public Shape<VertexSize, IndexSize>
	{
		public:
		virtual float Volume() = 0;
	};
}