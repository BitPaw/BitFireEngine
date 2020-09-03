#pragma once

#include <string>
#include <vector>

#include "WaveFront.h"
#include "WaveFrontLineCommand.h"

#include "../../../Mathematic/Geometry/Position.h"
#include "../../../IO/TrippelIndex.h"
#include "../../../IO/File/TextFile.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Utility/StringSplitter.h"

class WaveFrontLoader
{
private:
	static Position ParsePositionLine(std::string line);
	static Point ParsePointLine(std::string line);
	static std::vector<IndexPosition> ParseFaceLine(std::string line);

public:
	static WaveFront LoadFromFile(std::string filePath);
	static void SaveToFile(std::string filePath, WaveFront& waveFont);
	static void PrintObjectDataToConsole(WaveFront& waveFont);
};