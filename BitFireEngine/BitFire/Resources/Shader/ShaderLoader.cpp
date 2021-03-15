#include "ShaderLoader.h"

BF::ShaderType BF::ShaderLoader::CheckShaderType(ASCIIString& fileExtension)
{
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
}

void BF::ShaderLoader::LoadFromFile(ASCIIString& filePath, Shader& shader)
{
    ASCIIString extension;
   
    FileLoader::ReadCompleteFile(filePath, shader.Content);    
    FileLoader::GetFileExtension(filePath, extension);

    shader.FilePath.Copy(filePath);
    shader.Type = CheckShaderType(extension); 
}