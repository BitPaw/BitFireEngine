#pragma once

#include <string>
#include <vector>

#include "PixelArray.h"

#include "../../../IO/File/FileLoader.h"

class PixelArrayLoader
{
public:
	static PixelArray LoadFromFile(std::string filePath);
	static void SaveToFile(std::string filePath, PixelArray& pixelArray);

	static void PrintPixelArray(PixelArray& pixelArray);
};