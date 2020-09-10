#include "RenderDataCache.h"

RenderInformation* BF::RenderDataCache::GetRenderInformation(RenderModel* renderModel)
{
    RenderInformation* renderInformation = nullptr;

    for (unsigned int i = 0; i < _renderObjectCounter; i++)
    {
        RenderInformation* targetRenderInformation = &_renderInformationCache[i];
        bool isSameObject = targetRenderInformation->Model == renderModel;

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

    for (unsigned int i = 0; i < indiceData->Size.Value; i++)
    {
        IndexData.Data[IndexData.Size.Current++] = i + _faceModelOffset;

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

        VertexData.Size.Current += (3 + 3 + 4 + 2);

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

    for (unsigned int i = 0; i < IndexData.Size.Current; i++)
    {
        unsigned int index = IndexData.Data[i];

        if (index > _faceModelOffset)
        {
            _faceModelOffset = index;
        }
    }

    _faceModelOffset++;
}

void BF::RenderDataCache::UpdateDataLink(RenderModel* renderModel)
{
    RenderInformation* renderInformation = GetRenderInformation(renderModel);
    bool isAlreadyLinked = renderInformation != nullptr;
    
    if (isAlreadyLinked)
    {
        Update(renderInformation);
    }
    else
    {      
        renderInformation = &_renderInformationCache[_renderObjectCounter];

        renderInformation->RenderID = _renderObjectCounter++;
        renderInformation->ShouldItBeRendered = true;
        renderInformation->Model = renderModel;
        renderInformation->VertexDataPosition = VertexData.Size.Current;

        Update(renderInformation);
    }

  //  printf("[%.2x][MODEL] <%s> : %s\n", renderInformation->RenderID, renderModel->ModelName.c_str(), (isAlreadyLinked ? "Update" : "Registered"));
}