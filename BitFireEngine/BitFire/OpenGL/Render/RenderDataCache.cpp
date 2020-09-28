#include "RenderDataCache.h"

RenderInformation* BF::RenderDataCache::GetRenderInformation(RenderModel* renderModel)
{
    RenderInformation* renderInformation = nullptr;

    for (unsigned int i = 0; i < _renderObjectCounter; i++)
    {
        RenderInformation* targetRenderInformation = &_renderInformationCache[i];
        bool isSameObject = targetRenderInformation->Model->ModelID == renderModel->ModelID;

        if (isSameObject)
        {
            renderInformation = targetRenderInformation;
            break;
        }
    }

    return renderInformation;
}

BF::RenderDataCache::RenderDataCache(unsigned int bufferSize)
{
    _renderInformationCache.ReSize(20);

	VertexData.AllocateSpace(bufferSize);
	IndexData.AllocateSpace(bufferSize);
}

void BF::RenderDataCache::Update(RenderInformation* renderInformation)
{
    RGBA defaultColor;
    Point defaultTexturepoint;
    Position normalPosition;

    Vertex* vertex;
    RGBA* color;
    Position* position;
    Position* normal;
    Point* texture;

    RenderModel* renderModel = renderInformation->Model;

    LinkedMesh* mesh = &renderInformation->Model->GlobalMesh;
    List<MeshIndexData*>* indiceData = &mesh->IndexList;
   
    unsigned int dataIndex = renderInformation->VertexDataPosition;
    unsigned int indiceIndex = renderInformation->IndiceIndex;

    for (unsigned int i = 0; i < indiceData->Size.Value; i++)
    {      
        IndexData.Data[indiceIndex++] = i + renderInformation->IndexOffset;
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

        VertexData.Data[dataIndex++] = position->X;
        VertexData.Data[dataIndex++] = position->Y;
        VertexData.Data[dataIndex++] = position->Z;

        VertexData.Data[dataIndex++] = normal->X;
        VertexData.Data[dataIndex++] = normal->Y;
        VertexData.Data[dataIndex++] = normal->Z;

        VertexData.Data[dataIndex++] = color->Red;
        VertexData.Data[dataIndex++] = color->Green;
        VertexData.Data[dataIndex++] = color->Blue;
        VertexData.Data[dataIndex++] = color->Alpha;

        VertexData.Data[dataIndex++] = texture->X;
        VertexData.Data[dataIndex++] = texture->Y;       
    }

    renderInformation->VertexDataLength = dataIndex - renderInformation->VertexDataPosition -1;
    renderInformation->IndiceIndexLength = indiceIndex - renderInformation->IndiceIndex-1;
}

void BF::RenderDataCache::UpdateDataLink(RenderModel* renderModel)
{
    if (renderModel == nullptr)
    {
        printf("\n\nInvalid Call\n\n");
        return;
    }

    RenderInformation* renderInformation = GetRenderInformation(renderModel);
    bool isAlreadyLinked = renderInformation != nullptr;
    
    if (isAlreadyLinked)
    {        
        Update(renderInformation);
        
        RenderInformation* renderInformation = GetRenderInformation(renderModel);
        unsigned int startPosition = renderInformation->VertexDataPosition;
        unsigned int dataSize = renderInformation->VertexDataLength;
        float* vertexDataPos = &VertexData.Data[startPosition];

        startPosition *= sizeof(float);
        dataSize *= sizeof(float);

        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, startPosition, dataSize, vertexDataPos);       
    }
    else
    {      
        renderInformation = &_renderInformationCache[_renderObjectCounter];       
        renderInformation->RenderID = _renderObjectCounter++;
        renderInformation->ShouldItBeRendered = true;
        renderInformation->Model = renderModel;
        renderInformation->VertexDataPosition = VertexData.Size.Current;
        renderInformation->IndiceIndex = IndexData.Size.Current;

        renderModel->ModelID = renderInformation->RenderID;

        // Reserve Space
        {
            unsigned int size = renderModel->GlobalMesh.IndexList.Size.Value;

            IndexData.Size.Current += size;
            VertexData.Size.Current += (3 + 3 + 4 + 2) * size;          
        }

        std::cout << "New Object registered : " << "[ " << renderModel->ModelID << "] " << renderModel->ModelName << std::endl;

        renderInformation->IndexOffset = _faceModelOffset;

        Update(renderInformation);     

        for (unsigned int i = 0; i < IndexData.Size.Current; i++)
        {
            unsigned int index = IndexData.Data[i];

            if (index > _faceModelOffset)
            {
                _faceModelOffset = index;
            }
        }

        _faceModelOffset++;     


        VertexData.CalculateByteSize();
        IndexData.SizeInBytes.Current = IndexData.Size.Current * IndexData.DataBlockSizeInBytes;

        GLsizeiptr vArraySize = VertexData.SizeInBytes.Current;
        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vArraySize, VertexData.Data);
       
        GLsizeiptr iArraySize = IndexData.SizeInBytes.Current;
        glBindBuffer(GL_ARRAY_BUFFER, IndexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, iArraySize, IndexData.Data);
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