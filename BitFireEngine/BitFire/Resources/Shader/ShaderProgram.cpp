#include "ShaderProgram.h"
#include "ShaderLoader.h"

void BF::ShaderProgram::AddShader(ASCIIString& vertexShader, ASCIIString& fragmentShader)
{
    ShaderList.ReSize(2);

    ShaderLoader::LoadFromFile(vertexShader, ShaderList[0]);
    ShaderLoader::LoadFromFile(fragmentShader, ShaderList[1]);
}
