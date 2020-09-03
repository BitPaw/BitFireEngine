#pragma once

#include <string>
#include "../Mathmatic/Geometry/Vertex.h"
#include "../Mathmatic/Geometry/RenderObject.h"
#include "../SplittedString.h"

class WaveFont
{
private:
	Position ParsePositionLine(std::string line);
	Point ParsePointLine(std::string line);
	void ParseIndicesAndMerge(std::string line, Position* list, unsigned int* index);

public:
	RenderObject* LoadFromFile(std::string filePath);
};

