#pragma once

#include <string>

#include "OGG.h"

#include "../../ILoader.h"

namespace BF
{
	class OGGLoader : public ILoader
	{
		private:
		OGGLoader();

		public:
		static OGG* LoadFromFile(std::string filePath);
	};
}