#include "Shader.h"
#include "../File/File.h"

BF::Shader::Shader()
{
	ID = -1;
	Type = ShaderType::Unkown;
	Content = 0;
}

BF::Shader::Shader(ShaderType type, char* filePath)
{
    ID = -1;
    Type = type;
    Content = 0;
    strcpy_s(FilePath, 255, filePath);
}

void BF::Shader::Load()
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

	File::Read(FilePath, &Content);
}
