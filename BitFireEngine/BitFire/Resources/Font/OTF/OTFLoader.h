#pragma once

#include "OTF.h"

#include "../../ILoader.h"
#include "../../../Utility/ASCIIString.h"

namespace BF
{
	class OTFLoader : public ILoader
	{
		private:
		OTFLoader();

		public:
		static OTF* LoadFromFile(ASCIIString filePath);
	};
}