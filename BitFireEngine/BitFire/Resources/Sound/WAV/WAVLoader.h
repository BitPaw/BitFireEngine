#pragma once

#include "WAV.h"

#include "../../ILoader.h"
#include "../../../Utility/AsciiString.h"

namespace BF
{
	class WAVLoader : public ILoader
	{
		private:
		WAVLoader();

		public:
		static WAV* LoadFromFile(AsciiString filePath);
	};
}