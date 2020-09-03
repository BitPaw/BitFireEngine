#pragma once
#include <string>
#include <iostream>
#include <fstream>

class FileLoader
{
public:
	static std::string ReadFile(std::string filePath);
};

