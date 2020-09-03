#include "RenderSystem.h"

void BF::RenderSystem::UpdateGPUCache()
{
    _dataCache->VertexData.CalculateByteSize();

    _dataCache->IndexData.SizeInBytes.Current = _dataCache->IndexData.Size.Current * _dataCache->IndexData.DataBlockSizeInBytes;

    /*
    // Print
    {
        unsigned int length = _dataCache->IndexData.Size.Current;

        for (unsigned int i = 0; i < length; i+= 3)
        {
            printf("[%5u -> %5u -> %5u]\n", _dataCache->IndexData.Data[i], _dataCache->IndexData.Data[i+1], _dataCache->IndexData.Data[i+2]);
        }

        length = _dataCache->VertexData.Size.Current;

        for (unsigned int i = 0; i < length; i += (4+4+4+2))
        {
            Vertex vertex;

            vertex.CurrentPosition.X = _dataCache->VertexData.Data[i];
            vertex.CurrentPosition.Y = _dataCache->VertexData.Data[i+1];
            vertex.CurrentPosition.Z = _dataCache->VertexData.Data[i+2];

            Vertex::PrintVertex(vertex);
        }
    }
    */

    GLsizeiptr vArraySize = _dataCache->VertexData.SizeInBytes.Current;
    GLsizeiptr iArraySize = _dataCache->IndexData.SizeInBytes.Current;

    try
    {
        glBindBuffer(GL_ARRAY_BUFFER, _indiceBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, iArraySize, _dataCache->IndexData.Data);

        glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vArraySize / 4, _dataCache->VertexData.Data);

    }
    catch (const std::exception& e)
    {
        printf("OpenGL Error: %c", e.what());
    }
}

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



    glGenVertexArrays(1, &_vertexArrayObjectID);
    glBindVertexArray(_vertexArrayObjectID);

    glGenBuffers(1, &_bufferID); // Get BufferID
    glBindBuffer(GL_ARRAY_BUFFER, _bufferID); // Select Buffer
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize, nullptr, GL_DYNAMIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, blockSize, 0);

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, blockSize, (void*)(sizeof(float) * (4)));

    // Color
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, blockSize, (void*)(sizeof(float) * (8)));

    // TextureCoordinate
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, blockSize, (void*)(sizeof(float) * (12)));

    glGenBuffers(1, &_indiceBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indiceBuffer); // Select
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_DYNAMIC_DRAW);

    glLineWidth(3);
    glPointSize(5);

    //UnBindBuffer();
}

void BF::RenderSystem::AddRenderModel(RenderModel* renderModel)
{
    RGBA defaultColor;
    Point defaultTexturepoint;

    Vertex* vertex;
    RGBA* color;
    Position* position;
    Position* normal;
    Point* texture;


    LinkedMesh* mesh = &renderModel->GlobalMesh;
    List<MeshIndexData*>* indiceData = &mesh->IndexList;

    //mesh->ObjectBufferIndex = _dataCache->VertexData.Size.Current;

    for (unsigned int i = 0; i < indiceData->Size.Value; i++)
    {
        _dataCache->IndexData.Data[_dataCache->IndexData.Size.Current++] = i + _faceModelOffset;

        MeshIndexData* indexData = (*indiceData)[i];

        unsigned int vertexIndex = indexData->VertexPositionID;
        unsigned int textureIndex = indexData->TexturePointID;
        unsigned int normalIndex = indexData->NormalVectorID;


        vertex = renderModel->GlobalMesh.VertexList[vertexIndex];
        position = &vertex->CurrentPosition;

        if (mesh->ColorList.Size.Value > 0)
        {
            color = renderModel->GlobalMesh.ColorList[vertex->ColorID];
        }
        else
        {
            color = &defaultColor;
        }

        // has normals
        normal = renderModel->GlobalMesh.NormalPointList[normalIndex];


        if (mesh->TexturePointList.Size.Value > 0)
        {
            texture = renderModel->GlobalMesh.TexturePointList[textureIndex];
        }
        else
        {
            texture = &defaultTexturepoint;
        }

        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = position->X;
        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = position->Y;
        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = position->Z;
        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = 1;

        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = normal->X;
        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = normal->Y;
        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = normal->Z;
        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = 1;

        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = color->Red;
        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = color->Green;
        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = color->Blue;
        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = color->Alpha;

        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = texture->X;
        _dataCache->VertexData.Data[_dataCache->VertexData.Size.Current++] = texture->Y;
    }



    for (unsigned int i = 0; i < _dataCache->IndexData.Size.Current; i++)
    {
        unsigned int index = _dataCache->IndexData.Data[i];

        if (index > _faceModelOffset)
        {
            _faceModelOffset = index;
        }
    }

    _faceModelOffset++;

}



void BF::RenderSystem::UpdateMesh(Mesh* mesh)
{
    //ListFloat* vertexData = mesh->GetVertexData();
    //ListUInt* indiceData = mesh->GetIndiceData();
    unsigned int length;
    unsigned int startIndex = mesh->ObjectBufferIndex;

    //length = vertexData->Lengh;    

    /*
    for (unsigned int i = 0; i < length; i++)
    {
      //  _dataCache->VertexData.Data[startIndex++] = vertexData->Data[i];
    }
    */
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
    //glClearColor(0.2f, 0.2f, 0.2f, 1);        

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
    //glDrawElements(GL_LINE_LOOP, _dataCache->IndexData.Size.Current, GL_UNSIGNED_INT, nullptr);
    //glDrawElements(GL_POINTS, _dataCache->IndexData.Size.Current, GL_UNSIGNED_INT, nullptr);
     //buffer.UnBindBuffer();
}

void BF::RenderSystem::AddShader(ShaderFile shaderFile)
{
    _shaderID = ShaderLoader::CreateShader(shaderFile.VertexShader.Content, shaderFile.FragmentShader.Content);

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
        //_texture = BitMapLoader::LoadFromFile("C:/_WorkSpace/C++/Data/F/A.bmp");

       // width = _texture.InformationHeader->Width;
      //  height = _texture.InformationHeader->Height;

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

int BF::RenderSystem::RegisterRenderModel(RenderModel* renderModel)
{
    int renderID = renderModel->RenderID;

    // ???? renderModel->ShouldBeRendered
    unsigned int numberOfMeshes = renderModel->MeshList.Size.Value;

    printf("[MODEL] %s\n", renderModel->ModelName.c_str());


    if (renderID == -1)
    {
        printf("Mesh Added:\n");

        AddRenderModel(renderModel);

        renderID = _dataCache->LoadedObjects++;
    }
    else
    {
        // Update
        printf("MODEL Updated: \n");

        // UpdateMesh(renderModel);
    }
    /*
    for (unsigned int i = 0; i < numberOfMeshes; i++)
    {
        Mesh* mesh = &renderModel->MeshList[i];

        //mesh->GenerateArrayData();


    }    */


    UpdateGPUCache();

    return renderID;
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