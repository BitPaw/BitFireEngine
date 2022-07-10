#include "OBJ.h"

#include <File/File.h>
#include <Text/Text.h>
#include <Hardware/Memory/Memory.h>

#include <cassert>
#include <cstring>

BF::OBJ::OBJ()
{
    const char na[] = "[N/A]";
    const size_t naSize = sizeof(na);

    Text::Copy(na, naSize, Name, OBJNameSize);

    VertexStructureSize = 0;

    MaterialFileListSize = 0;
    MaterialFileList = nullptr;

    ElementListSize = 0;
    ElementList = nullptr;
}

BF::OBJ::~OBJ()
{
    // TODO : Delete results in programm termination
    //delete[] MaterialList;
    //delete[] ElementList;
}

BF::Vector3<float>* BF::OBJ::GlobalVertexPosition(size_t index)
{
    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& objElement = ElementList[i];
        size_t arraySize = objElement.VertexPositionList.Size();
        bool isInThisElement = index <= arraySize;

        if (isInThisElement)
        {
            return &objElement.VertexPositionList[index];
        }

        index -= arraySize;
    }

    return nullptr;
}

BF::Vector2<float>* BF::OBJ::GlobalTextureCoordinate(size_t index)
{
    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& objElement = ElementList[i];
        size_t arraySize = objElement.TextureCoordinateList.Size();
        bool isInThisElement = index <= arraySize;

        if (isInThisElement)
        {
            return &objElement.TextureCoordinateList[index];
        }

        index -= arraySize;
    }

    return nullptr;
}

BF::Vector3<float>* BF::OBJ::GlobalVertexNormalPosition(size_t index)
{
    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& objElement = ElementList[i];
        size_t arraySize = objElement.VertexNormalPositionList.Size();
        bool isInThisElement = index <= arraySize;

        if (isInThisElement)
        {
            return &objElement.VertexNormalPositionList[index];
        }

        index -= arraySize;
    }

    return nullptr;
}

BF::Vector3<float>* BF::OBJ::GlobalVertexParameter(size_t index)
{
    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& objElement = ElementList[i];
        size_t arraySize = objElement.VertexParameterList.Size();
        bool isInThisElement = index <= arraySize;

        if (isInThisElement)
        {
            return &objElement.VertexParameterList[index];
        }

        index -= arraySize;
    }

    return nullptr;
}

BF::Vector3<unsigned int>* BF::OBJ::GlobalFaceElement(size_t index)
{
    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& objElement = ElementList[i];
        size_t arraySize = objElement.FaceElementList.Size();
        bool isInThisElement = index <= arraySize;

        if (isInThisElement)
        {
            return &objElement.FaceElementList[index];
        }

        index -= arraySize;
    }

    return nullptr;
}

bool BF::OBJ::ShouldCreateNewMesh(OBJLineCommand objLineCommand, bool isCurrentlyInFaces)
{
    if (!isCurrentlyInFaces)
    {
        return false;
    }

    switch (objLineCommand)
    {
        default:
        case BF::OBJLineCommand::Invalid:
        case BF::OBJLineCommand::None:;
        case BF::OBJLineCommand::Comment:
        case BF::OBJLineCommand::MaterialLibraryInclude:
        case BF::OBJLineCommand::FaceElement:
            return false;

        case BF::OBJLineCommand::MaterialLibraryUse:
        case BF::OBJLineCommand::VertexGeometric:
        case BF::OBJLineCommand::VertexTexture:
        case BF::OBJLineCommand::VertexNormal:
        case BF::OBJLineCommand::VertexParameter:
        case BF::OBJLineCommand::SmoothShading:
        case BF::OBJLineCommand::ObjectName:
            return true;
    }
}

BF::OBJLineCommand BF::OBJ::PeekCommandLine(const unsigned short lineTagID)
{
    switch (lineTagID)
    {
        case MakeShort('v', ' ') : return OBJLineCommand::VertexGeometric;
        case MakeShort('v', 't') : return OBJLineCommand::VertexTexture;
        case MakeShort('v', 'n') : return OBJLineCommand::VertexNormal;
        case MakeShort('v', 'p') : return OBJLineCommand::VertexParameter;
        case MakeShort('f', ' ') : return OBJLineCommand::FaceElement;
        case MakeShort('m', 't') : return OBJLineCommand::MaterialLibraryInclude;
        case MakeShort('u', 's') : return OBJLineCommand::MaterialLibraryUse;
        case MakeShort('#', ' ') : return OBJLineCommand::Comment;
        case MakeShort('o', ' ') : return OBJLineCommand::ObjectName;
        case MakeShort('s', ' ') : return OBJLineCommand::SmoothShading;

        default: return OBJLineCommand::Invalid;
    }
}

BF::FileActionResult BF::OBJ::Load(const char* filePath)
{
    File file;

    {
        const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryProtectionMode::ReadOnly);
        const bool sucessful = fileLoadingResult == FileActionResult::Successful;

        if(!sucessful)
        {
            return fileLoadingResult;
        }
    }    

    {
        wchar_t filePathW[PathMaxSize];

        Text::Copy(filePath, PathMaxSize, filePathW, PathMaxSize);

        const FileActionResult fileParsingResult = Load(file.Data, file.DataSize, filePathW);

        return fileParsingResult;
    }
}

BF::FileActionResult BF::OBJ::Load(const wchar_t* filePath)
{
    File file;

    {
        const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryProtectionMode::ReadOnly);
        const bool sucessful = fileLoadingResult == FileActionResult::Successful;

        if(!sucessful)
        {
            return fileLoadingResult;
        }
    }

    {
        const FileActionResult fileParsingResult = Load(file.Data, file.DataSize, filePath);

        return fileParsingResult;
    }
}

BF::FileActionResult BF::OBJ::Load(const unsigned char* data, const size_t dataSize, const wchar_t* fileName)
{
    ByteStream dataStream(data, dataSize);

    bool isFirstVertex = true;

    ElementListSize = 1;
    ElementList = new OBJElement();

    struct OBJSegmentData
    {
        size_t Position;
        size_t Texture;
        size_t Normal;
        size_t Parameter;
        size_t Face;
        size_t Material;
    };

    //---<Cound needed Space and allocate>----------------------------------
    {
        OBJSegmentData segmentData[128]{ 0 };
        size_t segmentAmount = 0;
        size_t materialCounter = 0;

        OBJElement* currentSegment = ElementList;
        bool isInMesh = false;

        do
        {
            const Byte__* currentLine = dataStream.CursorCurrentAdress();
            const unsigned short lineTagID = MakeShort(currentLine[0], currentLine[1]);
            const OBJLineCommand command = PeekCommandLine(lineTagID);

            OBJSegmentData& currentSegmentData = segmentData[segmentAmount];

            switch(command)
            {
                case OBJLineCommand::MaterialLibraryInclude:
                    ++materialCounter;
                    break;

                case OBJLineCommand::MaterialLibraryUse:
                    ++currentSegmentData.Material;
                    break;

                case OBJLineCommand::ObjectName:
                    ++segmentAmount;
                    break;

                case OBJLineCommand::VertexGeometric:
                    ++currentSegmentData.Position;
                    break;

                case OBJLineCommand::VertexTexture:
                    ++currentSegmentData.Texture;
                    break;

                case OBJLineCommand::VertexNormal:
                    ++currentSegmentData.Normal;
                    break;

                case OBJLineCommand::VertexParameter:
                    ++currentSegmentData.Parameter;
                    break;

                case OBJLineCommand::FaceElement:
                {
                    const size_t amount = Text::CountUntil(currentLine + 2, dataStream.ReadPossibleSize(), '/', '\n') / 2;

                    currentSegmentData.Face += amount;

                    isInMesh = true;

                    if(VertexStructureSize < amount)
                        VertexStructureSize = amount;

                    break;
                }
            }
        }
        while(dataStream.SkipLine());

        dataStream.CursorToBeginning();

        MaterialFileListSize = materialCounter;
        MaterialFileList = new MTL[materialCounter];

        for(size_t i = 0; i < segmentAmount; i++)
        {
            const OBJSegmentData& currentSegmentData = segmentData[segmentAmount];

            OBJElement& segment = *currentSegment;

            segment.Allocate
            (
                currentSegmentData.Position,
                currentSegmentData.Texture,
                currentSegmentData.Normal,
                currentSegmentData.Parameter,
                currentSegmentData.Face
            );

            segment.MaterialInfoSize = currentSegmentData.Material;
            segment.MaterialInfo = new OBJElementMaterialInfo[currentSegmentData.Material];

#if OBJDebug

            printf
            (
                "[OBJ][Segment (%li/%li)] V:%li T:%li N:%li P:%li F:%li M:%i\n",
                i+1, 
                segmentAmount,
                currentSegmentData.Position,
                currentSegmentData.Texture,
                currentSegmentData.Normal,
                currentSegmentData.Parameter,
                currentSegmentData.Face,
                currentSegmentData.Material
            );
#endif
        }
    }    
    //--------------------------------------------------------------------

    assert(VertexStructureSize == 3 || VertexStructureSize == 4);

    // Exact Parse
    {
        size_t currentPositionElement = 0;
        size_t currentTextureElement = 0;
        size_t currentNormalElement = 0;
        size_t currentParameterElement = 0;
        size_t currentFaceElement = 0;
        size_t materialIndex = 0;
        size_t materialIDCounter = 0;

        size_t elementIndex = -1;
        OBJElement* elemtentAdress = ElementList;
        bool isInMesh = false;

        size_t materialInfoIndex = 0;
        size_t materialFaceCounter = 0;
        size_t materialFaceCounterMAX = 0;

        // Parse
        do
        {
            const Byte__* currentLine = dataStream.CursorCurrentAdress();         
            const unsigned short lineTagID = MakeShort(currentLine[0], currentLine[1]);
            const OBJLineCommand command = PeekCommandLine(lineTagID);

            dataStream.SkipBlock();

            const char* dataPoint = (char*)dataStream.CursorCurrentAdress();
            const size_t maximalSize = dataStream.ReadPossibleSize();
            const size_t currentLineLength = Text::LengthUntil(dataPoint, maximalSize, '\n');

            OBJElement& currentElemtent = *elemtentAdress;

            switch(command)
            {
                case OBJLineCommand::MaterialLibraryInclude:
                {                  
                    char materialFilePathA[PathMaxSize];
                    wchar_t materialFilePathW[PathMaxSize];
                    wchar_t materialFilePathFullW[PathMaxSize];
                    MTL& material = MaterialFileList[materialIndex++];

                    // Parse materialPath
                    {
                        Text::Parse
                        (
                            dataPoint,
                            currentLineLength,
                            "s",
                            materialFilePathA
                        );
                    }

                    Text::Copy(materialFilePathA, PathMaxSize, materialFilePathW, PathMaxSize);
                    File::PathSwapFile(fileName, materialFilePathFullW, materialFilePathW);

                    {
                        const FileActionResult materialLoadResult = material.Load(materialFilePathFullW);
                        const bool sucessful = materialLoadResult == FileActionResult::Successful;

                        if(!sucessful)
                        {
#if OBJDebug
                            printf("[Warning] Material (.mtl) file is missing at path <%ls>\n", materialFilePathFullW);
#endif
                        }
                    }                  

                    break;
                }
                case OBJLineCommand::MaterialLibraryUse:
                {
                    char usedMaterialName[MTLNameSize];
                    unsigned int materialID = -1;

                    Text::Parse
                    (
                        dataPoint,
                        currentLineLength,
                        "s",
                        usedMaterialName
                    );

                    for(size_t i = 0; i < MaterialFileListSize; ++i)
                    {
                        const MTL& mtl = MaterialFileList[i];
                        const size_t materialListSize = mtl.MaterialListSize;

                        for(size_t j = 0; j < materialListSize; ++j)
                        {
                            const MTLMaterial& material = mtl.MaterialList[j];
                            const size_t matertalALength = Text::Length(material.Name);
                            const size_t matertalBLength = Text::Length(usedMaterialName);
                            const bool isSameName = Text::Compare(material.Name, matertalALength, usedMaterialName, matertalBLength);

                            if(isSameName)
                            {
                                materialID = j;
                                break;
                            }
                        }
                    }

                    if(materialInfoIndex > 0)
                    {
                        OBJElementMaterialInfo& infoBefore = currentElemtent.MaterialInfo[materialInfoIndex - 1];
                        OBJElementMaterialInfo& infoNew = currentElemtent.MaterialInfo[materialInfoIndex++];

                        infoNew.MaterialIndex = materialID;
                        infoNew.Size = -1;

                        size_t newSize = (currentFaceElement * 3);

                        infoBefore.Size = materialFaceCounter;

                        materialFaceCounterMAX += materialFaceCounter;
                        materialFaceCounter = 0;

                        if(materialInfoIndex == currentElemtent.MaterialInfoSize)
                        {
                            // Last entry
                            infoNew.Size = currentElemtent.FaceElementList.Size() - materialFaceCounterMAX;
                        }
                    }
                    else
                    {
                        OBJElementMaterialInfo& info = currentElemtent.MaterialInfo[materialInfoIndex++];

                        info.MaterialIndex = materialID;
                        info.Size = -1;
                    }                 

                    break;
                }

                case OBJLineCommand::ObjectName:
                {
                    OBJElement* elemtentAdress = &ElementList[elementIndex++];                                

                    materialInfoIndex = 0;
                   
                    Text::Copy(dataPoint, currentLineLength, currentElemtent.Name, OBJElementNameLength);
                    break;
                }

                case OBJLineCommand::VertexParameter:
                case OBJLineCommand::VertexNormal:
                case OBJLineCommand::VertexGeometric:
                {
                    Vector3<float>* currentVectorValue = nullptr;

                    switch(command)
                    {
                        case OBJLineCommand::VertexParameter:
                            currentVectorValue = &currentElemtent.VertexParameterList[currentParameterElement++];
                            break;

                        case OBJLineCommand::VertexNormal:
                            currentVectorValue = &currentElemtent.VertexNormalPositionList[currentNormalElement++];
                            break;

                        case OBJLineCommand::VertexGeometric:
                            currentVectorValue = &currentElemtent.VertexPositionList[currentPositionElement++];
                            break;
                    }

                    assert(currentVectorValue);

                    Text::Parse
                    (
                        (char*)dataPoint,
                        currentLineLength,
                        "fff",
                        &currentVectorValue->X,
                        &currentVectorValue->Y,
                        &currentVectorValue->Z
                    );
                    break;
                }

                case OBJLineCommand::VertexTexture:
                {
                    Vector2<float>& point = currentElemtent.TextureCoordinateList[currentTextureElement++];

                    Text::Parse
                    (
                        (char*)dataPoint,
                        currentLineLength,
                        "ff",
                        &point.X, 
                        &point.Y
                    );

                    break;
                }
                case OBJLineCommand::SmoothShading:
                    break;

                case OBJLineCommand::FaceElement:
                {
                    Vector3<unsigned int>& vectorA = currentElemtent.FaceElementList[currentFaceElement++];
                    Vector3<unsigned int>& vectorB = currentElemtent.FaceElementList[currentFaceElement++];
                    Vector3<unsigned int>& vectorC = currentElemtent.FaceElementList[currentFaceElement++];

                    materialFaceCounter += VertexStructureSize;

                    switch(VertexStructureSize)
                    {
                        case 3:
                        {
                            Text::Parse
                            (
                                (char*)dataPoint,
                                currentLineLength,
                                "u§u§uu§u§uu§u§u",
                                &vectorA.X, &vectorA.Y, &vectorA.Z,
                                &vectorB.X, &vectorB.Y, &vectorB.Z,
                                &vectorC.X, &vectorC.Y, &vectorC.Z
                            );
                            break;
                        }
                        case 4:
                        {
                            const Byte__* dataPoint = dataStream.CursorCurrentAdress();
                            const size_t readableSize = dataStream.ReadPossibleSize();
                            Vector3<unsigned int>& vectorD = currentElemtent.FaceElementList[currentFaceElement++];

                            Text::Parse
                            (
                                (char*)dataPoint,
                                readableSize,
                                "u§u§u§uu§u§u§uu§u§u§uu§u§u§u",
                                &vectorA.X, &vectorA.Y, &vectorA.Z,
                                &vectorB.X, &vectorB.Y, &vectorB.Z,
                                &vectorC.X, &vectorC.Y, &vectorC.Z,
                                &vectorD.X, &vectorD.Y, &vectorD.Z
                            );
                            break;
                        }

                        default:
                            break;
                    }

                    isInMesh = true;

                    break;
                }

                case OBJLineCommand::Invalid:
                case OBJLineCommand::None:
                case OBJLineCommand::Comment:
                default:
                    break;
            }
        }
        while(dataStream.SkipLine());
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::OBJ::Save(const wchar_t* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::OBJ::ConvertTo(Model& model)
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

            Text::Copy(mtlMaterial.Name, MTLNameSize, material.Name, MaterialNameLength);
            Text::Copy(mtlMaterial.TextureFilePath, MTLFilePath, material.TextureFilePath, MaterialTextureFilePathLength);
                       
            Memory::Copy(material.Ambient, mtlMaterial.Ambient, 3 * sizeof(float));
            Memory::Copy(material.Diffuse, mtlMaterial.Diffuse, 3 * sizeof(float));
            Memory::Copy(material.Specular, mtlMaterial.Specular, 3 * sizeof(float));
            Memory::Copy(material.Emission, mtlMaterial.Emission, 3 * sizeof(float));
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

    for (size_t i = 0; i < ElementListSize; i++)
    {
        OBJElement& element = ElementList[i];
        MeshSegment& meshSegment = mesh.SegmentList[i];
        const size_t faceElementListSize = element.FaceElementList.Size();
        const size_t verexDataSize = faceElementListSize * (3 + 3 + 4 + 2);

        Text::Copy(element.Name, OBJElementNameLength, meshSegment.Name, MeshSegmentNameLength);          

        mesh.VertexDataListSize = verexDataSize;
        mesh.VertexDataList = Memory::Allocate<float>(verexDataSize);
       

        // mesh.Structure.RenderType = VertexStructureSize == 4 ? RenderMode::Square : RenderMode::Triangle;
        //mesh.VertexDataStructureListSize

        meshSegment.IndexDataListSize = faceElementListSize;
        meshSegment.IndexDataList = Memory::Allocate<unsigned int>(faceElementListSize);

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
                infoB.Size = infoA.Size;
            }
        }
        else
        {
            meshSegment.MaterialInfoSize = 1;
            meshSegment.MaterialInfo = new OBJElementMaterialInfo[1];
            meshSegment.MaterialInfo->Size = element.FaceElementList.Size();
            meshSegment.MaterialInfo->MaterialIndex = -1;
        }
      

        for (size_t i = 0; i < faceElementListSize; i++)
        {
            const Vector3<unsigned int>& indexPosition = element.FaceElementList[i];
            unsigned int vertexPositionID = indexPosition.X - 1;
            unsigned int texturePointID = indexPosition.Y - 1; // TODO: REMOVED -1 form all positions
            unsigned int normalVectorID = indexPosition.Z - 1;
            Vector3<float>* vertexData = GlobalVertexPosition(vertexPositionID);
            Vector2<float>* textureData = GlobalTextureCoordinate(texturePointID);
            Vector3<float>* normalData = GlobalVertexNormalPosition(normalVectorID);
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

                ++texturePointID;
                textureData = GlobalTextureCoordinate(texturePointID);
            }

            if (!normalVectorIDValid)
            {
                ++normalVectorID;
                normalData = GlobalVertexNormalPosition(normalVectorID);
            }



#elif
            assert(vertexPositionIDValid);
            assert(texturePointIDValid);
            assert(normalVectorIDValid);
#endif // failsafe         


            const unsigned int dataSize = 12u;
            float data[dataSize]
            {
                vertexData->X,
                vertexData->Y,
                vertexData->Z,
                normalData->X,
                normalData->Y,
                normalData->Z,
                color.X,
                color.Y,
                color.Z,
                color.W,
                textureData->X,
                textureData->Y
            };

            meshSegment.IndexDataList[i] = i;

            Memory::Copy(vertexDataArray + vertecDataIndex, data, sizeof(float) * dataSize);

            vertecDataIndex += dataSize;        
        }
    }   

    return FileActionResult::Successful;
}

BF::FileActionResult BF::OBJ::ConvertFrom(Model& model)
{
    return FileActionResult::Successful;
}

void BF::OBJ::Clear()
{
    delete[] MaterialFileList;
    delete[] ElementList;

    VertexStructureSize = 0xFF;
    MaterialFileListSize = 0;
    MaterialFileList = 0;
    ElementListSize = 0;
    ElementList = 0;
}

void BF::OBJ::PrintData()
{
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
        }*/

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
}