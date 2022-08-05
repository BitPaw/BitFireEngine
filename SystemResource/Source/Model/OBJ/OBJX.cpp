#include "OBJX.h"

#include <File/File.h>
#include <Text/Text.h>

#include <Memory/MemoryX.h>

#include <cassert>
#include <cstring>

BF::OBJX::OBJX()
{
    OBJConstruct(this);
}

BF::OBJX::~OBJX()
{
    OBJDestruct(this);
}

float* BF::OBJX::GlobalVertexPosition(size_t index)
{
    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& objElement = ElementList[i];
        size_t arraySize = objElement.VertexPositionListSize;
        bool isInThisElement = index <= arraySize;

        if (isInThisElement)
        {
            return &objElement.VertexPositionList[index];
        }

        index -= arraySize;
    }

    return nullptr;
}

float* BF::OBJX::GlobalTextureCoordinate(size_t index)
{
    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& objElement = ElementList[i];
        size_t arraySize = objElement.TextureCoordinateListSize;
        bool isInThisElement = index <= arraySize;

        if (isInThisElement)
        {
            return &objElement.TextureCoordinateList[index];
        }

        index -= arraySize;
    }

    return nullptr;
}

float* BF::OBJX::GlobalVertexNormalPosition(size_t index)
{
    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& objElement = ElementList[i];
        size_t arraySize = objElement.VertexNormalPositionListSize;
        bool isInThisElement = index <= arraySize;

        if (isInThisElement)
        {
            return &objElement.VertexNormalPositionList[index];
        }

        index -= arraySize;
    }

    return nullptr;
}

float* BF::OBJX::GlobalVertexParameter(size_t index)
{
    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& objElement = ElementList[i];
        size_t arraySize = objElement.VertexParameterListSize;
        bool isInThisElement = index <= arraySize;

        if (isInThisElement)
        {
            return &objElement.VertexParameterList[index];
        }

        index -= arraySize;
    }

    return nullptr;
}

unsigned int* BF::OBJX::GlobalFaceElement(size_t index)
{
    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& objElement = ElementList[i];
        size_t arraySize = objElement.FaceElementListSize;
        bool isInThisElement = index <= arraySize;

        if (isInThisElement)
        {
            return &objElement.FaceElementList[index];
        }

        index -= arraySize;
    }

    return nullptr;
}

bool BF::OBJX::ShouldCreateNewMesh(OBJLineType objLineCommand, bool isCurrentlyInFaces)
{
    if (!isCurrentlyInFaces)
    {
        return false;
    }

    switch (objLineCommand)
    {
        default:
        case OBJLineInvalid:
        case OBJLineNone:;
        case OBJLineComment:
        case OBJLineMaterialLibraryInclude:
        case OBJLineFaceElement:
            return false;

        case OBJLineMaterialLibraryUse:
        case OBJLineVertexGeometric:
        case OBJLineVertexTexture:
        case OBJLineVertexNormal:
        case OBJLineVertexParameter:
        case OBJLineSmoothShading:
        case OBJLineObjectName:
            return true;
    }
}

ActionResult BF::OBJX::Load(const char* filePath)
{
    wchar_t filePathW[PathMaxSize];

    TextCopyAW(filePath, PathMaxSize, filePathW, PathMaxSize);

    const ActionResult fileParsingResult = Load(filePathW);

    return fileParsingResult;
}

ActionResult BF::OBJX::Load(const wchar_t* filePath)
{
    File file;

    FileConstruct(&file);

    {
        const ActionResult fileLoadingResult = FileMapToVirtualMemoryW(&file, filePath, 0, MemoryReadOnly);
        const bool sucessful = fileLoadingResult == ResultSuccessful;

        if(!sucessful)
        {
            return ResultInvalid;
        }
    }

    {
        const ActionResult fileParsingResult = Load(file.Data, file.DataSize, filePath);

        return fileParsingResult;
    }

    FileDestruct(&file);
}

ActionResult BF::OBJX::Load(const unsigned char* data, const size_t dataSize, const wchar_t* fileName)
{
    size_t bytesRead = 0;

    OBJParse(this, data, dataSize, &bytesRead, fileName);

    return ResultSuccessful;
}

ActionResult BF::OBJX::Save(const wchar_t* filePath)
{
    return ResultSuccessful;
}

ActionResult BF::OBJX::ConvertTo(Model& model)
{
    bool usedNormals = false;     
 
    for (size_t materialFileIndex = 0; materialFileIndex < MaterialFileListSize; materialFileIndex++)
    {
        MTL& mtl = MaterialFileList[materialFileIndex];
        size_t materialListSize = mtl.MaterialListSize;

        model.MaterialListSize = materialListSize;
        model.MaterialList = new Material[materialListSize];

        for (size_t materialIndex = 0; materialIndex < materialListSize; materialIndex++)
        {
            const MTLMaterial& mtlMaterial = mtl.MaterialList[materialIndex];
            Material& material = model.MaterialList[materialIndex];

            TextCopyAW(mtlMaterial.Name, MTLNameSize, material.Name, MaterialNameLength);
            TextCopyAW(mtlMaterial.TextureFilePath, MTLFilePath, material.TextureFilePath, MaterialTextureFilePathLength);
                       
            const size_t trippleFloat = 3u * sizeof(float);

            MemoryCopy(mtlMaterial.Ambient, trippleFloat, material.Ambient, trippleFloat);
            MemoryCopy(mtlMaterial.Diffuse, trippleFloat, material.Diffuse, trippleFloat);
            MemoryCopy(mtlMaterial.Specular, trippleFloat, material.Specular, trippleFloat);
            MemoryCopy(mtlMaterial.Emission, trippleFloat, material.Emission, trippleFloat);
        }
    }

    model.MeshListSize = 1;
    model.MeshList = new Mesh[1];  

    Mesh& mesh = *model.MeshList;

    mesh.VertexDataStructureListSize = 4;
    mesh.VertexDataStructureList[0] = 3;
    mesh.VertexDataStructureList[1] = 3;
    mesh.VertexDataStructureList[2] = 4;
    mesh.VertexDataStructureList[3] = 2;

    //Text::Copy(mesh.Name, Name, OBJElementNameLength);

    mesh.SegmentListSize = ElementListSize;
    mesh.SegmentList = new MeshSegment[ElementListSize];

    for(size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& element = ElementList[i];
        MeshSegment& meshSegment = mesh.SegmentList[i];
        const size_t faceElementListSize = element.FaceElementListSize;
        const size_t verexDataSize = faceElementListSize * (3 + 3 + 4 + 2);

        TextCopyAW(element.Name, OBJElementNameLength, meshSegment.Name, MeshSegmentNameLength);

        mesh.VertexDataListSize = verexDataSize;
        mesh.VertexDataList = (float*)MemoryAllocate(sizeof(float) * verexDataSize);


        // mesh.Structure.RenderType = VertexStructureSize == 4 ? RenderMode::Square : RenderMode::Triangle;
        //mesh.VertexDataStructureListSize

        meshSegment.IndexDataListSize = faceElementListSize;
        meshSegment.IndexDataList = (unsigned int*)MemoryAllocate(sizeof(unsigned int) * faceElementListSize);

        //meshSegment. = malloc .Allocate(faceElementListSize * (3 + 3 + 4 + 2), faceElementListSize);
        //mesh.RenderInfo.MaterialID = element.MaterialListIndex;

        size_t vertecDataIndex = 0;
        float* vertexDataArray = mesh.VertexDataList;


        if(element.MaterialInfoSize > 0)
        {
            meshSegment.MaterialInfoSize = element.MaterialInfoSize;
            meshSegment.MaterialInfo = new OBJElementMaterialInfo[element.MaterialInfoSize];

            for(size_t i = 0; i < element.MaterialInfoSize; i++)
            {
                const OBJElementMaterialInfo& infoA = element.MaterialInfo[i];
                OBJElementMaterialInfo& infoB = meshSegment.MaterialInfo[i];

                infoB.MaterialIndex = infoA.MaterialIndex;
                infoB.Size = infoA.Size/3;
            }
        }
        else
        {
            meshSegment.MaterialInfoSize = 1;
            meshSegment.MaterialInfo = new OBJElementMaterialInfo[1];
            meshSegment.MaterialInfo->Size = element.FaceElementListSize/3;
            meshSegment.MaterialInfo->MaterialIndex = -1;
        }

        float fallback[3] = { 0,0,0 };

        for (size_t i = 0; i < faceElementListSize; i += 3)
        {
            const unsigned int* indexPosition = &element.FaceElementList[i];
            unsigned int vertexPositionID = (indexPosition[0] - 1u) * 3u;
            unsigned int texturePointID= (indexPosition[1] - 1u) * 2u; // TODO: REMOVED -1 form all positions
            unsigned int normalVectorID = (indexPosition[2] - 1u) *3u;
            float* vertexData = GlobalVertexPosition(vertexPositionID);
            float* textureData = GlobalTextureCoordinate(texturePointID);
            float* normalData = GlobalVertexNormalPosition(normalVectorID);
            Vector4<float> color(1.0f, 1.0f, 1.0f, 1.0f);
            const bool vertexPositionIDValid = vertexData;
            const bool texturePointIDValid = textureData;
            const bool normalVectorIDValid = normalData;

#if 1 // failsafe
            if (!vertexPositionIDValid)
            {
                ++vertexPositionID;
                vertexData = GlobalVertexPosition(vertexPositionID);
            }


            if (!texturePointIDValid)
            {
                textureData = fallback;
                //++texturePointID;
               // textureData = GlobalTextureCoordinate(texturePointID);
            }

            if (!normalVectorIDValid)
            {
               // ++normalVectorID;
               // normalData = GlobalVertexNormalPosition(normalVectorID);

                normalData = fallback;
            }



#elif
            assert(vertexPositionIDValid);
            assert(texturePointIDValid);
            assert(normalVectorIDValid);
#endif // failsafe         


            const unsigned int dataSize = 12u;
            float data[dataSize]
            {
                vertexData[0],
                vertexData[1],
                vertexData[2],
                normalData[0],
                normalData[1],
                normalData[2],
                color.X,
                color.Y,
                color.Z,
                color.W,
                textureData[0],
                textureData[1]
            };

            meshSegment.IndexDataList[i] = i;

            MemoryCopy(data, sizeof(float) * dataSize, vertexDataArray + vertecDataIndex, -1);

            vertecDataIndex += dataSize;        
        }
    } 

    return ResultSuccessful;
}

ActionResult BF::OBJX::ConvertFrom(Model& model)
{
    return ResultSuccessful;
}

void BF::OBJX::Clear()
{
    delete[] MaterialFileList;
    delete[] ElementList;

    VertexStructureSize = 0xFF;
    MaterialFileListSize = 0;
    MaterialFileList = 0;
    ElementListSize = 0;
    ElementList = 0;
}

void BF::OBJX::PrintData()
{
    /*
    const char* line = "+-------+-------+-------+-------+-------+-------------------+------------------|\n";

    printf(line);
    printf("| (OBJ) Name: %-64ls |\n", Name);
    printf(line);


    for(size_t i = 0; i < ElementListSize; i++)
    {
        const OBJElement& element = ElementList[i];

        for(size_t j = 0; j < element.MaterialInfoSize; j++)
        {
            const OBJElementMaterialInfo& info = element.MaterialInfo[j];

            printf("[>>>] Part (%2i/%2i) | Size:%i MaterialID:%i\n", j+1, element.MaterialInfoSize, info.Size, info.MaterialIndex);
        }
    }

#if 0
    printf
    (
        "| %5s | %5s | %5s | %5s | %5s | %-17s | %-16s |\n",
        "VertP", "NormP", "TextC", "ParaV", "Face", "Mesh-Name", "Material-Name");
    printf(line);

    for (unsigned int i = 0; i < ElementListSize; i++)
    {
        const OBJElement& waveFrontElement = ElementList[i];

        size_t sizePos = waveFrontElement.VertexPositionList.Size();
        size_t sizeNormal = waveFrontElement.VertexNormalPositionList.Size();
        size_t sizeText = waveFrontElement.TextureCoordinateList.Size();
        size_t sizePara = waveFrontElement.VertexParameterList.Size();
        size_t sizeFace = waveFrontElement.FaceElementList.Size();
        char* materialName = nullptr;

        /*
        if (waveFrontElement->MaterialListIndex != -1)
        {
            materialName = MaterialFileList[0].MaterialList[waveFrontElement->MaterialListIndex].Name;
        }* /

        printf
        (
            "| %5u | %5u | %5u | %5u | %5u | %-17s | %-16s |\n", 
            sizePos, 
            sizeNormal, 
            sizeText,
            sizePara, 
            sizeFace, 
            0, //&waveFrontElement->Name[0],
            materialName
        );
    }

    printf(line);
#endif

    if (MaterialFileListSize == 0)
    {
        printf("| %-76s |\n", "---<No Materials>---");
        printf(line);
    }

    for (unsigned int i = 0; i < MaterialFileListSize; i++)
    {
        MTL& mtl = MaterialFileList[i];        

        for (unsigned int j = 0; j < mtl.MaterialListSize; j++)
        {
            MTLMaterial& material = mtl.MaterialList[j];
            
            printf("| Material ID   | %-29u | Ambient  [%4.3f|%4.3f|%4.3f] |\n", j, material.Ambient[0], material.Ambient[1], material.Ambient[2]);
            printf("| Material Name | %-29s | Diffuse  [%4.3f|%4.3f|%4.3f] |\n", material.Name, material.Diffuse[0], material.Diffuse[1], material.Diffuse[2]);
            printf("| Texture Path  | %-29.29s | Specular [%4.3f|%4.3f|%4.3f] |\n", material.TextureFilePath, material.Specular[0], material.Specular[1], material.Specular[2]);
            printf("+---------------+-------------------------------+------------------------------+\n");
        }
    }  

    */
}