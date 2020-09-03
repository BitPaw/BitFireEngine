#pragma once

#include <string>
#include "../Mathmatic/Geometry/Vertex.h"
#include "../Mathmatic/Geometry/RenderObject.h"
#include "../SplittedString.h"

class WaveFont
{
private:
	Vertex ParseVertexLine(std::string line);
	Point ParsePointLine(std::string line);
	void ParseIndicesAndMerge(std::string line, unsigned int* array, unsigned int* index);

public:
	RenderObject* LoadFromFile(std::string filePath);
};

