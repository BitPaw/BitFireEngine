#pragma once

#include <string>
#include <vector>

class TextFile
{
public:
	unsigned int AmountOfLines;
	std::vector<std::string> Lines;

	std::string Path;
	std::string Content;

	TextFile();
	TextFile(std::string path, std::string content);

	void SplitContentIntoLines();
};