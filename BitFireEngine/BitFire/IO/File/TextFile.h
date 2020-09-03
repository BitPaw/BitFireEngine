#pragma once

#include <string>
#include <vector>

class TextFile
{
public:
	unsigned int AmountOfLines;
	std::string* Lines;

	std::string Path;
	std::string Content;

	std::string FileName;

	TextFile();
	TextFile(std::string path, std::string content);

	void SplitContentIntoLines();
};