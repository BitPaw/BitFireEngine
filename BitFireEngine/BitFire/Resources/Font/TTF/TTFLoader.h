#pragma once

#include <string>

#include "TTF.h"

#include "../../ILoader.h"

namespace BF
{
	class TTFLoader : public ILoader
	{
		private:
		TTFLoader();

		public:
		static TTF* LoadFromFile(std::string filePath);
	};
}