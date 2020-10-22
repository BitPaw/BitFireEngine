#include "RenderDataCache.h"

BF::RenderInformation* BF::RenderDataCache::GetRenderInformation(Model* renderModel)
{
    RenderInformation* renderInformation = nullptr;

    for (unsigned int i = 0; i < _renderObjectCounter; i++)
    {
        RenderInformation* targetRenderInformation = &_renderInformationCache[i];
        bool isSameObject = targetRenderInformation->RenderModel->ModelID == renderModel->ModelID;

        if (isSameObject)
        {
            renderInformation = targetRenderInformation;
            break;
        }
    }

    return renderInformation;
}


BF::RenderDataCache::RenderDataCache()
{
    _renderInformationCache.ReSize(20);
 
}



void BF::RenderDataCache::Update(RenderInformation* renderInformation)
{
    RGBA defaultColor = RGBA();
    Point defaultTexturepoint = Point();
    Position normalPosition = Position();

    Vertex* vertex = nullptr;
    RGBA* color = nullptr;
    Position* position = nullptr;
    Position* normal = nullptr;
    Point* texture = nullptr;

    Model* renderModel = renderInformation->RenderModel;

    LinkedMesh* mesh = &renderInformation->RenderModel->GlobalMesh;
    List<MeshIndexData*>* indiceData = &mesh->IndexList;
   
    unsigned int dataIndex = renderInformation->VertexDataPosition;
    unsigned int indiceIndex = renderInformation->IndiceIndex;

    //printf("Update: <%p> <%.2u> %s\n", renderInformation, renderInformation->RenderID, renderInformation->Model->ModelName.c_str());

    if (renderInformation->RenderModel->ModelName == "")
    {
        //printf("YEET\n");
        return;
    }

    for (unsigned int i = 0; i < indiceData->Size.Value; i++)
    {      
        renderInformation->IndexData.Data[indiceIndex++] = i +renderInformation->IndexOffset;
        MeshIndexData* indexData = (*indiceData)[i];

        unsigned int vertexIndex = indexData->VertexPositionID;
        unsigned int textureIndex = indexData->TexturePointID;
        unsigned int normalIndex = indexData->NormalVectorID;

        if (renderModel->GlobalMesh.VertexList.Size.Value < vertexIndex)
        {
            printf("ERROR\n");
        }

        vertex = renderModel->GlobalMesh.VertexList[vertexIndex];
        position = &vertex->CurrentPosition;


        if (renderModel->ColorList.Size.Value > 0 && (vertex->ColorID != -1)) 
        {
            color = &renderModel->ColorList[vertex->ColorID];                 
        }
        else
        {
            color = &defaultColor;
        }

        if (mesh->NormalPointList.Size.Value > 0)
        {
            normal = renderModel->GlobalMesh.NormalPointList[normalIndex];
        }
        else
        {
            normal = &normalPosition;
        }      

        if (mesh->TexturePointList.Size.Value > 0)
        {
            texture = renderModel->GlobalMesh.TexturePointList[textureIndex];
        }
        else
        {
            texture = &defaultTexturepoint;
        }        

        renderInformation->VertexData.Data[dataIndex++] = position->X;
        renderInformation->VertexData.Data[dataIndex++] = position->Y;
        renderInformation->VertexData.Data[dataIndex++] = position->Z;

        renderInformation->VertexData.Data[dataIndex++] = normal->X;
        renderInformation->VertexData.Data[dataIndex++] = normal->Y;
        renderInformation->VertexData.Data[dataIndex++] = normal->Z;

        renderInformation->VertexData.Data[dataIndex++] = color->Red;
        renderInformation->VertexData.Data[dataIndex++] = color->Green;
        renderInformation->VertexData.Data[dataIndex++] = color->Blue;
        renderInformation->VertexData.Data[dataIndex++] = color->Alpha;

        renderInformation->VertexData.Data[dataIndex++] = texture->X;
        renderInformation->VertexData.Data[dataIndex++] = texture->Y;
    }

    renderInformation->VertexDataLength = dataIndex - renderInformation->VertexDataPosition -1;
    renderInformation->IndiceIndexLength = indiceIndex - renderInformation->IndiceIndex-1;
}

void BF::RenderDataCache::DrawAll()
{
    bool wireFrame = false;

    for (unsigned int i = 0; i < _renderObjectCounter; i++)
    {  
        RenderInformation* renderInformation = &_renderInformationCache[i];

        //printf("A:%.2u, V:%.2u, I:%.2u  [%u]\n", renderInformation->VertexArrayID,renderInformation->VertexBufferID, renderInformation->IndexBufferID, renderInformation->RenderID);

        //glBindBuffer(GL_ARRAY_BUFFER,renderInformation->VertexBufferID);
        
        glBindVertexArray(renderInformation->VertexArrayID);

        //glDrawArrays(GL_LINE_LOOP, i, renderInformation->IndiceIndexLength);

        if (wireFrame)
        {
            glDrawElements(GL_LINE_STRIP, renderInformation->IndexData.Size.Maximal, GL_UNSIGNED_INT, nullptr);
        }

        //glDrawElements(GL_TRIANGLES, renderInformation->IndexData.Size.Current, GL_UNSIGNED_INT, nullptr);
        glDrawElements(GL_TRIANGLES, renderInformation->IndexData.Size.Maximal, GL_UNSIGNED_INT, nullptr);
        // glDrawElements(GL_LINE_LOOP, _dataCache->IndexData.Size.Current, GL_UNSIGNED_INT, nullptr);
         //glDrawElements(GL_POINTS, _dataCache->IndexData.Size.Current, GL_UNSIGNED_INT, nullptr);
    }
}

void BF::RenderDataCache::UpdateDataLink(Model* renderModel)
{
    if (renderModel == nullptr)
    {
        throw "Invalid Call";
    }

    bool isAlreadyLinked = renderModel->ModelID != -1;
    RenderInformation* renderInformation;

    if (isAlreadyLinked)
    {        
        renderInformation = GetRenderInformation(renderModel);
        unsigned int startPosition = renderInformation->VertexDataPosition;
        unsigned int dataSize = renderInformation->VertexDataLength;
        float* vertexDataPos = &renderInformation->VertexData.Data[startPosition];

        startPosition *= sizeof(float);
        dataSize *= sizeof(float);

       // glBindBuffer(GL_ARRAY_BUFFER, renderInformation->VertexBufferID);
       // glBufferSubData(GL_ARRAY_BUFFER, startPosition, dataSize, vertexDataPos);       

        Update(renderInformation);

        GLsizeiptr vArraySize = renderInformation->VertexData.Size.Maximal * sizeof(float);

        glBindVertexArray(renderInformation->VertexArrayID);
        glBindBuffer(GL_ARRAY_BUFFER, renderInformation->VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vArraySize, renderInformation->VertexData.Data);

       // GLsizeiptr iArraySize = renderInformation->IndexData.SizeInBytes.Current;
        //glBindBuffer(GL_ARRAY_BUFFER, renderInformation->IndexBufferID);
        //glBufferSubData(GL_ARRAY_BUFFER, 0, iArraySize, renderInformation->IndexData.Data);
    }
    else
    {      
        renderInformation = &_renderInformationCache[_renderObjectCounter];       
        renderInformation->RenderID = _renderObjectCounter++;
        renderInformation->ShouldItBeRendered = true;
        renderInformation->RenderModel = renderModel;


        renderInformation->IndexOffset = renderInformation->FaceModelOffset;

        renderInformation->VertexDataPosition = renderInformation->VertexData.Size.Current;
        renderInformation->IndiceIndex = renderInformation->IndexData.Size.Current;

        renderInformation->VertexData.AllocateSpace(renderModel->GlobalMesh.IndexList.Size.Value * (3+3+4+2));
        renderInformation->IndexData.AllocateSpace(renderModel->GlobalMesh.IndexList.Size.Value);
     
        renderInformation->VertexData.CalculateByteSize();
        renderInformation->IndexData.SizeInBytes.Current = renderInformation->IndexData.Size.Current * renderInformation->IndexData.DataBlockSizeInBytes;

        renderModel->ModelID = renderInformation->RenderID;

        std::cout << "[i] New Object registered : " << "[" << renderModel->ModelID << "] " << renderModel->ModelName << std::endl;
             
        Update(renderInformation);     

        for (unsigned int i = 0; i < renderInformation->IndexData.Size.Current; i++)
        {
            unsigned int index = renderInformation->IndexData.Data[i];

            if (index > renderInformation->FaceModelOffset)
            {
                renderInformation->FaceModelOffset = index;
            }
        }

        renderInformation->FaceModelOffset++;

        // Allocate GPU Buffer        
        const unsigned int vertexSize = 3;
        const unsigned int normalSize = 3;
        const unsigned int colorSize = 4;
        const unsigned int textureSize = 2;
        unsigned int blockSize = renderInformation->VertexData.DataBlockSizeInBytes;
        unsigned int vertexDataSize = renderInformation->VertexData.SizeInBytes.Maximal;
        unsigned int indexDataSize = renderInformation->IndexData.SizeInBytes.Maximal;
        unsigned int* indexData = renderInformation->IndexData.Data;

        //unsigned int blockSize = sizeof(float) * (3 + 3 + 4 + 2);

        glGenVertexArrays(1, &renderInformation->VertexArrayID);
        glBindVertexArray(renderInformation->VertexArrayID);

        unsigned int sizzze = sizeof(float) * renderInformation->VertexData.Size.Maximal;

        glGenBuffers(1, &renderInformation->VertexBufferID); // Get BufferID
        glBindBuffer(GL_ARRAY_BUFFER, renderInformation->VertexBufferID); // Select Buffer
        glBufferData(GL_ARRAY_BUFFER, sizzze, renderInformation->VertexData.Data, GL_STREAM_DRAW);

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

        glGenBuffers(1, &renderInformation->IndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderInformation->IndexBufferID); // Select
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderInformation->IndexData.SizeInBytes.Maximal, renderInformation->IndexData.Data, GL_STATIC_DRAW);


    }
    /*
    printf
    (
        "[MODEL][%.2x] <%p> I<%.4u->%.4u> V<%.4u->%.4u>: <%s> %s\n",

        renderInformation->RenderID,
        renderModel,      
        renderInformation->IndiceIndex,
        renderInformation->IndiceIndexLength,
        renderInformation->VertexDataPosition,
        renderInformation->VertexDataLength,
        renderModel->ModelName.c_str(),
        (isAlreadyLinked ? "Update" : "Registered")    
    );
    */
}