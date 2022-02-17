#include "OpenGL.h"

#include <cassert>
#include <GL/glew.h>

#include "../Shader/Shader.h"

#define GLC  BF::OpenGL::CallErrorCheck();

void BF::OpenGL::ErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{ 
    bool openGLspecific = type == GL_DEBUG_TYPE_ERROR;
    const char* sourceText = 0;
    const char* typeText = 0;
    const char* servertyText = 0;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:
            sourceText = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            sourceText = "Window";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            sourceText = "Shader";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            sourceText = "3rd Party";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            sourceText = "Application";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            sourceText = "Other";
            break;

        default:
            break;
    }

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            typeText = "Error";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeText = "DEPRECATED_BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeText = "UNDEFINED_BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            typeText = "PORTABILITY";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            typeText = "PERFORMANCE";
            break;

        case GL_DEBUG_TYPE_OTHER:
            typeText = "OTHER";
            break;

        case GL_DEBUG_TYPE_MARKER:
            typeText = "MARKER";
            break;

        case GL_DEBUG_TYPE_PUSH_GROUP:
            typeText = "PUSH_GROUP";
            break;

        case GL_DEBUG_TYPE_POP_GROUP:
            typeText = "POP_GROUP";
            break;

        default:
            break;
    }

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            servertyText = "High";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            servertyText = "Medium";
            break;

        case GL_DEBUG_SEVERITY_LOW:
            servertyText = "Low";
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            servertyText = "Info";
            break;

        default:
            break;
    }
    

    // (0x%x)

    fprintf
    (
        stderr,
        "[x][OpenGL][%s][%s][%s] %s\n",
        sourceText,        
        typeText,        
        servertyText,
        message
    );
}

void BF::OpenGL::CallErrorCheck()
{
    /*
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        printf("[x][OpenGL] Error detected : %i\n", err);
    }*/
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
    assert(shaderProgramID != -1);

    glUseProgram(shaderProgramID);

    return 0;
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

void BF::OpenGL::RenderClear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1);
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

    (*shaderList) = (const char**)malloc(shaderListSize * sizeof(const char**));

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
            char* message = (char*)malloc(lengh * sizeof(char));

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

            free(message);

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
    return glGetUniformLocation(shaderID, UniformName);
}

void BF::OpenGL::ShaderSetUniformMatrix4x4(const int matrixUniformID, const float* matrix)
{
    if (matrixUniformID != -1)
    {
        glUniformMatrix4fv(matrixUniformID, 1, GL_FALSE, matrix);
    }
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