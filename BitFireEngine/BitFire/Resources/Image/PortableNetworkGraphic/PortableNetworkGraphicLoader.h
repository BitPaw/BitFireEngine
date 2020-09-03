#pragma once

#include <string>

#include "PortableNetworkGraphic.h"
#include "Chunk/Type/PortableNetworkGraphicFileHeader.h"
#include "Chunk/Type/PortableNetworkGraphicImageData.h"
#include "Chunk/Type/PortableNetworkGraphicChunkPalette.h"
#include "Chunk/Type/PortableNetworkGraphicChunkImageHeader.h"

#include "../../../IO/File/FileLoader.h"

class PortableNetworkGraphicLoader
{
public:
	static PortableNetworkGraphic LoadFromFile(std::string filePath);
};

