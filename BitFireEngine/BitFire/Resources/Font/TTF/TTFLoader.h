#pragma once

#include "TTF.h"

#include "../../ILoader.h"
#include "../../../Utility/ASCIIString.h"

namespace BF
{
	class TTFLoader : public ILoader
	{
		private:
		TTFLoader();

		public:
		static TTF* LoadFromFile(ASCIIString filePath);
	};
}