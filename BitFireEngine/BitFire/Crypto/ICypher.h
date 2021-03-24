#pragma once

#include "../Utility/AsciiString.h"

namespace BF
{
	class ICypher
	{
		protected:
		ICypher();

		public:
		virtual AsciiString Cypher(AsciiString message);
		virtual AsciiString DeCypher(AsciiString message);
	};
}