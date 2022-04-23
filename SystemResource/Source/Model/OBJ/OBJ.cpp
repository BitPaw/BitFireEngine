#include "OBJ.h"

#include "../../File/File.h"
#include "../../File/FileStream.h"
#include "../../Container/AsciiString.h"

#include <Text/Text.h>

#include <cassert>
#include <cstring>

#include <Hardware/Memory/Memory.h>

BF::OBJ::OBJ()
{
    Text::Copy(Name, "[N/A]", OBJNameSize);

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

BF::OBJLineCommand BF::OBJ::PeekCommandLine(const char* commandLine)
{
    unsigned char functionChar = commandLine[0];

    switch (functionChar)
    {
        case 'v':
        {
            functionChar = commandLine[1];

            switch (functionChar)
            {
                case ' ':
                    return OBJLineCommand::VertexGeometric;

                case 't':
                    return OBJLineCommand::VertexTexture;

                case 'n':
                    return OBJLineCommand::VertexNormal;

                case 'p':
                    return OBJLineCommand::VertexParameter;

                default:
                    return OBJLineCommand::Invalid;
            }

            break;
        }

        case 'f':    
            return OBJLineCommand::FaceElement;

        case 'm':
            return OBJLineCommand::MaterialLibraryInclude;

        case 'u':
            return OBJLineCommand::MaterialLibraryUse;

        case '#':
            return OBJLineCommand::Comment;

        case 'o':
            return OBJLineCommand::ObjectName;

        case 's':
            return OBJLineCommand::SmoothShading;

        case ' ': 
            return OBJLineCommand::None;

        default:
            return OBJLineCommand::Invalid;
    }
}

BF::FileActionResult BF::OBJ::Load(const wchar_t* filePath)
{
    const size_t currentLineBufferSize = 1024;
    char currentLineBuffer[currentLineBufferSize];
    bool isFirstVertex = true;
    FileStream file; 

    {
        const FileActionResult fileActionResult = file.MapToVirtualMemory(filePath); // TODO: true
        const bool successful = fileActionResult == FileActionResult::Successful;

        if(!successful)
        {
            return fileActionResult;
        }
    }
   

    Text::Copy(Name, filePath, OBJNameSize);

    //---<Cound needed Space and allocate>----------------------------------
    {
        bool isInMesh = false;  

        size_t vertexPositionListSize = 0;
        size_t vertexTextureCoordinateListSize = 0;
        size_t vertexNormalPositionListSize = 0;
        size_t vertexParameterListSize = 0;
        size_t faceElementListSize = 0;

        ElementListSize = 1;
        ElementList = new OBJElement();

        while (file.ReadNextLineInto(currentLineBuffer))
        {                
            const OBJLineCommand command = PeekCommandLine(currentLineBuffer);

            switch (command)
            {
                default:
                case OBJLineCommand::Invalid:
                case OBJLineCommand::None:
                case OBJLineCommand::Comment:
                    break;

                case OBJLineCommand::MaterialLibraryInclude:
                    ++MaterialFileListSize;
                    break;

                case OBJLineCommand::MaterialLibraryUse:
                    break;
                case OBJLineCommand::ObjectName:
                    break;
                case OBJLineCommand::VertexGeometric:
                    ++vertexPositionListSize;
                    break;

                case OBJLineCommand::VertexTexture:
                    ++vertexTextureCoordinateListSize;
                    break;

                case OBJLineCommand::VertexNormal:
                    ++vertexNormalPositionListSize;
                    break;

                case OBJLineCommand::VertexParameter:
                    ++vertexParameterListSize;
                    break;

                case OBJLineCommand::SmoothShading:
                    break;
                case OBJLineCommand::FaceElement:
                {
                    AsciiString characters(currentLineBuffer);
                    unsigned char amount = static_cast<char>(characters.Count('/')) / 2;

                    faceElementListSize += amount;

                    isInMesh = true;

                    if (VertexStructureSize < amount)
                        VertexStructureSize = amount;

                    break;
                }
            }  

            bool fetchNextMesh = ShouldCreateNewMesh(command, isInMesh);

            /*
            if (!(lineIndex < numberOfLines))
            {
                OBJElement& element = ElementList[ElementListSize - 1];

                element.VertexPositionList.ReSize(vertexPositionListSize);
                element.TextureCoordinateList.ReSize(vertexTextureCoordinateListSize);
                element.VertexNormalPositionList.ReSize(vertexNormalPositionListSize);
                element.VertexParameterList.ReSize(vertexParameterListSize);
                element.FaceElementList.ReSize(faceElementListSize);
            }*/

            if (fetchNextMesh)
            {
                OBJElement* newelementList = Memory::Rellocate<OBJElement>(ElementList, ++ElementListSize);

                if (!newelementList)
                {
                    return FileActionResult::OutOfMemory;
                }

                ElementList = newelementList;

                OBJElement& oldElement = newelementList[ElementListSize - 2];
                OBJElement& newElement = newelementList[ElementListSize - 1];

                newElement = OBJElement();

                oldElement.Allocate
                (
                    vertexPositionListSize,
                    vertexTextureCoordinateListSize,
                    vertexNormalPositionListSize,
                    vertexParameterListSize,
                    faceElementListSize
                );

                vertexPositionListSize = 0;
                vertexTextureCoordinateListSize = 0;
                vertexNormalPositionListSize = 0;
                vertexParameterListSize = 0;
                faceElementListSize = 0;              

                isInMesh = false;
            }
        } 

        ElementList[ElementListSize - 1].Allocate
        (
            vertexPositionListSize,
            vertexTextureCoordinateListSize,
            vertexNormalPositionListSize,
            vertexParameterListSize,
            faceElementListSize
        );

        if (MaterialFileListSize > 0)
        {
            MaterialFileList = new MTL[MaterialFileListSize];
        }
     }
     //--------------------------------------------------------------------

    assert(VertexStructureSize == 3 || VertexStructureSize == 4);

    // Exact Parse
    {    
        size_t elementIndex = 0;
        size_t currentPositionElement = 0;
        size_t currentTextureElement = 0;
        size_t currentNormalElement = 0;
        size_t currentParameterElement = 0;
        size_t currentFaceElement = 0;
        size_t materialIndex = 0;
        size_t materialIDCounter = 0;

        OBJElement* elemtent = &ElementList[elementIndex++];
        bool isInMesh = false;      
        
        file.CursorToBeginning();

        // Parse
        while (file.ReadNextLineInto(currentLineBuffer))
        {
            const OBJLineCommand command = PeekCommandLine(currentLineBuffer);            
            
            {
                const bool fetchNextMesh = ShouldCreateNewMesh(command, isInMesh);

                if (fetchNextMesh)
                {
                    elemtent = &ElementList[elementIndex++];

                    currentPositionElement = 0;
                    currentTextureElement = 0;
                    currentNormalElement = 0;
                    currentParameterElement = 0;
                    currentFaceElement = 0;
                }
            }           

            switch (command)
            {
                case OBJLineCommand::MaterialLibraryInclude:
                { 
                    wchar_t materialFilePath[PathMaxSize];
                    MTL& material = MaterialFileList[materialIndex++];

                    // Parse materialPath
                    {
                        char materialFilePathTempA[PathMaxSize];
                        wchar_t materialFilePathTempW[PathMaxSize];

                        Text::Parse
                        (
                            currentLineBuffer,
                            currentLineBufferSize,
                            "$s",
                            materialFilePathTempA
                        );

                        Text::AsciiToUnicode(materialFilePathTempA, PathMaxSize, materialFilePathTempW, PathMaxSize);

                        File::PathSwapFile(filePath, materialFilePath, materialFilePathTempW);
                    }              

                    const BF::FileActionResult materialLoadResult = material.Load(materialFilePath);

                    if (materialLoadResult != FileActionResult::Successful)
                    {
                        printf("[Warning] Material (.mtl) file is missing at path <%ls>\n", materialFilePath);
                    }

                    break;
                }
                case OBJLineCommand::MaterialLibraryUse:
                {
                    char usedMaterialName[MTLNameSize];
                    unsigned int materialID = -1;
                 
                    Text::Parse
                    (
                        currentLineBuffer,
                        currentLineBufferSize,
                        "$s",
                        usedMaterialName
                    );

                    for (size_t i = 0; i < MaterialFileListSize; i++)
                    {
                        const MTL& mtl = MaterialFileList[i];
                        const size_t materialListSize = mtl.MaterialListSize;

                        for (size_t j = 0; j < materialListSize; j++)
                        {
                            const MTLMaterial& material = mtl.MaterialList[j];     
                            const size_t matertalALength = Text::Length(material.Name);
                            const size_t matertalBLength = Text::Length(usedMaterialName);
                            const bool isSameName = Text::Compare(material.Name, matertalALength, usedMaterialName, matertalBLength);

                            if (isSameName)
                            {
                                materialID = j;
                                break;
                            }
                        }
                    }

                    elemtent->MaterialListIndex = materialID;

                    break;
                }

                case OBJLineCommand::ObjectName:
                {
                    Text::Copy(elemtent->Name, currentLineBuffer + 2, OBJElementNameLength);
                    break;
                }

                case OBJLineCommand::VertexParameter:
                case OBJLineCommand::VertexNormal:
                case OBJLineCommand::VertexGeometric:
                {
                    Vector3<float>* currentVectorValue = nullptr;

                    assert(elemtent);

                    switch (command)
                    {
                        case OBJLineCommand::VertexParameter:
                            currentVectorValue = &elemtent->VertexParameterList[currentParameterElement++];
                            break;

                        case OBJLineCommand::VertexNormal:
                            currentVectorValue = &elemtent->VertexNormalPositionList[currentNormalElement++];
                            break;

                        case OBJLineCommand::VertexGeometric:
                            currentVectorValue = &elemtent->VertexPositionList[currentPositionElement++];
                            break;
                    }

                    assert(currentVectorValue);

                    Text::Parse
                    (
                        currentLineBuffer,
                        currentLineBufferSize,
                        "$fff",
                        &currentVectorValue->X, 
                        &currentVectorValue->Y,
                        &currentVectorValue->Z
                    );
                    break;
                }          

                case OBJLineCommand::VertexTexture:
                {
                    Vector2<float>& point = elemtent->TextureCoordinateList[currentTextureElement++];

                    Text::Parse
                    (
                        currentLineBuffer,
                        currentLineBufferSize,
                        "$ff",
                        &point.X, &point.Y 
                    );

                    break;
                }        
                case OBJLineCommand::SmoothShading:
                    break;

                case OBJLineCommand::FaceElement:
                {     
                    assert(currentFaceElement < elemtent->FaceElementList.Size());

                    Vector3<unsigned int>& vectorA = elemtent->FaceElementList[currentFaceElement++];
                    Vector3<unsigned int>& vectorB = elemtent->FaceElementList[currentFaceElement++];
                    Vector3<unsigned int>& vectorC = elemtent->FaceElementList[currentFaceElement++];

                    switch (VertexStructureSize)
                    {
                        case 3:
                        {
                            Text::Parse
                            (
                                currentLineBuffer,
                                currentLineBufferSize,
                                "$uuuuuuuuu",
                                &vectorA.X, &vectorA.Y, &vectorA.Z,
                                &vectorB.X, &vectorB.Y, &vectorB.Z,
                                &vectorC.X, &vectorC.Y, &vectorC.Z
                            );
                            break;
                        }
                        case 4:
                        {
                            Vector3<unsigned int>& vectorD = elemtent->FaceElementList[currentFaceElement++];

                            Text::Parse
                            (
                                currentLineBuffer,
                                currentLineBufferSize,
                                "$uuuuuuuuuuuu",                                
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
            MTLMaterial& mtlMaterial = mtl.MaterialList[materialIndex];
            Material& material = model.MaterialList[materialIndex];

            Text::Copy(material.Name, mtlMaterial.Name, MTLNameSize);
          //  Text::Copy(material.FilePath, mtlMaterial.TextureFilePath, MTLFilePath);
            memcpy(material.Ambient, mtlMaterial.Ambient, 3 * sizeof(float));
            memcpy(material.Diffuse, mtlMaterial.Diffuse, 3 * sizeof(float));
            memcpy(material.Specular, mtlMaterial.Specular, 3 * sizeof(float));
            memcpy(material.Emission, mtlMaterial.Emission, 3 * sizeof(float));
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

        Text::Copy(meshSegment.Name, element.Name, OBJElementNameLength);

        
        const size_t verexDataSize = faceElementListSize * (3 + 3 + 4 + 2);

        mesh.VertexDataListSize = verexDataSize;
        mesh.VertexDataList = (float*)malloc(verexDataSize * sizeof(float));
       

        // mesh.Structure.RenderType = VertexStructureSize == 4 ? RenderMode::Square : RenderMode::Triangle;
        //mesh.VertexDataStructureListSize

        meshSegment.IndexDataListSize = faceElementListSize;
        meshSegment.IndexDataList = (unsigned int*)malloc(faceElementListSize * sizeof(unsigned int));

        //meshSegment. = malloc .Allocate(faceElementListSize * (3 + 3 + 4 + 2), faceElementListSize);
        //mesh.RenderInfo.MaterialID = element.MaterialListIndex;


        size_t vertecDataIndex = 0;
        float* vertexDataArray = mesh.VertexDataList;


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

            memcpy(vertexDataArray + vertecDataIndex, data, sizeof(float) * dataSize);

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
    printf
    (
        "| %5s | %5s | %5s | %5s | %5s | %-17s | %-16s |\n",
        "VertP", "NormP", "TextC", "ParaV", "Face", "Mesh-Name", "Material-Name");
    printf(line);

    for (unsigned int i = 0; i < ElementListSize; i++)
    {
        OBJElement* waveFrontElement = &ElementList[i];

        unsigned int sizePos = waveFrontElement->VertexPositionList.Size();
        unsigned int sizeNormal = waveFrontElement->VertexNormalPositionList.Size();
        unsigned int sizeText = waveFrontElement->TextureCoordinateList.Size();
        unsigned int sizePara = waveFrontElement->VertexParameterList.Size();
        unsigned int sizeFace = waveFrontElement->FaceElementList.Size();                
        char* materialName = nullptr;

        if (waveFrontElement->MaterialListIndex != -1)
        {
            materialName = MaterialFileList[0].MaterialList[waveFrontElement->MaterialListIndex].Name;
        }

        printf
        (
            "| %5u | %5u | %5u | %5u | %5u | %-17s | %-16s |\n", 
            sizePos, 
            sizeNormal, 
            sizeText,
            sizePara, 
            sizeFace, 
            &waveFrontElement->Name[0],
            materialName
        );
    }

    printf(line);

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