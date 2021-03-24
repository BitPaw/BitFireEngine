#pragma once

#include "MID.h"

#include "../../ILoader.h"
#include "../../../Utility/AsciiString.h"

namespace BF
{
	class MIDLoader : public ILoader
	{
		private:
		MIDLoader();

		public:
		static MID* LoadFromFile(AsciiString filePath);
	};
}