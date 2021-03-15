#pragma once

#include "../Utility/ASCIIString.h"

namespace BF
{
	class ICypher
	{
		protected:
		ICypher();

		public:
		virtual ASCIIString Cypher(ASCIIString message);
		virtual ASCIIString DeCypher(ASCIIString message);
	};
}