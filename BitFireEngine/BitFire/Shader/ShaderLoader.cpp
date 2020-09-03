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
            char* message = new char[lengh];

            glGetShaderInfoLog(id, lengh, &lengh, message);

            std::cout << "Failed to compile Shader!" << std::endl;
            std::cout << message << std::endl;

            glDeleteShader(id);

            delete[] message;

            return 0;
        }
    }   

    return id;
}

unsigned int ShaderLoader::CreateShader(const std::string vertexShader, const std::string fragmentShader)
{
    printf("[i] Creating Shader\n");

    unsigned int programm = glCreateProgram();
    unsigned int vertexShaderIndex = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragmentShaderIndex = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(programm, vertexShaderIndex);
    glAttachShader(programm, fragmentShaderIndex);
    glLinkProgram(programm);

    printf("[Programm]\n");

    GLint linked;
    glGetProgramiv(programm, GL_LINK_STATUS, &linked);
    printf(" linking [%s]\n", (linked ? "OK" : "ERROR"));

    glValidateProgram(programm);

    glGetProgramiv(programm, GL_VALIDATE_STATUS, &linked);
    printf(" validating [%s]\n", (linked ? "OK" : "ERROR"));


    ShaderLoader::CheckShader(vertexShaderIndex);
    ShaderLoader::CheckShader(fragmentShaderIndex);
    int res = ShaderLoader::CheckProgram(programm);



    // We used the Shaders above to compile, these elements are not used anymore.
    glDeleteShader(vertexShaderIndex); 
    glDeleteShader(fragmentShaderIndex);

    if (res == 0)
    {
        glDeleteProgram(programm);
        return -1;
    }

    return programm;
}

void ShaderLoader::CheckShader(const unsigned int shaderID)
{   
    GLint isCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
   
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
     
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);


        if (maxLength == 0)
        {
            printf("Shader Compileing failed :\n  <No information>\n");
        }
        else
        {
            // The maxLength includes the NULL character
// std::vector<GLchar> errorLog(maxLength);
            char* message = new char[maxLength];
            glGetShaderInfoLog(shaderID, maxLength, &maxLength, message);

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            //glDeleteShader(shader); // Don't leak the shader.

            printf("Shader Compileing failed :\n  %s\n", message);

            delete[] message;
        }

    }
    else
    {
        printf("Shader compileing sucessful.\n");
    }
}

int ShaderLoader::CheckProgram(const unsigned int programID)
{
    GLint isCompiled = 0;
    glGetProgramiv(programID, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

        if (maxLength == 0)
        {
            printf("Programm Compileing failed :\n  <No information>\n");
        }
        else
        {
            // The maxLength includes the NULL character
            char* message = new char[maxLength];
            glGetProgramInfoLog(programID, maxLength, &maxLength, message);

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            //glDeleteShader(shader); // Don't leak the shader.

            printf("Programm Compileing failed :\n  %s\n", message);

            delete[] message;
        }


    }
    else
    {
        printf("Programm compileing sucessful.\n");
    }

    return isCompiled;
}
