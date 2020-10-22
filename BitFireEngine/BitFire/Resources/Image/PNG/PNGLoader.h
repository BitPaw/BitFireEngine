#pragma once

#include <string>

#include "PNG.h"
#include "Chunk/Type/PortableNetworkGraphicFileHeader.h"
#include "Chunk/Type/PortableNetworkGraphicImageData.h"
#include "Chunk/Type/PortableNetworkGraphicChunkPalette.h"
#include "Chunk/Type/PNGChunkImageHeader.h"

#include "../../ILoader.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Mathematic/Converter/Converter.h"

namespace BF
{
	class PNGLoader : public ILoader
	{
	public:
		static PNG LoadFromFile(std::string filePath);
	};
}