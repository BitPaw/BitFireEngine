#pragma once

#include "MID.h"

#include "../../ILoader.h"
#include "../../../Utility/ASCIIString.h"

namespace BF
{
	class MIDLoader : public ILoader
	{
		private:
		MIDLoader();

		public:
		static MID* LoadFromFile(ASCIIString filePath);
	};
}