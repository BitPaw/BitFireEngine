#include "OBJ.h"
#include "../../File/File.h"
#include <cstdarg>
#include "../../Container/AsciiString.h"

void StringParse(char* buffer, const char* syntax, ...)
{
    va_list args;
    va_start(args, syntax);

    int startIndex = 0;
    int stopIndex = 0;
    int command = 0;
    bool finished = false;

    while (!finished)
    {
        char commandKey = syntax[command++];

        {
            while (true)
            {
                char current = buffer[stopIndex++];
                finished = current == '\0';

                if (current == ' ' || finished || current == '/')
                {
                    break;
                }
            }


            switch (commandKey)
            {
                case 's':
                {
                    char* destination = va_arg(args, char*);
                    char* source = &buffer[startIndex];
                    unsigned int length = stopIndex - startIndex - 1;

                    memcpy(destination, source, length);
                    destination[length] = '\0';
                    break;
                }


                case 'u':
                {
                    unsigned int* i = va_arg(args, unsigned int*);
                    char* source = &buffer[startIndex];

                    *i = BF::AsciiString::ToInt(source);

                    break;
                }


                case 'f':
                {

                    float* number = va_arg(args, float*);
                    char* source = &buffer[startIndex];

                    (*number) = BF::AsciiString::ToFloat(source);

                    break;
                }

                case 'c':
                {
                    int c = va_arg(args, int);
                    std::cout << static_cast<char>(c) << '\n';
                    break;
                }


                default:
                    break;
            }

        }      
      
            
       startIndex = stopIndex;
        
    }

    va_end(args);
}

BF::OBJ::OBJ()
{
    strcpy_s(Name, OBJNameSize, "[N/A]");

    VertexStructureSize = 0;

    MaterialListSize = 0;
    MaterialList = 0;

    ElementListSize = 0;
    ElementList = 0;
}

BF::OBJ::~OBJ()
{
   // free(MaterialList);
   // free(ElementList);
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



void BF::OBJ::Load(const char* filePath)
{
    bool isFirstVertex = true;
    char currentLineBuffer[FileLineBufferSize];
    File file(filePath, true); 
    unsigned int numberOfLines = file.CountAmountOfLines();

    strcpy(Name, filePath);

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

        for (size_t lineIndex = 0; lineIndex <= numberOfLines; lineIndex++)
        {
            unsigned int writtenBytes = file.ReadNextLineInto(currentLineBuffer);                       
            OBJLineCommand command = PeekCommandLine(currentLineBuffer);

            switch (command)
            {
                default:
                case OBJLineCommand::Invalid:
                case OBJLineCommand::None:
                case OBJLineCommand::Comment:
                    break;

                case OBJLineCommand::MaterialLibraryInclude:
                    ++MaterialListSize;
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

            if (!(lineIndex < numberOfLines))
            {
                OBJElement& element = ElementList[ElementListSize - 1];

                element.VertexPositionList.ReSize(vertexPositionListSize);
                element.TextureCoordinateList.ReSize(vertexTextureCoordinateListSize);
                element.VertexNormalPositionList.ReSize(vertexNormalPositionListSize);
                element.VertexParameterList.ReSize(vertexParameterListSize);
                element.FaceElementList.ReSize(faceElementListSize);
            }

            if (fetchNextMesh)
            {
                OBJElement* newelementList = (OBJElement*)realloc(ElementList, ++ElementListSize * sizeof(OBJElement));

                if (!newelementList)
                {
                    // Out of memory
                    return;
                }

                ElementList = newelementList;

                OBJElement& oldElement = newelementList[ElementListSize - 2];
                OBJElement& newElement = newelementList[ElementListSize - 1];

                newElement = OBJElement();

                oldElement.VertexPositionList.ReSize(vertexPositionListSize);
                oldElement.TextureCoordinateList.ReSize(vertexTextureCoordinateListSize);
                oldElement.VertexNormalPositionList.ReSize(vertexNormalPositionListSize);
                oldElement.VertexParameterList.ReSize(vertexParameterListSize);
                oldElement.FaceElementList.ReSize(faceElementListSize);

                vertexPositionListSize = 0;
                vertexTextureCoordinateListSize = 0;
                vertexNormalPositionListSize = 0;
                vertexParameterListSize = 0;
                faceElementListSize = 0;              

                isInMesh = false;
            }
        }                
   
        if (MaterialListSize > 0)
        {
            MaterialList = new MTL[MaterialListSize];
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

        char dummyBuffer[FileLineBufferSize];
        
        file.CursorToBeginning();

        // Parse
        for (unsigned int lineIndex = 0; lineIndex <= numberOfLines; lineIndex++)
        {
            unsigned int writtenBytes = file.ReadNextLineInto(currentLineBuffer);
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

                    //sscanf(currentLineBuffer, "%s %s", dummyBuffer, materialFilePath);

                    StringParse
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

                    File file(&materialFileFolder[0]);
                    doesFileExist = file.DoesFileExist();

                    if (doesFileExist)
                    {
                        MTL& material = MaterialList[materialIndex++];
                   
                        material.Load(file.Path);

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
                 
                    //sscanf(currentLineBuffer, "%s %s", dummyBuffer, usedMaterialName);    

                    StringParse
                    (
                        currentLineBuffer,
                        "§s",
                        usedMaterialName
                    );

                    for (unsigned int i = 0; i < MaterialListSize; i++)
                    {
                        MTL& mtl = MaterialList[i];
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
                    Vector3<float>* currentVectorValue;

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

                        default:
                            throw "Error";
                    }


                    //sscanf(currentLineBuffer, "%s %f %f %f", dummyBuffer, &currentVectorValue->X, &currentVectorValue->Y, &currentVectorValue->Z);

                    StringParse
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

                    StringParse
                    (
                        currentLineBuffer,
                        "§ff",
                        &point.X, &point.Y 
                    );

                   // sscanf(currentLineBuffer, "%s %f %f", dummyBuffer, &point.X, &point.Y);

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
                            StringParse
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

                            StringParse
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

       

                    // sscanf(currentLineBuffer, "%s %s %s %s", dummyBuffer, cacheA, cacheB, cacheC);
                   

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

void BF::OBJ::Save(const char* filePath)
{
}

void BF::OBJ::Convert(Model& model)
{
    bool usedNormals = false;

    switch (VertexStructureSize)
    {
        case 3:
        {
            model.RenderInformation.RenderType = RenderMode::Triangle;
            break;
        }

        case 4:
        {
            model.RenderInformation.RenderType = RenderMode::Square;
            break;
        }
    }

    model.MeshList.ReSize(ElementListSize);

    // Convert Materials
    if (MaterialListSize > 0)
    {
        unsigned int mtlMaterialListSize = MaterialList[0].MaterialListSize;

        model.MaterialList.ReSize(mtlMaterialListSize);

        for (unsigned int mtlIndex = 0; mtlIndex < MaterialListSize; mtlIndex++)
        {
            MTL& mtl = MaterialList[mtlIndex];

            for (unsigned int mtlMaterialIndex = 0; mtlMaterialIndex < mtlMaterialListSize; mtlMaterialIndex++)
            {
                MTLMaterial& mtlMaterial = mtl.MaterialList[mtlMaterialIndex];
                Material& material = model.MaterialList[mtlMaterialIndex];

                strcpy(material.Name, mtlMaterial.Name);
                strcpy(material.TextureFilePath, mtlMaterial.TextureFilePath);
                memcpy(material.Ambient, mtlMaterial.Ambient, 3 * sizeof(float));
                memcpy(material.Diffuse, mtlMaterial.Diffuse, 3 * sizeof(float));
                memcpy(material.Specular, mtlMaterial.Specular, 3 * sizeof(float));
                memcpy(material.Emission, mtlMaterial.Emission, 3 * sizeof(float));
            }
        }
    }

    for (unsigned int elementIndex = 0; elementIndex < model.MeshList.Size(); elementIndex++)
    {
        OBJElement& element = ElementList[elementIndex]; // Get current source Mesh
        Mesh& mesh = model.MeshList[elementIndex]; // Get current target Mesh
        unsigned int vertexListSize = element.VertexPositionList.Size();
        unsigned int faceElementListSize = element.FaceElementList.Size();
        unsigned int normalListSize = element.VertexNormalPositionList.Size();
        unsigned int textureCoordinateListSize = element.TextureCoordinateList.Size();

        strcpy(mesh.Name, element.Name);

        mesh.MeshMaterial = element.MaterialListIndex == -1 ? nullptr : &model.MaterialList[element.MaterialListIndex];

        // Color

        // Vertex Data
        mesh.VertexList.ReSize(vertexListSize);
        for (unsigned int i = 0; i < vertexListSize; i++)
        {
            Vertex& vertex = mesh.VertexList[i];
            vertex.ColorID = (unsigned int)-1;
            vertex.CurrentPosition = element.VertexPositionList[i];

            //printf("V: <%f|%f|%f> C:%u\n", vertex->CurrentPosition.X, vertex->CurrentPosition.Y, vertex->CurrentPosition.Z, vertex->ColorID);
        }

        mesh.TexturePointList.ReSize(textureCoordinateListSize);
        for (unsigned int i = 0; i < textureCoordinateListSize; i++)
        {
            mesh.TexturePointList[i] = element.TextureCoordinateList[i];
            // printf("T: <%f|%f>\n", mesh->TexturePointList[i].X, mesh->TexturePointList[i].Y);
        }

        if (normalListSize > 0)
        {
            usedNormals = true;
            mesh.NormalPointList.ReSize(normalListSize);
            for (unsigned int i = 0; i < normalListSize; i++)
            {
                mesh.NormalPointList[i] = element.VertexNormalPositionList[i];
                //printf("N: <%f|%f|%f>\n", mesh->NormalPointList[i].X, mesh->NormalPointList[i].Y, mesh->NormalPointList[i].Z);
            }
        }

        // Index Data
        mesh.IndexList.ReSize(faceElementListSize);
        for (unsigned int i = 0; i < faceElementListSize; i++)
        {
            Vector3<unsigned int>& indexPosition = element.FaceElementList[i];
            MeshIndexData& meshData = mesh.IndexList[i];
            meshData.VertexPositionID = indexPosition.X - 1;
            meshData.TexturePointID = indexPosition.Y - 1;
            meshData.NormalVectorID = indexPosition.Z - 1;

            //printf("F: <%5u|%5u|%5u>\n", meshData->VertexPositionID, meshData->TexturePointID, meshData->NormalVectorID);
        }
    }

    if (!usedNormals)
    {
        model.CalculateNormalVectors();
    }

    model.UpdateGlobalMesh();
}

void BF::OBJ::Clear()
{
    free(MaterialList);
    free(ElementList);

    VertexStructureSize = 0xFF;
    MaterialListSize = 0;
    MaterialList = 0;
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

    if (MaterialListSize == 0)
    {
        printf(" +-------+-------+-------+-------+-------+-------\n");
        printf(" | No Materials  |\n");
    }

    for (unsigned int i = 0; i < MaterialListSize; i++)
    {
        MTL& mtl = MaterialList[i];

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