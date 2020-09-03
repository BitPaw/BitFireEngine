#pragma once

#include <string>

#include "../../../IO/File/TextFile.h"
#include "../../../IO/File/FileLoader.h"

class ShaderFile
{
public:
	TextFile VertexShader;
	TextFile FragmentShader;

	ShaderFile();
	ShaderFile(std::string vertexShaderPath, std::string fragmentShaderPath);

	void LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath);
};