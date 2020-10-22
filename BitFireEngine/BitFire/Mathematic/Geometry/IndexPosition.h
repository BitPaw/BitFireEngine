#pragma once

#include "IndexPoint.h"

namespace BF
{
	class IndexPosition : public IndexPoint
	{
		public:
		unsigned int Z;

		IndexPosition();
		IndexPosition(unsigned int x, unsigned int y, unsigned int z);
	};
}