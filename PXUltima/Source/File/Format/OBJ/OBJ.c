#include "OBJ.h"

#include <File/ParsingStream.h>
#include <Memory/Memory.h>
#include <Container/ClusterShort.h>
#include <Text/Text.h>
#include <File/File.h>

void OBJElementConstruct(OBJElement* objElement)
{
    MemorySet(objElement, sizeof(OBJElement), 0);
}

void OBJElementDestruct(OBJElement* objElement)
{
    //TODO: clear memeory
}

void OBJConstruct(OBJ* obj)
{
	MemorySet(obj, sizeof(OBJ), 0);
}

void OBJDestruct(OBJ* obj)
{
	MemoryRelease(obj->ElementList, obj->ElementListSize);

	MemoryRelease(obj->MaterialFileList, obj->MaterialFileListSize);
}

OBJLineType OBJPeekLine(const void* line)
{
    const unsigned short lineTagID = MakeShort(((unsigned char*)line)[0], ((unsigned char*)line)[1]);

    switch(lineTagID)
    {
        case MakeShort('v', ' '): return OBJLineVertexGeometric;
        case MakeShort('v', 't'): return OBJLineVertexTexture;
        case MakeShort('v', 'n'): return OBJLineVertexNormal;
        case MakeShort('v', 'p'): return OBJLineVertexParameter;
        case MakeShort('f', ' '): return OBJLineFaceElement;
        case MakeShort('m', 't'): return OBJLineMaterialLibraryInclude;
        case MakeShort('u', 's'): return OBJLineMaterialLibraryUse;
        case MakeShort('#', ' '): return OBJLineComment;
        case MakeShort('o', ' '): return OBJLineObjectName;
        case MakeShort('s', ' '): return OBJLineSmoothShading;

        default: return OBJLineInvalid;
    }
}

ActionResult OBJParse(OBJ* obj, const void* data, const size_t dataSize, size_t* dataRead, const wchar_t* fileName)
{
    ParsingStream parsingStream;

    ParsingStreamConstruct(&parsingStream, data, dataSize);
    OBJConstruct(obj);
    *dataRead = 0;

    unsigned char isFirstVertex = 0;

    obj->ElementListSize = 1;
    obj->ElementList = MemoryAllocate(sizeof(OBJElement) * 1u);

    typedef struct OBJSegmentData
    {
        size_t Position;
        size_t Texture;
        size_t Normal;
        size_t Parameter;
        size_t Face;
        size_t Material;
    }
    OBJSegmentData;       

    //---<Cound needed Space and allocate>----------------------------------
    {
        OBJSegmentData segmentData[128];
        size_t segmentAmount = 0;
        size_t materialCounter = 0;

        OBJElement* currentSegment = obj->ElementList;
        unsigned char isInMesh = 0;

        MemorySet(segmentData, sizeof(OBJSegmentData) * 128, 0);

        do
        {
            const char* currentLine = ParsingStreamCursorPosition(&parsingStream);
            const OBJLineType command = OBJPeekLine(currentLine);

            OBJSegmentData* currentSegmentData = &segmentData[segmentAmount];

            switch(command)
            {
                case OBJLineMaterialLibraryInclude:
                    ++materialCounter;
                    break;

                case OBJLineMaterialLibraryUse:
                    ++currentSegmentData->Material;
                    break;

                case OBJLineObjectName:
                    ++segmentAmount;
                    break;

                case OBJLineVertexGeometric:
                    ++currentSegmentData->Position;
                    break;

                case OBJLineVertexTexture:
                    ++currentSegmentData->Texture;
                    break;

                case OBJLineVertexNormal:
                    ++currentSegmentData->Normal;
                    break;

                case OBJLineVertexParameter:
                    ++currentSegmentData->Parameter;
                    break;

                case OBJLineFaceElement:
                {
                    const size_t amount = TextCountUntilA(currentLine + 2, ParsingStreamRemainingSize(&parsingStream), '/', '\n') / 2;

                    currentSegmentData->Face += amount;

                    isInMesh = 1u;

                    if(obj->VertexStructureSize < amount)
                        obj->VertexStructureSize = amount;

                    break;
                }
            }
        }
        while(ParsingStreamSkipLine(&parsingStream));

        ParsingStreamCursorToBeginning(&parsingStream);

        obj->MaterialFileListSize = materialCounter;
        obj->MaterialFileList = MemoryAllocate(sizeof(MTL) * materialCounter);

        MemorySet(obj->MaterialFileList, sizeof(MTL)* materialCounter, 0);

        for(size_t i = 0; i < segmentAmount; i++)
        {
            const OBJSegmentData* currentSegmentData = &segmentData[segmentAmount];

            OBJElement* segment = currentSegment;

            OBJElementConstruct(segment); 
            
            segment->VertexPositionListSize = currentSegmentData->Position * 3u;
            segment->VertexPositionList = MemoryAllocate(sizeof(float) * segment->VertexPositionListSize);

            segment->TextureCoordinateListSize = currentSegmentData->Texture * 2u;
            segment->TextureCoordinateList = MemoryAllocate(sizeof(float) * segment->TextureCoordinateListSize);

            segment->VertexNormalPositionListSize = currentSegmentData->Normal * 3u;
            segment->VertexNormalPositionList = MemoryAllocate(sizeof(float) * segment->VertexNormalPositionListSize);

            segment->VertexParameterListSize = currentSegmentData->Parameter * 3u;
            segment->VertexParameterList = MemoryAllocate(sizeof(float) * segment->VertexParameterListSize);

            segment->FaceElementListSize = currentSegmentData->Face * 3u;
            segment->FaceElementList = MemoryAllocate(sizeof(unsigned int) * segment->FaceElementListSize);

            segment->MaterialInfoSize = currentSegmentData->Material;
            segment->MaterialInfo = MemoryAllocate(sizeof(OBJElementMaterialInfo) * segment->MaterialInfoSize);

#if OBJDebug

            printf
            (
                "[OBJ][Segment (%li/%li)] V:%li T:%li N:%li P:%li F:%li M:%i\n",
                i + 1,
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

    //assert(VertexStructureSize == 3 || VertexStructureSize == 4);

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
        OBJElement* elemtentAdress = obj->ElementList;
        unsigned char isInMesh = 0;

        size_t materialInfoIndex = 0;
        size_t materialFaceCounter = 0;
        size_t materialFaceCounterMAX = 0;

        // Parse
        do
        {
            const char* currentLine = ParsingStreamCursorPosition(&parsingStream);
            const unsigned short lineTagID = MakeShort(currentLine[0], currentLine[1]);
            const OBJLineType command = OBJPeekLine(currentLine);

            ParsingStreamSkipBlock(&parsingStream);

            const char* dataPoint = ParsingStreamCursorPosition(&parsingStream);
            const size_t maximalSize = ParsingStreamRemainingSize(&parsingStream);
            const size_t currentLineLength = TextLengthUntilA(dataPoint, maximalSize, '\n');

            OBJElement* currentElemtent = elemtentAdress;

            switch(command)
            {
                case OBJLineMaterialLibraryInclude:
                {
                    char materialFilePathA[PathMaxSize];
                    wchar_t materialFilePathW[PathMaxSize];
                    wchar_t materialFilePathFullW[PathMaxSize];
                    MTL* material = &obj->MaterialFileList[materialIndex++];

                    // Parse materialPath
                    {
                        TextParseA
                        (
                            dataPoint,
                            currentLineLength,
                            "s",
                            materialFilePathA
                        );
                    }

                    TextCopyAW(materialFilePathA, PathMaxSize, materialFilePathW, PathMaxSize);
                    
                    FilePathSwapFile(fileName, materialFilePathFullW, materialFilePathW);

                    {

                        File file;

                        FileConstruct(&file);

                        {
                            const ActionResult fileLoadingResult = FileMapToVirtualMemoryW(&file, materialFilePathFullW, MemoryReadOnly);
                            const unsigned char sucessful = fileLoadingResult == ResultSuccessful;

                           // if(!sucessful)
                           // {
                           //     return FileActionResult::Invalid;
                           // }
                        }   
                        size_t readBytes = 0;
                        const ActionResult actionResult = MTLParse(material, file.Data, file.DataSize, &readBytes);
                        const unsigned char sucessful = actionResult == ResultSuccessful;

#if 1 //OBJDebug

                        if(sucessful)
                        {
                            printf("[+][MTL] Material (.mtl) file loaded <%ls>\n", materialFilePathFullW);

                           

                        }
                        else
                        {
                            printf("[Warning] Material (.mtl) file is missing at path <%ls>\n", materialFilePathFullW);
                        }

#endif

                        FileUnmapFromVirtualMemory(&file);
                    }                    

                    break;
                }
                case OBJLineMaterialLibraryUse:
                {
                    char usedMaterialName[MTLNameSize];
                    unsigned int materialID = -1;

                    TextParseA
                    (
                        dataPoint,
                        currentLineLength,
                        "s",
                        usedMaterialName
                    );

                    for(size_t i = 0; i < obj->MaterialFileListSize; ++i)
                    {
                        const MTL* mtl = &obj->MaterialFileList[i];
                        const size_t materialListSize = mtl->MaterialListSize;

                        for(size_t j = 0; j < materialListSize; ++j)
                        {
                            const MTLMaterial* material = &mtl->MaterialList[j];   
                            const unsigned char isSameName = TextCompareA(material->Name, MTLNameSize, usedMaterialName, MTLNameSize);

                            if(isSameName)
                            {
                                materialID = j;
                                break;
                            }
                        }
                    }

                    if(materialInfoIndex)
                    {
                        OBJElementMaterialInfo* infoBefore = &currentElemtent->MaterialInfo[materialInfoIndex - 1];
                        OBJElementMaterialInfo* infoNew = &currentElemtent->MaterialInfo[materialInfoIndex++];

                        infoNew->MaterialIndex = materialID;
                        infoNew->Size = -1;

                        size_t newSize = (currentFaceElement * 3);

                        infoBefore->Size = materialFaceCounter;

                        materialFaceCounterMAX += materialFaceCounter;
                        materialFaceCounter = 0;

                        if(materialInfoIndex == currentElemtent->MaterialInfoSize)
                        {
                            // Last entry
                            infoNew->Size = currentElemtent->FaceElementListSize - materialFaceCounterMAX;
                        }
                    }
                    else
                    {
                        OBJElementMaterialInfo* info = &currentElemtent->MaterialInfo[materialInfoIndex++];

                        info->MaterialIndex = materialID;
                        info->Size = -1;
                    }

                    break;
                }

                case OBJLineObjectName:
                {
                    OBJElement* elemtentAdress = &obj->ElementList[elementIndex++];

                    materialInfoIndex = 0;

                    TextCopyA(dataPoint, currentLineLength, currentElemtent->Name, OBJElementNameLength);
                    break;
                }

                case OBJLineVertexParameter:
                case OBJLineVertexNormal:
                case OBJLineVertexGeometric:
                {
                    float* data = 0;

                    switch(command)
                    {
                        case OBJLineVertexParameter:
                            data = &currentElemtent->VertexParameterList[currentParameterElement];
                            currentParameterElement += 3;
                            break;

                        case OBJLineVertexNormal:
                            data = &currentElemtent->VertexNormalPositionList[currentNormalElement];
                            currentNormalElement += 3;
                            break;

                        case OBJLineVertexGeometric:
                            data = &currentElemtent->VertexPositionList[currentPositionElement];
                            currentPositionElement += 3;
                            break;
                    }

                    //assert(currentVectorValue);

                    TextParseA
                    (
                        dataPoint,
                        currentLineLength,
                        "fff",
                        &data[0], // x
                        &data[1], // y
                        &data[2] // z
                    );
                    break;
                }

                case OBJLineVertexTexture:
                {
                    float* data = &currentElemtent->TextureCoordinateList[currentTextureElement];
               
                    currentTextureElement += 2u;

                    TextParseA
                    (
                        dataPoint,
                        currentLineLength,
                        "ff",
                        &data[0], // x
                        &data[1] // y
                    );

                    break;
                }
                case OBJLineSmoothShading:
                    break;

                case OBJLineFaceElement:
                {
                    unsigned int* data = &currentElemtent->FaceElementList[currentFaceElement];

                    currentFaceElement += obj->VertexStructureSize * 3;
                    materialFaceCounter += obj->VertexStructureSize * 3;

                    switch(obj->VertexStructureSize)
                    {
                        case 3:
                        {
                            TextParseA
                            (
                                dataPoint,
                                currentLineLength,
                                "u§u§uu§u§uu§u§u",
                                &data[0], &data[1], &data[2], // x, y, z (A)
                                &data[3], &data[4], &data[5], // x, y, z (B)
                                &data[6], &data[7], &data[8]  // x, y, z (C)
                            );
                            break;
                        }
                        case 4:
                        {
                            TextParseA
                            (
                                dataPoint,
                                currentLineLength,
                                "u§u§u§uu§u§u§uu§u§u§uu§u§u§u",
                                &data[0], &data[1], &data[2], // x, y, z (A)
                                &data[3], &data[4], &data[5], // x, y, z (B)
                                &data[6], &data[7], &data[8],  // x, y, z (C)
                                &data[9], &data[10], &data[11]  // x, y, z (D)
                            );
                            break;
                        }

                        default:
                            break;
                    }

                    isInMesh = 1;

                    break;
                }

                case OBJLineInvalid:
                case OBJLineNone:
                case OBJLineComment:
                default:
                    break;
            }
        }
        while(ParsingStreamSkipLine(&parsingStream));
    }

    return ResultSuccessful;
}