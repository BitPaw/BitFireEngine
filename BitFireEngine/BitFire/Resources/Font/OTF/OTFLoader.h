#pragma once

#include <string>

#include "OTF.h"

#include "../../ILoader.h"

namespace BF
{
	class OTFLoader : public ILoader
	{
		private:
		OTFLoader();

		public:
		static OTF* LoadFromFile(std::string filePath);
	};
}