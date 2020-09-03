#pragma once

#include <string>
#include <GLEW/glew.h>
#include <fstream>

#include "DataType/Texture.h"

class TextureLoader
{
public:
	static Texture* LoadTexture(std::string filePath);
};