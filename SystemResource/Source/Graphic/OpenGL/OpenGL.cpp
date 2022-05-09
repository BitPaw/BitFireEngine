#include "OpenGL.h"

#if OpenGLInUse

#include <cassert>

#include <GL/glew.h>
#include <Hardware/Memory/Memory.h>

void BF::OpenGL::Initialize()
{

}

OpenGLID BF::OpenGL::ShaderProgramCreate()
{
    return glCreateProgram();
}

void BF::OpenGL::DepthMaskEnable(bool enable)
{
    if (enable)
    {
        glDepthMask(GL_TRUE);
    }
    else
    {
        glDepthMask(GL_FALSE);
    }
}

void BF::OpenGL::DrawOrder(bool clockwise)
{
    if (clockwise)
    {
        glFrontFace(GL_CW);
    }
    else
    {
        glFrontFace(GL_CCW);
    }
}

void BF::OpenGL::RenderBothSides(bool renderBothSides)
{
    if (renderBothSides)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
    }
}

char BF::OpenGL::UseShaderProgram(int shaderProgramID)
{
    const bool valid = shaderProgramID != -1;

    if(!valid)
    {
        return false;
    }

    glUseProgram(shaderProgramID);

    return true;
}

void BF::OpenGL::VertexArrayBind(int vertexArrayID)
{
    assert(vertexArrayID != -1);

    glBindVertexArray(vertexArrayID);
}

void BF::OpenGL::VertexBufferBind(int vertexBufferID, int indexBuffer)
{
    assert(vertexBufferID != -1);
    assert(indexBuffer != -1);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

int BF::OpenGL::TextureMaxSlots()
{
    int value = -1;

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (GLint*)&value);

    return value;
}

int BF::OpenGL::TextureMaxLoaded()
{
    int value = -1;

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, (GLint*)&value);

    return value;
}

const char* BF::OpenGL::GLSLVersionPrimary()
{
    return (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
}

void BF::OpenGL::GLSLVersionsSupported(const char*** shaderList, int shaderListSize)
{
    glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &shaderListSize);

    (*shaderList) = Memory::Allocate<const char*>(shaderListSize);

    for (size_t i = 0; i < shaderListSize; i++)
    {
        const char* shaderVersion = (const char*)glGetStringi(GL_SHADING_LANGUAGE_VERSION, i);

        (*shaderList)[i] = shaderVersion;
    }
}

const char* BF::OpenGL::GPUVendorName()
{
    return (const char*)glGetString(GL_VENDOR);
}

const char* BF::OpenGL::GPUModel()
{
    return (const char*)glGetString(GL_RENDERER);
}

void BF::OpenGL::VertexArrayUpdate(int vertexArrayID, int size, void* data)
{
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)size, data);
}

unsigned int BF::OpenGL::ShaderCompile(unsigned int type, char* shaderString)
{
    unsigned int id = glCreateShader(type);

    glShaderSource(id, 1, &shaderString, nullptr);
    glCompileShader(id);

    // Error handling
    {
        int result;

        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int lengh;

            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lengh);
            char* message = Memory::Allocate<char>(lengh);

            glGetShaderInfoLog(id, lengh, &lengh, message);

            printf
            (
                "[x][OpenGL][Shader] Failed to compile <%s>!\n"
                "+-------------------------------------------------------+\n"
                "| GSGL - Shader compile error log                       |\n"
                "+-------------------------------------------------------+\n"
                "%s"
                "+-------------------------------------------------------+\n",
                "N/A",//ShaderTypeToString(type),
                message
            );

            Memory::Release(message, lengh);

            glDeleteShader(id);

            return -1;
        }
    }

    return id;
}

void BF::OpenGL::VertexAttributeArrayDefine(const unsigned int sizeOfElement, const unsigned int listSize, const unsigned int* list)
{
    int offset = 0;
    int wholeBlockSize = 0;
    int currentBlockSize = 0;

    for (unsigned int vertexAtributeIndex = 0; vertexAtributeIndex < listSize; vertexAtributeIndex++)
    {
        int vertexSize = list[vertexAtributeIndex];

        wholeBlockSize += vertexSize;
    }

    wholeBlockSize *= sizeOfElement;

    for (unsigned int vertexAtributeIndex = 0; vertexAtributeIndex < listSize; vertexAtributeIndex++)
    {
        int vertexSize = list[vertexAtributeIndex];

        glEnableVertexAttribArray(vertexAtributeIndex);
        glVertexAttribPointer(vertexAtributeIndex, vertexSize, GL_FLOAT, GL_FALSE, wholeBlockSize, (void*)offset);

        currentBlockSize += vertexSize;
        offset = sizeOfElement * currentBlockSize;
    }
}

void BF::OpenGL::VertexArrayDefine(unsigned int* vertexArrayID)
{
    glGenVertexArrays(1, vertexArrayID);
}

void BF::OpenGL::VertexDataDefine(unsigned int* vertexID, int size, void* data)
{
    glGenBuffers(1, vertexID); // Get BufferID
    glBindBuffer(GL_ARRAY_BUFFER, *vertexID); // Select Buffer
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void BF::OpenGL::IndexDataDefine(unsigned int* indexID, int size, void* data)
{
    glGenBuffers(1, indexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

int BF::OpenGL::ShaderGetUniformLocationID(int shaderID, const char* UniformName)
{
    const bool valid = (shaderID != -1) && (UniformName != nullptr);

    if(!valid)
    {
        return -1;
    }

    {
        const int uniformLocationID = glGetUniformLocation(shaderID, UniformName);

        return uniformLocationID;
    }
}

void BF::OpenGL::ShaderSetUniformMatrix4x4(const int matrixUniformID, const float* matrix)
{
    const bool valid = matrixUniformID != -1;

    if (!valid)
    {
        return;     
    }

    glUniformMatrix4fv(matrixUniformID, 1, GL_FALSE, matrix);
}

void BF::OpenGL::ShaderSetUniformVector3(int vector3UniformID, float x, float y, float z)
{
    if (vector3UniformID != -1)
    {
        glUniform3f(vector3UniformID, x, y, z);
    }
}

void BF::OpenGL::ShaderSetUniformVector4(int vector3UniformID, float x, float y, float z, float w)
{
    if (vector3UniformID != -1)
    {
        glUniform4f(vector3UniformID, x, y, z, w);
    }
}

#endif