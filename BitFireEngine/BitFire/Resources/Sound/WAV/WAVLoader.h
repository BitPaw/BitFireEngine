#pragma once

#include <string>

#include "WAV.h"

#include "../../ILoader.h"

namespace BF
{
	class WAVLoader : public ILoader
	{
		private:
		WAVLoader();

		public:
		static WAV* LoadFromFile(std::string filePath);
	};
}