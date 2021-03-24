#include "ShaderProgram.h"
#include "ShaderLoader.h"

void BF::ShaderProgram::AddShader(AsciiString& vertexShader, AsciiString& fragmentShader)
{
    ShaderList.ReSize(2);

    ShaderLoader::LoadFromFile(vertexShader, ShaderList[0]);
    ShaderLoader::LoadFromFile(fragmentShader, ShaderList[1]);
}
