#include "ShaderFile.h"

/*
        .vert - a vertex shader
        .tesc - a tessellation control shader
        .tese - a tessellation evaluation shader
        .geom - a geometry shader
        .frag - a fragment shader
        .comp - a compute shader
*/

ShaderFile::ShaderFile()
{

}

ShaderFile::ShaderFile(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    LoadShader(vertexShaderPath, fragmentShaderPath);
}

void ShaderFile::LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    VertexShader = FileLoader::ReadTextFile(vertexShaderPath);
    FragmentShader = FileLoader::ReadTextFile(fragmentShaderPath);
}