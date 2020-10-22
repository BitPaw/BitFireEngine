#pragma once

#include <string>

#include "MP3.h"

#include "../../ILoader.h"

namespace BF
{
	class MP3Loader : public ILoader
	{
		private:
		MP3Loader();

		public:
		static MP3* LoadFromFile(std::string filePath);
	};
}