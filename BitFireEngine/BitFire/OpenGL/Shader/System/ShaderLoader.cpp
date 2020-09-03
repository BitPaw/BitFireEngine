#include "ShaderLoader.h"

unsigned int ShaderLoader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    {
        int result;

        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int lengh;

            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lengh);
            char* message = (char*)alloca(lengh * sizeof(char));

            glGetShaderInfoLog(id, lengh, &lengh, message);

            std::cout << "Failed to compile Shader ID:" << id << "!" << std::endl;
            std::cout << message << std::endl;

            glDeleteShader(id);

            return 0;
        }
    }   

    return id;
}

unsigned int ShaderLoader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int programm = glCreateProgram();
    printf("Trining to compile GL_VERTEX_SHADER\n");
    unsigned int vertexShaderIndex = CompileShader(GL_VERTEX_SHADER, vertexShader);
    printf("Trining to compile GL_FRAGMENT_SHADER\n");
    unsigned int fragmentShaderIndex = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(programm, vertexShaderIndex);
    glAttachShader(programm, fragmentShaderIndex);
    glLinkProgram(programm);
    glValidateProgram(programm);

    // We used the Shaders above to compile, these elements are not used anymore.
    glDeleteShader(vertexShaderIndex); 
    glDeleteShader(fragmentShaderIndex);

    return programm;
}