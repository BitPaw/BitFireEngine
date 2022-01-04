#include "OBJ.h"

#include "../../File/File.h"
#include "../../File/FileStream.h"
#include "../../Container/AsciiString.h"

#include <cassert>
#include <cstring>

BF::OBJ::OBJ()
{
    strncpy(Name, "[N/A]", OBJNameSize);

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

BF::FileActionResult BF::OBJ::Load(const char* filePath)
{
    bool isFirstVertex = true;
    char currentLineBuffer[300];
    FileStream file; 
    FileActionResult FileActionResult = file.ReadFromDisk(filePath, true);

    if (FileActionResult != FileActionResult::Successful)
    {
        return FileActionResult;
    }   

    strncpy(Name, filePath, OBJNameSize);

    //---<Cound needed Space and allocate>----------------------------------
    {
        bool isInMesh = false;  

        unsigned int vertexPositionListSize = 0;
        unsigned int vertexTextureCoordinateListSize = 0;
        unsigned int vertexNormalPositionListSize = 0;
        unsigned int vertexParameterListSize = 0;
        unsigned int faceElementListSize = 0;

        ElementListSize = 1;
        ElementList = new OBJElement();

        while (file.ReadNextLineInto(currentLineBuffer))
        {                
            OBJLineCommand command = PeekCommandLine(currentLineBuffer);

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
                OBJElement* newelementList = (OBJElement*)realloc(ElementList, ++ElementListSize * sizeof(OBJElement));

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
        unsigned int elementIndex = 0;
        unsigned int currentPositionElement = 0;
        unsigned int currentTextureElement = 0;
        unsigned int currentNormalElement = 0;
        unsigned int currentParameterElement = 0;
        unsigned int currentFaceElement = 0;
        unsigned int materialIndex = 0;
        unsigned int materialIDCounter = 0;

        OBJElement* elemtent = &ElementList[elementIndex++];
        bool isInMesh = false;      
        
        file.CursorToBeginning();

        // Parse
        while (file.ReadNextLineInto(currentLineBuffer))
        {
            OBJLineCommand command = PeekCommandLine(currentLineBuffer);
            bool fetchNextMesh = ShouldCreateNewMesh(command, isInMesh);
                      
            if (fetchNextMesh)
            {
                elemtent = &ElementList[elementIndex++];    

                currentPositionElement = 0;
                currentTextureElement = 0;
                currentNormalElement = 0;
                currentParameterElement = 0;
                currentFaceElement = 0;
            }

            switch (command)
            {
                case OBJLineCommand::MaterialLibraryInclude:
                { 
                    char materialFilePath[_MAX_PATH];

                    AsciiString::Parse
                    (
                        currentLineBuffer,
                        "$s",
                        materialFilePath
                    );

                    AsciiString materialFileFolder;
                    AsciiString filePathS(filePath);
                    AsciiString materialPathS(materialFilePath);
                    int position = filePathS.FindLast('/');
                    bool hasSlash = position != -1;
                    bool doesFileExist = false;

                    if (hasSlash)
                    {
                        filePathS.Cut(0, position + 1, materialFileFolder);
                        materialFileFolder.AttachToBack(materialPathS);
                    }
                    else
                    {
                        materialFileFolder.Copy(materialPathS);
                    }

                    const char* filePath = &materialFileFolder[0];
                    FileStream fileStreamMaterial;
                    doesFileExist = File::DoesFileExist(filePath);

                    if (doesFileExist)
                    {
                        MTL& material = MaterialFileList[materialIndex++];
                   
                        material.Load(filePath);

                        //material.PrintContent();
                    }
                    else
                    {
                        printf("[Warning] Material (.mtl) file is missing at path <%s>\n", &materialFileFolder[0]);
                    }
                    break;
                }
                case OBJLineCommand::MaterialLibraryUse:
                {
                    char usedMaterialName[MTLNameSize];
                    unsigned int materialID = -1;
                 
                    AsciiString::Parse
                    (
                        currentLineBuffer,
                        "$s",
                        usedMaterialName
                    );

                    for (unsigned int i = 0; i < MaterialFileListSize; i++)
                    {
                        MTL& mtl = MaterialFileList[i];
                        unsigned int materialListSize = mtl.MaterialListSize;

                        for (unsigned int j = 0; j < materialListSize; j++)
                        {
                            MTLMaterial& material = mtl.MaterialList[j];                            
                            bool isSameName = strncmp(material.Name, usedMaterialName, MTLNameSize) == 0;

                            if (isSameName)
                            {
                                materialID = j;
                                //printf("%s == %s >> %i\n", material->Name.c_str(), materialName.c_str(), materialID);
                                break;
                            }
                        }
                    }

                    elemtent->MaterialListIndex = materialID;

                    break;
                }

                case OBJLineCommand::ObjectName:
                {
                    strncpy(elemtent->Name, currentLineBuffer + 2, OBJElementNameLength);
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

                    AsciiString::Parse
                    (
                        currentLineBuffer,
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

                    AsciiString::Parse
                    (
                        currentLineBuffer,
                        "$ff",
                        &point.X, &point.Y 
                    );

                    break;
                }        
                case OBJLineCommand::SmoothShading:
                    break;

                case OBJLineCommand::FaceElement:
                {
                    /*
                    line.Splitt(' ', faceTextCache);
                    unsigned int amountOfValuesline = line.Count(' ');
                    for (unsigned int i = 1; i <= amountOfValuesline; i++)
                    {
                        faceTextCache[i].Splitt('/', trippelTextCache);
                        // Possiple error if char is '/'

                        elemtent->FaceElementList[currentFaceElement++].Set
                        (
                            trippelTextCache[0].ToInt(),
                            trippelTextCache[1].ToInt(),
                            trippelTextCache[2].ToInt()
                        );

                         usedFacesBefore = true;
                    }*/                   

                    assert(currentFaceElement < elemtent->FaceElementList.Size());

                    Vector3<unsigned int>& vectorA = elemtent->FaceElementList[currentFaceElement++];
                    Vector3<unsigned int>& vectorB = elemtent->FaceElementList[currentFaceElement++];
                    Vector3<unsigned int>& vectorC = elemtent->FaceElementList[currentFaceElement++];


                    switch (VertexStructureSize)
                    {
                        case 3:
                        {
                            AsciiString::Parse
                            (
                                currentLineBuffer,
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

                            AsciiString::Parse
                            (
                                currentLineBuffer,
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
}

BF::FileActionResult BF::OBJ::Save(const char* filePath)
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

            strncpy(material.Name, mtlMaterial.Name, MTLNameSize);
            strncpy(material.FilePath, mtlMaterial.TextureFilePath, MTLFilePath);
            memcpy(material.Ambient, mtlMaterial.Ambient, 3 * sizeof(float));
            memcpy(material.Diffuse, mtlMaterial.Diffuse, 3 * sizeof(float));
            memcpy(material.Specular, mtlMaterial.Specular, 3 * sizeof(float));
            memcpy(material.Emission, mtlMaterial.Emission, 3 * sizeof(float));
        }
    }

    model.MeshListSize = ElementListSize;
    model.MeshList = new Mesh[ElementListSize];

    strncpy(model.Name, Name, OBJNameSize);

    for (size_t elementIndex = 0; elementIndex < model.MeshListSize; elementIndex++)
    {
        OBJElement& element = ElementList[elementIndex]; // Get current source Mesh
        Mesh& mesh = model.MeshList[elementIndex]; // Get current target Mesh
        unsigned int vertexListSize = element.VertexPositionList.Size();
        unsigned int faceElementListSize = element.FaceElementList.Size();
        unsigned int normalListSize = element.VertexNormalPositionList.Size();
        unsigned int textureCoordinateListSize = element.TextureCoordinateList.Size();

        mesh.Structure.RenderType = VertexStructureSize == 4 ? RenderMode::Square : RenderMode::Triangle;

        mesh.Structure.Allocate(faceElementListSize * (3 + 3 + 4 + 2), faceElementListSize);
        mesh.RenderInfo.MaterialID = element.MaterialListIndex;

        strncpy(mesh.Name, element.Name, OBJElementNameLength);

        size_t vertecDataIndex = 0;
        float* vertexDataArray = mesh.Structure.VertexData;
             
        for (size_t i = 0; i < faceElementListSize; i++)
        {
            Vector3<unsigned int>& indexPosition = element.FaceElementList[i];
            unsigned int vertexPositionID = indexPosition.X - 1;
            unsigned int texturePointID = indexPosition.Y - 1; // TODO: REMOVED -1 form all positions
            unsigned int normalVectorID = indexPosition.Z -1;
            Vector3<float>* vertexData = GlobalVertexPosition(vertexPositionID);
            Vector2<float>* textureData = GlobalTextureCoordinate(texturePointID);
            Vector3<float>* normalData = GlobalVertexNormalPosition(normalVectorID);
            Vector4<float> color(1.0f,1.0f,1.0f,1.0f);
            bool vertexPositionIDValid = vertexData;
            bool texturePointIDValid = textureData;
            bool normalVectorIDValid = normalData;

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

            mesh.Structure.IndexData[i] = i;

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
    printf("| (OBJ) Name: %-64s |\n", Name);
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