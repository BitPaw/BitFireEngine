#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "TextFile.h"

class FileLoader
{
private:
	static std::string ReadCompleteFile(std::string filePath);
	static std::string* ReadFileByLines(std::string filePath, unsigned int* amount);

public:
	static TextFile ReadTextFile(std::string filePath);
	static std::vector<unsigned char> ReadFileAsBytes(std::string filePath);
};