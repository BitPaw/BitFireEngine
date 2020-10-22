#pragma once

#include <string>

#include "MID.h"

#include "../../ILoader.h"

namespace BF
{
	class MIDLoader : public ILoader
	{
		private:
		MIDLoader();

		public:
		static MID* LoadFromFile(std::string filePath);
	};
}