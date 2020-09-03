#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class FileLoader
{
public:
	static std::string ReadCompleteFile(std::string filePath);
	static std::string* ReadFileByLines(std::string filePath, unsigned int* amount);
};

