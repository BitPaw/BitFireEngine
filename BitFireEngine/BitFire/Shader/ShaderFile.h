#pragma once

#include <string>

class ShaderFile
{
public:
	std::string VertexShader;
	std::string VertexShaderPath;
	std::string FragmentShader;
	std::string FragmentShaderPath;

	ShaderFile();
	ShaderFile(std::string vertexShaderPath, std::string fragmentShaderPath);

	void LoadShaderFiles();
};