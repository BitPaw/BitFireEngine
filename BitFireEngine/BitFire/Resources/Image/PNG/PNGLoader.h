#pragma once

#include "PNG.h"
#include "Chunk/PNGChunkType.h"

#include "../../ILoader.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Mathematic/Converter/Converter.h"

#include "../../../Utility/DoubleWord.h"
#include "../Image.h"

namespace BF
{
	class PNGLoader : public ILoader
	{	

		private:
		unsigned char FilterTypePeath(unsigned char leftCell, unsigned char aboveCell, unsigned char upperCell);

		public:
			static PNGChunkType ParseChunkType(DoubleWord& doubleWord);

		static PNG* LoadFromFile(AsciiString& filePath);
		static void LoadFromFile(AsciiString& filePath, PNG& png);

		static void PNGToImage(PNG& png, Image& image);
	};
}