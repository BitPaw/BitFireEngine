#include "ShaderFile.h"

ShaderFile::ShaderFile()
{

}

ShaderFile::ShaderFile(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	VertexShaderPath = vertexShaderPath;
	//VertexShader = nullptr;

	FragmentShaderPath = fragmentShaderPath;
	//FragmentShader = nullptr;
}

void ShaderFile::LoadShaderFiles()
{

}
