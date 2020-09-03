#pragma once

#include <string>

#include "../../Mathmatic/Geometry/Vertex.h"
#include "../../Mathmatic/Geometry/RenderObject.h"
#include "../../Mathmatic/Geometry/TrippelIndex.h"
#include "../../SplittedString.h"

class WaveFont
{
private:
	static Position ParsePositionLine(std::string line);
	static Point ParsePointLine(std::string line);
	static void ParseIndicesAndMerge(std::string line, TrippelIndex* indexList, unsigned int* index);

public:
	static RenderObject* LoadFromFile(std::string filePath);
};