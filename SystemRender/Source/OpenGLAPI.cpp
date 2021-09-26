#include "OpenGLAPI.h"

#include <GL/glew.h>
#include <cassert>

void BF::OpenGLAPI::RegisterImage(Image& image)
{
    unsigned int& imageID = image.ID;
    unsigned int format = ToImageFormat(image.Format);
    unsigned int textureType = ToImageType(image.Type);
   // bool validFormat = image.Type == ImageType::Texture2D || image.Type == ImageType::Texture3D;

    if (image.PixelData == nullptr)
    {
        return;
    }

    glGenTextures(1, &imageID);

    glBindTexture(textureType, imageID);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, ImageWrapToOpenGLFormat(image.WrapWidth));
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, ImageWrapToOpenGLFormat(image.WrapHeight));

    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, ImageLayoutToOpenGLFormat(image.LayoutNear));
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, ImageLayoutToOpenGLFormat(image.LayoutFar));

    //glTexParameterf(textureType, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

    glTexImage2D(textureType, 0, GL_RGB, image.Width, image.Height, 0, format, GL_UNSIGNED_BYTE, image.PixelData);

    glGenerateMipmap(textureType);

    glBindTexture(textureType, 0);
}

void BF::OpenGLAPI::SkyBoxUse(SkyBox& skybox)
{
    OpenGLAPI::VertexArrayBind(skybox.VAOID);
    OpenGLAPI::TextureUse(ImageType::TextureCubeContainer, skybox.ID);
}

void BF::OpenGLAPI::SkyBoxSet(SkyBox& skybox)
{
    glGenTextures(1, &skybox.ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.ID);

    for (unsigned int i = 0; i < 6; i++)
    {   
        Image& image = skybox.Faces[i];        
        unsigned int textureTypeID = (unsigned int)GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
        unsigned int imageID = ToImageFormat(image.Format);

        image.Type = ToImageType(textureTypeID);        

        //glActiveTexture(GL_TEXTURE0 + i);

        glTexImage2D(textureTypeID, 0, GL_RGB, image.Width, image.Height, 0, imageID, GL_UNSIGNED_BYTE, image.PixelData);
    }    

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    OpenGLAPI::VertexArrayDefine(&skybox.VAOID);
    OpenGLAPI::VertexArrayBind(skybox.VAOID);

    OpenGLAPI::VertexDataDefine(&skybox.VBOID, sizeof(float) * 108u, skybox.SkyboxVertices);

    unsigned int vertexstuff[1] = { 3 };

    OpenGLAPI::VertexAttributeArrayDefine(sizeof(float), 1, vertexstuff);

    OpenGLAPI::IndexDataDefine(&skybox.IndexID, 36u* sizeof(unsigned int), skybox.IndexList);
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

void BF::OpenGLAPI::DrawOrder(bool clockwise)
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

void BF::OpenGLAPI::TextureUse(ImageType imageType, int textureID)
{
    assert(textureID != -1);

   // glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture

    unsigned int imageTypeID = ToImageType(imageType);    

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

    glPointSize(40);
    glLineWidth(30);

    switch (renderMode)
    {
        case RenderMode::Point:      
            mode = GL_POINTS;
            break;

        case RenderMode::Line:           
            mode = GL_LINES;
            break;        

        case RenderMode::LineAdjacency:
            mode = GL_LINES_ADJACENCY;
            break;

        case RenderMode::LineStripAdjacency:
            mode = GL_LINE_STRIP_ADJACENCY;
            break;

        case RenderMode::LineLoop:
            mode = GL_LINE_LOOP;
            break;

        case RenderMode::LineStrip:
            mode = GL_LINE_STRIP;
            break;

        case RenderMode::Triangle:
            mode = GL_TRIANGLES;
            break;

        case RenderMode::TriangleAdjacency:
            mode = GL_TRIANGLES_ADJACENCY;
            break;

        case RenderMode::TriangleFAN:
            mode = GL_TRIANGLE_FAN;
            break;

        case RenderMode::TriangleStrip:
            mode = GL_TRIANGLE_STRIP;
            break;

        case RenderMode::TriangleStripAdjacency:
            mode = GL_TRIANGLE_STRIP_ADJACENCY;
            break;

        case RenderMode::Square:
            mode = GL_QUADS;
            break;

        case RenderMode::Patches:
            mode = GL_PATCHES;
            break;
    } 



    //glDrawElements(mode, amount, GL_UNSIGNED_INT, 0);
    glDrawArrays(mode, startIndex, amount);

    /*
    bool wireFrame = true;
    if (wireFrame)
    {
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);

        glDrawArrays(GL_POLYGON, startIndex, amount);

        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }
    */

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

const char* BF::OpenGLAPI::GPUVendorName()
{
    return (const char*)glGetString(GL_VENDOR);;
}

const char* BF::OpenGLAPI::GPUModel()
{
    return (const char*)glGetString(GL_RENDERER);;
}

void BF::OpenGLAPI::VertexArrayUpdate(int vertexArrayID, int size, void* data)
{
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)size, data);
}

bool BF::OpenGLAPI::ShaderCompile(ShaderProgram& shaderProgram)
{
    bool isValidShader = false;
    bool isLoaded = shaderProgram.IsLoaded();

    if (!isLoaded)
    {
        return false;
    }

    shaderProgram.ID = glCreateProgram();

    for (unsigned int i = 0; i < 2; i++)
    {
        Shader& shader = shaderProgram.ShaderList[i];
        unsigned int type = ToShaderType(shader.Type);
     
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
                ShaderTypeToString(type),
                message
            );

            free(message);

            glDeleteShader(id);

            return -1;
        }
    }

    return id;
}

void BF::OpenGLAPI::VertexAttributeArrayDefine(unsigned int sizeOfElement, unsigned int listSize, unsigned int* list)
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








BF::ShaderType BF::OpenGLAPI::ToShaderType(unsigned int token)
{
    return ShaderType();
}

unsigned int BF::OpenGLAPI::ToShaderType(ShaderType shaderType)
{
    switch (shaderType)
    {
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;

        case   ShaderType::TessellationControl:
            return -1; // ???

        case   ShaderType::TessellationEvaluation:
            return -1; // ???

        case   ShaderType::Geometry:
            return GL_GEOMETRY_SHADER;

        case   ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;

        case  ShaderType::Compute:
            return GL_COMPUTE_SHADER;

        case ShaderType::Unkown:
        default:
            return -1;
    }
}

BF::ImageFormat BF::OpenGLAPI::ToImageFormat(unsigned int token)
{
    return ImageFormat();
}

unsigned int BF::OpenGLAPI::ToImageFormat(ImageFormat imageFormat)
{
    switch (imageFormat)
    {
        case ImageFormat::BGR:
            return GL_BGR;

        case ImageFormat::BGRA:
            return GL_BGRA;

        case ImageFormat::RGB:
            return GL_RGB;

        case ImageFormat::RGBA:
            return GL_RGBA;

        case ImageFormat::AlphaMask:
        default:
            return -1;
    }
}

unsigned int  BF::OpenGLAPI::ToImageType(ImageType imageType)
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

