#include "OpenGLAPI.h"

#include <GL/glew.h>

void BF::OpenGLAPI::RegisterImage(Image& image)
{
    unsigned int& imageID = image.ID;
    unsigned int format;
    bool validFormat = image.Type == ImageType::Texture2D || image.Type == ImageType::Texture3D;

    if (image.PixelData == nullptr)
    {
        return;
    }

    if (!validFormat)
    {
        return;
    }

    switch (image.Format)
    {
        case ImageFormat::RGB:
            format = GL_RGB;
            break;

        case ImageFormat::RGBA:
            format = GL_RGBA;
            break;

        case ImageFormat::BlackAndWhite:
        default:
            throw "Invalid ImageFormat";
    }

    if (imageID == -1)
    {
        glGenTextures(1, &imageID);
    }

    glBindTexture(GL_TEXTURE_2D, imageID);    

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ImageWrapToOpenGLFormat(image.WrapWidth));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ImageWrapToOpenGLFormat(image.WrapHeight));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ImageLayoutToOpenGLFormat(image.LayoutNear));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ImageLayoutToOpenGLFormat(image.LayoutFar));

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

    glTexImage2D(GL_TEXTURE_2D, 0, format, image.Width, image.Height, 0, format, GL_UNSIGNED_BYTE, image.PixelData);
    //glGenerateMipmap(GL_TEXTURE_2D);
}

int BF::OpenGLAPI::ImageWrapToOpenGLFormat(ImageWrap imageWrap)
{
    switch (imageWrap)
    {
        case ImageWrap::NoModification:
            return GL_CLAMP_TO_BORDER;

        case ImageWrap::StrechEdges:
            return GL_CLAMP_TO_EDGE;

        case ImageWrap::StrechEdgesAndMirror:
            return GL_MIRROR_CLAMP_TO_EDGE;

        case ImageWrap::Repeat:
            return GL_REPEAT;

        case ImageWrap::RepeatAndMirror:
            return GL_MIRRORED_REPEAT;
    }
}

int BF::OpenGLAPI::ImageLayoutToOpenGLFormat(ImageLayout layout)
{
    switch (layout)
    {
        case ImageLayout::Nearest:
            return GL_NEAREST;

        case ImageLayout::Linear:
            return GL_LINEAR;

        case ImageLayout::MipMapNearestNearest:
            return GL_NEAREST_MIPMAP_NEAREST;

        case ImageLayout::MipMapLinearNearest:
            return GL_LINEAR_MIPMAP_NEAREST;

        case ImageLayout::MipMapNNearestLinear:
            return GL_NEAREST_MIPMAP_LINEAR;

        case ImageLayout::MipMapLinearLinear:
            return GL_LINEAR_MIPMAP_LINEAR;
    }
}

void BF::OpenGLAPI::SkyBoxUse(SkyBox& skybox)
{
    OpenGLAPI::VertexArrayBind(skybox.VAOID);
    OpenGLAPI::TextureUse(ImageType::TextureCubeContainer, skybox.ID);
}

unsigned int  BF::OpenGLAPI::FromImageType(ImageType imageType)
{
    switch (imageType)
    {
        case ImageType::Texture2D:
            return GL_TEXTURE_2D;

        case ImageType::Texture3D:
            return GL_TEXTURE_3D;

        case ImageType::TextureCubeContainer:
            return GL_TEXTURE_CUBE_MAP;

        case ImageType::TextureCubeRight:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_X;

        case ImageType::TextureCubeLeft:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;

        case ImageType::TextureCubeTop:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;

        case ImageType::TextureCubeDown:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;

        case ImageType::TextureCubeBack:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;

        case ImageType::TextureCubeFront:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;

        default:
            return -1;
    }
}

BF::ImageType BF::OpenGLAPI::ToImageType(unsigned int token)
{
    switch (token)
    {
        case GL_TEXTURE_2D:
            return ImageType::Texture2D;

        case GL_TEXTURE_3D:
            return ImageType::Texture3D;

        case GL_TEXTURE_CUBE_MAP:
            return ImageType::TextureCubeContainer;

        case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
            return ImageType::TextureCubeRight;

        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
            return ImageType::TextureCubeLeft;

        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
            return ImageType::TextureCubeTop;

        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
            return ImageType::TextureCubeDown;

        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
            return ImageType::TextureCubeBack;

        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
            return ImageType::TextureCubeFront;

        default:
            return ImageType::TextureUnkown;
    }
}

void BF::OpenGLAPI::SkyBoxSet(SkyBox& skybox)
{
    glGenTextures(1, &skybox.ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.ID);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++)
    {   
        Image& image = skybox.Faces[i];        
        unsigned int textureTypeID = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;

        image.Type = ToImageType(textureTypeID);

        glTexImage2D(textureTypeID, 0, GL_RGB, image.Width, image.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.PixelData);
    }    

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    OpenGLAPI::VertexArrayDefine(&skybox.VAOID);
    OpenGLAPI::VertexArrayBind(skybox.VAOID);

    OpenGLAPI::VertexDataDefine(&skybox.VBOID, sizeof(float) * 24, skybox.SkyboxVertices);

    int vertexstuff[1] = { 3 };

    OpenGLAPI::VertexAttributeArrayDefine(sizeof(float), 1, vertexstuff);
    OpenGLAPI::IndexDataDefine(&skybox.IndexID, 36 * 4, skybox.IndexData);
}

void BF::OpenGLAPI::DepthMaskEnable(bool enable)
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

void BF::OpenGLAPI::TextureUse(ImageType imageType, int textureID)
{
    assert(textureID != -1, "[BitFireEngine][OpenGL] TextureSlot -1 was selected. You can't do that.");

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture

    unsigned int imageTypeID = FromImageType(imageType);    

    glBindTexture(imageTypeID, textureID);
}

char BF::OpenGLAPI::UseShaderProgram(int shaderProgramID)
{
    glUseProgram(shaderProgramID);

    return 0;
}

void BF::OpenGLAPI::VertexArrayBind(int vertexArrayID)
{
    glBindVertexArray(vertexArrayID);
}

void BF::OpenGLAPI::Render(RenderMode renderMode, int startIndex, int amount)
{
    unsigned int mode = -1;

    switch (renderMode)
    {
        case RenderMode::Point:
            mode = GL_POINTS;
            break;

        case RenderMode::Line:
            mode = GL_LINE_LOOP;
            break;

        case RenderMode::Triangle:
            mode = GL_TRIANGLES;
            break;

        case RenderMode::Square:
            mode = GL_QUADS;
            break;
    }

    glDrawArrays(mode, startIndex, amount);
}

void BF::OpenGLAPI::RenderClear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1);
}

int BF::OpenGLAPI::TextureMaxSlots()
{
    int value = -1;

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (GLint*)&value);

    return value;
}

int BF::OpenGLAPI::TextureMaxLoaded()
{
    int value = -1;

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, (GLint*)&value);

    return value;
}

const char* BF::OpenGLAPI::VersionName()
{
    return (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
}

void BF::OpenGLAPI::VertexArrayUpdate(int vertexArrayID, int size, void* data)
{
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)size, data);
}

bool BF::OpenGLAPI::ShaderCompile(ShaderProgram& shaderProgram)
{
    unsigned int type;
    bool isValidShader = false;
    bool isLoaded = shaderProgram.IsLoaded();

    if (!isLoaded)
    {
        return false;
    }

    shaderProgram.ID = glCreateProgram();

    printf("[i][OpenGL][Shader] Create Program...\n");

    for (unsigned int i = 0; i < 2; i++)
    {
        Shader& shader = shaderProgram.ShaderList[i];

        switch (shader.Type)
        {
            case ShaderType::Vertex:
                type = GL_VERTEX_SHADER;
                break;

            case   ShaderType::TessellationControl:
                type = -1; // ???
                break;

            case   ShaderType::TessellationEvaluation:
                type = -1; // ???
                break;

            case   ShaderType::Geometry:
                type = GL_GEOMETRY_SHADER;
                break;

            case   ShaderType::Fragment:
                type = GL_FRAGMENT_SHADER;
                break;

            case  ShaderType::Compute:
                type = GL_COMPUTE_SHADER;
                break;

            case ShaderType::Unkown:
            default:
                type = -1;
                break;
        }

        printf("[i][OpenGL][Shader] Loading from <%s>... ", shader.FilePath);

        shader.ID = OpenGLAPI::ShaderCompile(type, &shader.Content[0]);

        if (shader.ID == -1)
        {
            isValidShader = false;
            break;
        }

        isValidShader = true;

        glAttachShader(shaderProgram.ID, shader.ID);        
    }

    if (isValidShader)
    {
        glLinkProgram(shaderProgram.ID);
        glValidateProgram(shaderProgram.ID);
        printf("[i][OpenGL][Shader] Program sucessfully created!\n");
    }

    // We used the Shaders above to compile, these elements are not used anymore.
    for (unsigned int i = 0; i < 2; i++)
    {
        Shader* shader = &shaderProgram.ShaderList[i];

        if (shader->ID != -1)
        {
            glDeleteShader(shader->ID);
        }
    }

    return isValidShader;
}

unsigned int BF::OpenGLAPI::ShaderCompile(unsigned int type, char* shaderString)
{
    printf("Detected: <%s-Shader>\n", ShaderTypeToString(type));

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
            char* message = new char[lengh];

            glGetShaderInfoLog(id, lengh, &lengh, message);

            printf
            (
                "[x][OpenGL][Shader] Failed to compile <%s>!\n"
                "+-------------------------------------------------------+\n"
                "| GSGL - Shader compile error log                       |\n"
                "+-------------------------------------------------------+\n"
                "%s"
                "+-------------------------------------------------------+\n",
                ShaderTypeToString(type),
                message
            );

            delete[] message;

            glDeleteShader(id);

            return -1;
        }
    }

    return id;
}

void BF::OpenGLAPI::VertexAttributeArrayDefine(int sizeOfElement, int listSize, int* list)
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

void BF::OpenGLAPI::VertexArrayDefine(unsigned int* vertexArrayID)
{
    glGenVertexArrays(1, vertexArrayID);
}

void BF::OpenGLAPI::VertexDataDefine(unsigned int* vertexID, int size, void* data)
{
    glGenBuffers(1, vertexID); // Get BufferID
    glBindBuffer(GL_ARRAY_BUFFER, *vertexID); // Select Buffer
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void BF::OpenGLAPI::IndexDataDefine(unsigned int* indexID, int size, void* data)
{
    glGenBuffers(1, indexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexID); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

int BF::OpenGLAPI::ShaderGetUniformLocationID(int shaderID, const char* UniformName)
{
    return glGetUniformLocation(shaderID, UniformName);
}

void BF::OpenGLAPI::ShaderSetUniformMatrix4x4(int matrixUniformID, float* matrix)
{
    if (matrixUniformID != -1)
    {
        glUniformMatrix4fv(matrixUniformID, 1, GL_FALSE, matrix);
    }
}

const char* BF::OpenGLAPI::ShaderTypeToString(int type)
{
    switch (type)
    {
        case GL_VERTEX_SHADER:
            return "Vertex";

        case  GL_GEOMETRY_SHADER:
            return "Geometry";

        case  GL_FRAGMENT_SHADER:
            return "Fragment";

        case  GL_COMPUTE_SHADER:
            return "Compute";

        default:
            return "Unkown";
    }
}
