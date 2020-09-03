#pragma once

#include <string>
#include <vector>

#include "PixelArray.h"

#include "../../../IO/File/FileLoader.h"

class PixelArrayLoader
{
public:
	static PixelArray LoadFromFile(std::string filePath);
	static void PrintPixelArray(PixelArray& pixelArray);
};