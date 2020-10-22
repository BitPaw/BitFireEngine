#pragma once

namespace BF
{
	class CRCAlgorithm
	{
		public:
		static bool Check(unsigned int);
		static unsigned int Calculate();
	};
}