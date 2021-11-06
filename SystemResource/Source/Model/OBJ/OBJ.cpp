#include "OBJ.h"

#include "../../File/File.h"
#include "../../File/FileStream.h"
#include "../../Container/AsciiString.h"

BF::OBJ::OBJ()
{
    strcpy_s(Name, OBJNameSize, "[N/A]");

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
                        "§s",
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
                        "§s",
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
                    strcpy_s(elemtent->Name, OBJElementNameLength, currentLineBuffer + 2);
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
                        "§fff",
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
                        "§ff",
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
                                "§uuuuuuuuu",
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
                                "§uuuuuuuuuuuu",
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

    model.MeshListSize = ElementListSize;
    model.MeshList = new Mesh[ElementListSize];
  
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

    for (size_t elementIndex = 0; elementIndex < model.MeshListSize; elementIndex++)
    {
        OBJElement& element = ElementList[elementIndex]; // Get current source Mesh
        Mesh& mesh = model.MeshList[elementIndex]; // Get current target Mesh
        unsigned int vertexListSize = element.VertexPositionList.Size();
        unsigned int faceElementListSize = element.FaceElementList.Size();
        unsigned int normalListSize = element.VertexNormalPositionList.Size();
        unsigned int textureCoordinateListSize = element.TextureCoordinateList.Size();

       // TODO: strncpy(mesh.Name, element.Name, ResourceNameSize);
    
        mesh.Structure.RenderType = VertexStructureSize == 4 ? RenderMode::Square : RenderMode::Triangle;

        mesh.Structure.Allocate(faceElementListSize * (3+3+4+2), faceElementListSize);
        mesh.RenderInfo.MaterialID = element.MaterialListIndex;

        size_t vertecDataIndex = 0;
        float* vertexDataArray = mesh.Structure.VertexData;

        for (size_t i = 0; i < faceElementListSize; i++)
        {
            Vector3<unsigned int>& indexPosition = element.FaceElementList[i];
            unsigned int vertexPositionID = indexPosition.X - 1;
            unsigned int texturePointID = indexPosition.Y - 1;
            unsigned int normalVectorID = indexPosition.Z - 1;

            Vector3<float>& vertexData = element.VertexPositionList[vertexPositionID];
            Vector2<float>& textureData = element.TextureCoordinateList[vertexPositionID];
            Vector3<float>& normalData = element.VertexNormalPositionList[vertexPositionID];

            mesh.Structure.IndexData[i] = i;
            vertexDataArray[vertecDataIndex++] = vertexData.X;
            vertexDataArray[vertecDataIndex++] = vertexData.Y;
            vertexDataArray[vertecDataIndex++] = vertexData.Z;
            vertexDataArray[vertecDataIndex++] = normalData.X;
            vertexDataArray[vertecDataIndex++] = normalData.Y;
            vertexDataArray[vertecDataIndex++] = normalData.Z;
            vertexDataArray[vertecDataIndex++] = 1;
            vertexDataArray[vertecDataIndex++] = 1;
            vertexDataArray[vertecDataIndex++] = 1;
            vertexDataArray[vertecDataIndex++] = 1;
            vertexDataArray[vertecDataIndex++] = normalData.X;
            vertexDataArray[vertecDataIndex++] = normalData.Y;
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
    printf(" +-------+-------+-------+-------+-------+-------\n");
    printf(" | Object: %-30s |\n", Name);
    printf(" +-------+-------+-------+-------+-------+-------\n");
    printf(" | %5s | %5s | %5s | %5s | %5s | %s\n", "Vert", "Norm", "Text", "Para", "Face", "Name");
    printf(" +-------+-------+-------+-------+-------+-------\n");

    for (unsigned int i = 0; i < ElementListSize; i++)
    {
        OBJElement* waveFrontElement = &ElementList[i];

        unsigned int sizePos = waveFrontElement->VertexPositionList.Size();
        unsigned int sizeNormal = waveFrontElement->VertexNormalPositionList.Size();
        unsigned int sizeText = waveFrontElement->TextureCoordinateList.Size();
        unsigned int sizePara = waveFrontElement->VertexParameterList.Size();
        unsigned int sizeFace = waveFrontElement->FaceElementList.Size();

        printf(" | %5u | %5u | %5u | %5u | %5u | %s\n", sizePos, sizeNormal, sizeText, sizePara, sizeFace, &waveFrontElement->Name[0]);
    }

    printf(" +-------+-------+-------+-------+-------+-------\n");

    if (MaterialFileListSize == 0)
    {
        printf(" +-------+-------+-------+-------+-------+-------\n");
        printf(" | No Materials  |\n");
    }

    for (unsigned int i = 0; i < MaterialFileListSize; i++)
    {
        MTL& mtl = MaterialFileList[i];

        for (unsigned int j = 0; j < mtl.MaterialListSize; j++)
        {
            MTLMaterial& material = mtl.MaterialList[j];

            printf(" Material <%u> : %s\n", j, material.Name);
            printf(" - Ambient  [%4.4f|%4.4f|%4.4f]\n", material.Ambient[0], material.Ambient[1], material.Ambient[2]);
            printf(" - Diffuse  [%4.4f|%4.4f|%4.4f]\n", material.Diffuse[0], material.Ambient[1], material.Ambient[2]);
            printf(" - Specular [%4.4f|%4.4f|%4.4f]\n", material.Specular[0], material.Ambient[1], material.Ambient[2]);
        }

        printf(" +-------+-------+-------+-------+-------+-------\n");
    }
}