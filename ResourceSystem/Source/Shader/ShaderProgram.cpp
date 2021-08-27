#include "ShaderProgram.h"

void BF::ShaderProgram::AddShader(const char* vertexShaderPath, const char* fragmentShaderFilePath)
{
    ShaderList[0] = Shader(ShaderType::Vertex, vertexShaderPath);
    ShaderList[1] = Shader(ShaderType::Fragment, fragmentShaderFilePath);
}

void BF::ShaderProgram::Load()
{
    unsigned char size = static_cast<unsigned char>(2);

    for (unsigned char i = 0; i < size; i++)
    {
        Shader& shader = ShaderList[i];

        shader.Load();
    }
}

bool BF::ShaderProgram::IsLoaded()
{
    for (size_t i = 0; i < 2; i++)
    {
        Shader& shader = ShaderList[i];
        bool isLoaded = shader.Content != 0;

        if (!isLoaded)
        {
            return false;
        }
    }

    return true;
}
