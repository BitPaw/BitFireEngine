#pragma once

#include "PNG.h"

#include "../../ILoader.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Mathematic/Converter/Converter.h"

namespace BF
{
	class PNGLoader : public ILoader
	{	

		public:
		static PNG* LoadFromFile(ASCIIString& filePath);
	};
}