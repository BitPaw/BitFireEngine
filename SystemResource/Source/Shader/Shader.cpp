#include "Shader.h"
#include "../File/FileStream.h"

#include <string>

BF::Shader::Shader()
{
	ID = -1;
	Type = ShaderType::Unkown;
	Content = 0;
    ContentSize = 0;
}

BF::Shader::Shader(ShaderType type, const wchar_t* filePath)
{
    ID = -1;
    Type = type;
    Content = 0;
    ContentSize = 0;

    FilePathChange(filePath);
}

BF::FileActionResult BF::Shader::Load()
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

     return FileStream::ReadFromDisk(FilePath, (Byte**)&Content, ContentSize, true);
}