#pragma once

#include "../Shape/Shape.h"

namespace BF
{
	class Form : public Shape
	{
		public:
		virtual float Volume();
	};
}