#pragma once

#include "OGG.h"

#include "../../ILoader.h"
#include "../../../Utility/ASCIIString.h"

namespace BF
{
	class OGGLoader : public ILoader
	{
		private:
		OGGLoader();

		public:
		static OGG* LoadFromFile(ASCIIString filePath);
	};
}