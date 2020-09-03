#pragma once

#include <string>
#include <GLEW/glew.h>

#include "DataType/Texture.h"

class TextureLoader
{
	static Texture* LoadTexture(std::string filePath);
};