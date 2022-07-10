#include "Shader.h"

#include <File/File.h>

#include <cstdlib>

BF::Shader::Shader()
{
	Type = ShaderType::Unkown;
	Content = 0;
    ContentSize = 0;
}

BF::Shader::Shader(const ShaderType type)
{
    Type = type;
    Content = 0;
    ContentSize = 0;
}

BF::Shader::~Shader()
{
    free(Content);
}

size_t BF::Shader::FullSizeInMemory()
{
    return sizeof(*this) + sizeof(char) * ContentSize;
}

BF::FileActionResult BF::Shader::Load(const wchar_t* filePath)
{
	/*
	    bool isVertexType = fileExtension.CompareIgnoreCase("vert");
    bool isTessellationControlType = fileExtension.CompareIgnoreCase("tesc");
    bool isTessellationEvaluationType = fileExtension.CompareIgnoreCase("tese");
    bool isGeometryType = fileExtension.CompareIgnoreCase("geom");
    bool isFragmentType = fileExtension.CompareIgnoreCase("frag");
    bool isComputeType = fileExtension.CompareIgnoreCase("comp");

    if (isVertexType)
        return ShaderType::Vertex;

    if (isTessellationControlType) 
        return  ShaderType::TessellationControl;

    if (isTessellationEvaluationType)
        return  ShaderType::TessellationEvaluation;

    if (isGeometryType) 
        return ShaderType::Geometry;

    if (isFragmentType) 
        return ShaderType::Fragment;

    if (isComputeType) 
        return ShaderType::Compute;

    return ShaderType::Unkown;
	*/

     return File::ReadFromDisk(filePath, (Byte__**)&Content, ContentSize, true);
}