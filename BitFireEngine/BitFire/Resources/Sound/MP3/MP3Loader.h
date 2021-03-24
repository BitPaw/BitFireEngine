#pragma once

#include "MP3.h"

#include "../../ILoader.h"
#include "../../../Utility/AsciiString.h"

namespace BF
{
	class MP3Loader : public ILoader
	{
		private:
		MP3Loader();

		public:
		static MP3* LoadFromFile(AsciiString filePath);
	};
}