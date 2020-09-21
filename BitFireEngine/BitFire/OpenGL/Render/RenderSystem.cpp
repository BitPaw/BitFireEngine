#include "RenderSystem.h"


    /*
    _dataCache->VertexData.CalculateByteSize();

    GLsizeiptr vArraySize = _dataCache->VertexData.SizeInBytes.Current;


    try
    {       

        glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vArraySize / 4, _dataCache->VertexData.Data);

    }
    catch (const std::exception& e)
    {
        printf("OpenGL Error: %c", e.what());
    }
    */


void BF::RenderSystem::AllocateGPUCache()
{
    unsigned int blockSize = _dataCache->VertexData.DataBlockSizeInBytes;

    unsigned int vertexDataSize = _dataCache->VertexData.SizeInBytes.Maximal;

    unsigned int indexDataSize = _dataCache->IndexData.SizeInBytes.Maximal;
    unsigned int* indexData = _dataCache->IndexData.Data;

    // setIndi
    {
        unsigned int offset = 0;

        for (unsigned int i = 0; i < _dataCache->IndexData.Size.Maximal + 6; i += 6)
        {
            indexData[i + 0] = 0 + offset;
            indexData[i + 1] = 1 + offset;
            indexData[i + 2] = 2 + offset;

            indexData[i + 3] = 2 + offset;
            indexData[i + 4] = 3 + offset;
            indexData[i + 5] = 0 + offset;

            offset += 4;
        }
    }

    const unsigned int vertexSize = 3;
    const unsigned int normalSize = 3;
    const unsigned int colorSize = 4;
    const unsigned int textureSize = 2;

    glGenVertexArrays(1, &_vertexArrayObjectID);
    glBindVertexArray(_vertexArrayObjectID);

    glGenBuffers(1, &_bufferID); // Get BufferID
    glBindBuffer(GL_ARRAY_BUFFER, _bufferID); // Select Buffer
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize, nullptr, GL_DYNAMIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, vertexSize, GL_FLOAT, GL_FALSE, blockSize, 0);

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, normalSize, GL_FLOAT, GL_FALSE, blockSize, (void*)(sizeof(float) * (vertexSize)));

    // Color
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, colorSize, GL_FLOAT, GL_FALSE, blockSize, (void*)(sizeof(float) * (vertexSize + normalSize)));

    // TextureCoordinate
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, textureSize, GL_FLOAT, GL_FALSE, blockSize, (void*)(sizeof(float) * (vertexSize + normalSize + colorSize)));



    glGenBuffers(1, &_indiceBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indiceBuffer); // Select
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_DYNAMIC_DRAW);


    _dataCache->VertexBufferID = _bufferID;
    _dataCache->IndexBufferID = _indiceBuffer;

    glLineWidth(10);
    glPointSize(5);

    //UnBindBuffer();
}


void BF::RenderSystem::UpdateModel(RenderModel* renderModel)
{
    
}

void BF::RenderSystem::UpdatePosition(RenderModel* renderModel)
{
    /*
    float* vertexDataPos = _dataCache->VertexData.Data;
    RenderInformation* renderInformation = _dataCache->GetRenderInformation(renderModel);

    unsigned int startPosition = renderInformation->VertexDataPosition;
    unsigned int objectLength = renderModel->GlobalMesh.VertexList.Size.Value;
    const unsigned int vertexDataLengh = 3;
    const unsigned int otherDataLengh = (3 + 4 + 2);

    unsigned int bCounter = 0;

    glBindBuffer(GL_ARRAY_BUFFER, _bufferID);

    for (unsigned int i = 0; i < objectLength; i++)
    {
        if (bCounter++ >= vertexDataLengh)
        {
            vertexDataPos += otherDataLengh;
        }
        
       

        vertexDataPos += i;
    }   

    glBufferSubData(GL_ARRAY_BUFFER, 0, vArraySize / 4, );
    */
}

void BF::RenderSystem::UpdateNormals(RenderModel* renderModel)
{

}

BF::RenderSystem::RenderSystem(Player* player)
{
    _currentPlayer = player;
    _dataCache = new RenderDataCache(100000000);

    AllocateGPUCache();
}

void BF::RenderSystem::RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1);        

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

    glDrawElements(GL_TRIANGLES, _dataCache->IndexData.Size.Current, GL_UNSIGNED_INT, nullptr);
   // glDrawElements(GL_LINE_LOOP, _dataCache->IndexData.Size.Current, GL_UNSIGNED_INT, nullptr);
    //glDrawElements(GL_POINTS, _dataCache->IndexData.Size.Current, GL_UNSIGNED_INT, nullptr);
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

    if (false)// Texture
    {
        unsigned int texture;
        glGenTextures(1, &texture);

        unsigned int width;
        unsigned int height;

        //_front = BitMapFontLoader::LoadBitMapFont("C:/_WorkSpace/C++/Data/arial.fnt");
        _texture = BitMapLoader::LoadFromFile("C:/_WorkSpace/C++/old/Data/F/A.bmp");

        width = _texture.InformationHeader->Width;
        height = _texture.InformationHeader->Height;

        //BitMapLoader::PrintBitMapInformation(boxTexture);
        _pixelArray = BitMapLoader::GeneratePixelArray(_texture);

        //PixelArrayLoader::PrintPixelArray(pixelarray);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixelArray.PixelData);
        glGenerateMipmap(GL_TEXTURE_2D);

    }

    //_camera.Settings->Mode = CameraMode::Perspectdive;

    printf("SHADER ID %i | %i | %i | %i\n", _shaderID, _modelViewProjectionID, _inverseModelViewID, _modelViewID);
}

void BF::RenderSystem::RegisterRenderModel(RenderModel* renderModel)
{
    _dataCache->UpdateDataLink(renderModel);
}

int BF::RenderSystem::UnRegisterRenderModel(RenderModel* renderModel)
{
    return -1;
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