#include "RenderSystem.h"

BF::RenderSystem::RenderSystem(Player* player)
{
    _currentPlayer = player;
    _dataCache = new RenderDataCache(); 

    glLineWidth(10);
    glPointSize(5);
}

void BF::RenderSystem::RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.05f, 0.05f, 0.05f, 1);        

    glm::mat4 modelMatr = glm::mat4(1.0f);

    //modelMatr = glm::scale(modelMatr, glm::vec3(1, 1, 1));

    _modelView = _currentPlayer->Camera._view * modelMatr;
    _invModelView = glm::transpose(glm::inverse(_modelView));

    glm::vec3 offset = glm::vec3(0, 0, 0);
    glm::mat4 diff = glm::translate(_currentPlayer->Camera._view, offset);

    _completematrix = _currentPlayer->Camera._projection * diff * modelMatr;

    glUniformMatrix4fv(_modelViewID, 1, GL_FALSE, &_modelView[0][0]);
    glUniformMatrix4fv(_modelViewProjectionID, 1, GL_FALSE, &_completematrix[0][0]);
    glUniformMatrix4fv(_inverseModelViewID, 1, GL_FALSE, &_invModelView[0][0]);

    // UpdateGPUCache();

    _dataCache->DrawAll();


     //buffer.UnBindBuffer();
}

void BF::RenderSystem::AddShader(ShaderFile shaderFile)
{
    _shaderID = ShaderLoader::CreateShader(shaderFile.VertexShader.Lines[0], shaderFile.FragmentShader.Lines[0]);

    glUseProgram(_shaderID);

    _modelViewProjectionID = glGetUniformLocation(_shaderID, "ModelViewProjection");
    _inverseModelViewID = glGetUniformLocation(_shaderID, "ModelView");
    _modelViewID = glGetUniformLocation(_shaderID, "InverseModelView");
    _textureID = glGetUniformLocation(_shaderID, "texture");
    /*
    if (false)// Texture
    {
        unsigned int texture;
        glGenTextures(1, &texture);

        unsigned int width;
        unsigned int height;

        //_front = BitMapFontLoader::LoadBitMapFont("C:/_WorkSpace/C++/Data/arial.fnt");
        _texture = BMPLoader::LoadFromFile("C:/_WorkSpace/C++/old/Data/F/A.bmp");

        width = _texture.InformationHeader->Width;
        height = _texture.InformationHeader->Height;

        //BitMapLoader::PrintBitMapInformation(boxTexture);
        _pixelArray = BMPLoader::GeneratePixelArray(_texture);

        //PixelArrayLoader::PrintPixelArray(pixelarray);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixelArray.PixelData);
        glGenerateMipmap(GL_TEXTURE_2D);

    }*/

    //_camera.Settings->Mode = CameraMode::Perspectdive;



    printf("SHADER ID %i | %i | %i | %i\n", _shaderID, _modelViewProjectionID, _inverseModelViewID, _modelViewID);
}

void BF::RenderSystem::RegisterRenderModel(Model* renderModel)
{
    if (renderModel == nullptr)
    {
        throw "Null reference";
    }

    _dataCache->UpdateDataLink(renderModel);
}

int BF::RenderSystem::UnRegisterRenderModel(Model* renderModel)
{
    return -1;
}

int BF::RenderSystem::RegisterImage(Image* image)
{
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->Width, image->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image->PixelData[0]);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

/*
VertexBuffer::~VertexBuffer()
{
    const unsigned int amount = 1;

    glDeleteBuffers(amount, &_bufferID);
}

void VertexBuffer::BindBuffer()
{
    glBindVertexArray(_vertexArrayObjectID);
}

void VertexBuffer::UnBindBuffer()
{
    glBindVertexArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
}
*/