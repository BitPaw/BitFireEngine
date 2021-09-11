#include "OBJ.h"
#include "../../File/File.h"
#include "OBJLineCommand.h"
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

                    BF::AsciiString::ToInt(source, (int*)i);

                    break;
                }


                case 'f':
                {

                    float* number = va_arg(args, float*);
                    char* source = &buffer[startIndex];

                    (*number) = strtof(source, 0);

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
    strcpy(Name, "[N/A]");

    VertexStructureSize = -1;

    MaterialListSize = 0;
    MaterialList = 0;

    ElementListSize = 0;
    ElementList = 0;
}

BF::OBJ::~OBJ()
{
    delete[] MaterialList;
    delete[] ElementList;
}

void BF::OBJ::Load(const char* filePath)
{
    const char _characterComment = '#';
    const char _characterObjectName = 'o';
    const char _characterSmoothShading = 's';
    const char _characterFace = 'f';
    const char _characterNone = ' ';
    const char _characterVertex = 'v';
    const char _characterVertexTexture = 't';
    const char _characterVertexNormal = 'n';
    const char _characterParameter = 'p';

    bool isFirstVertex = true;
    File file(filePath);
    file.Read();

    unsigned int numberOfLines = file.CountAmountOfLines();
    List<OBJLineCommand> commandList;
    char currentLineBuffer[100];

    commandList.ReSize(numberOfLines);

    strcpy(Name, filePath);

    // Translate to enum commands
    {
        bool usedFacesBefore = false;
        bool newMeshKey = false;
        bool checkedRenderType = false;
        unsigned int elementListSize = 1; // We will have at least one mesh.

        for (unsigned int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
        {
            OBJLineCommand& currentCommand = commandList[lineIndex];

            file.ReadNextLineInto(currentLineBuffer);

            unsigned char functionChar = currentLineBuffer[0];

            switch (functionChar)
            {
                case 'm':
                    currentCommand = OBJLineCommand::MaterialLibraryInclude;
                    break;

                case 'u':
                    currentCommand = OBJLineCommand::MaterialLibraryUse;

                    if (usedFacesBefore)
                    {
                        newMeshKey = true;
                        usedFacesBefore = false;
                    }

                    break;

                case '#':
                    currentCommand = OBJLineCommand::Comment;
                    break;

                case 'o':
                    currentCommand = OBJLineCommand::ObjectName;
                    newMeshKey = true;
                    break;

                case 's':
                    currentCommand = OBJLineCommand::SmoothShading;
                    break;

                case 'f':
                    currentCommand = OBJLineCommand::FaceElement;
                    usedFacesBefore = true;

                    if (!checkedRenderType)
                    {
                        checkedRenderType = true;
                    }

                    break;

                case 'v':
                {
                    functionChar = (currentLineBuffer)[1]; //  Potential error

                    switch (functionChar)
                    {
                        case ' ':
                            currentCommand = OBJLineCommand::VertexGeometric;
                            break;

                        case 't':
                            currentCommand = OBJLineCommand::VertexTexture;
                            break;

                        case 'n':
                            currentCommand = OBJLineCommand::VertexNormal;
                            break;

                        case 'p':
                            currentCommand = OBJLineCommand::VertexParameter;
                            break;

                        default:
                            currentCommand = OBJLineCommand::Invalid;
                            break;
                    }

                    break;
                }

                case ' ':
                    currentCommand = OBJLineCommand::None;
                    break;

                default:
                    currentCommand = OBJLineCommand::Invalid;
                    break;
            }

            if (newMeshKey)
            {
                newMeshKey = false;
                elementListSize++;
            }
        }

        ElementListSize = elementListSize - 1;
        ElementList = new OBJElement[elementListSize - 1];
    }

    // Space lookup
    {
        bool usedFacesBefore = false;
        bool newMeshKey = false;

        unsigned int elementIndex = 0;
        unsigned int materialsCounter = 0;

        unsigned int vertexPositionListSize = 0;
        unsigned int textureCoordinateListSize = 0;
        unsigned int vertexNormalPositionListSize = 0;
        unsigned int vertexParameterListSize = 0;
        unsigned int faceElementListSize = 0;

        OBJElement* elemtent = &ElementList[elementIndex++];

        VertexStructureSize = 0;

        // How many data do i need?
        for (unsigned int i = 0; i < numberOfLines; i++)
        {
            OBJLineCommand& command = commandList[i];

            switch (command)
            {
                case OBJLineCommand::Invalid:
                    break;

                case OBJLineCommand::None:
                    break;

                case OBJLineCommand::Comment:
                    break;

                case OBJLineCommand::MaterialLibraryInclude:
                    materialsCounter++;
                    break;

                case OBJLineCommand::MaterialLibraryUse:
                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        newMeshKey = true;
                    }

                    break;

                case OBJLineCommand::ObjectName:
                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        newMeshKey = true;
                    }

                    break;

                case OBJLineCommand::VertexGeometric:
                    vertexPositionListSize++;
                    break;

                case OBJLineCommand::VertexTexture:
                    textureCoordinateListSize++;
                    break;

                case OBJLineCommand::VertexNormal:
                    vertexNormalPositionListSize++;
                    break;

                case OBJLineCommand::VertexParameter:
                    vertexParameterListSize++;
                    break;

                case OBJLineCommand::SmoothShading:
                    break;

                case OBJLineCommand::FaceElement:
                {
                    unsigned int amount = 3;//lineList[i].Count(' ');

                    faceElementListSize += amount;

                    if (VertexStructureSize < amount)  VertexStructureSize = amount;

                    usedFacesBefore = true;
                    break;
                }

            }

            if (newMeshKey && (elementIndex <= ElementListSize))
            {
                newMeshKey = false;

                elemtent->VertexPositionList.ReSize(vertexPositionListSize);
                elemtent->TextureCoordinateList.ReSize(textureCoordinateListSize);
                elemtent->VertexNormalPositionList.ReSize(vertexNormalPositionListSize);
                elemtent->VertexParameterList.ReSize(vertexParameterListSize);
                elemtent->FaceElementList.ReSize(faceElementListSize);

                elemtent = &ElementList[elementIndex++];

                vertexPositionListSize = 0;
                textureCoordinateListSize = 0;
                vertexNormalPositionListSize = 0;
                vertexParameterListSize = 0;
                faceElementListSize = 0;
            }
        }

        // Register Memory
        {
            elemtent->VertexPositionList.ReSize(vertexPositionListSize);
            elemtent->TextureCoordinateList.ReSize(textureCoordinateListSize);
            elemtent->VertexNormalPositionList.ReSize(vertexNormalPositionListSize);
            elemtent->VertexParameterList.ReSize(vertexParameterListSize);
            elemtent->FaceElementList.ReSize(faceElementListSize);

            MaterialListSize = materialsCounter;
            MaterialList = new MTL[materialsCounter];
        }
    }

    // Exact Parse
    {
        bool usedFacesBefore = false;
        bool newMeshKey = false;

        unsigned int elementIndex = 0;
        unsigned int currentPositionElement = 0;
        unsigned int currentTextureElement = 0;
        unsigned int currentNormalElement = 0;
        unsigned int currentParameterElement = 0;
        unsigned int currentFaceElement = 0;
        unsigned int materialIndex = 0;
        unsigned int materialIDCounter = 0;
        OBJElement* elemtent = &ElementList[elementIndex++];
        //List<Position<unsigned int>> indexPositionCache(waveFront->VertexStructureSize); // 36 Byte alloc

        Vector3<float>* currentVectorValue;

        char dummyBuffer[50];
        
        file.CursorToBeginning();

        // Parse
        for (unsigned int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
        {
            file.ReadNextLineInto(currentLineBuffer);

            OBJLineCommand command = commandList[lineIndex];

            switch (command)
            {
                case OBJLineCommand::MaterialLibraryInclude:
                {
                    char materialFilePath[30];

                    sscanf(currentLineBuffer, "%s %s", dummyBuffer, materialFilePath);

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
                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        elemtent = &ElementList[elementIndex++];
                        newMeshKey = true;
                    }

                    char usedMaterialName[20];
                    unsigned int materialID = -1;

                    sscanf(currentLineBuffer, "%s %s", dummyBuffer, usedMaterialName);            

                    for (unsigned int i = 0; i < MaterialListSize; i++)
                    {
                        MTL& mtl = MaterialList[i];
                        unsigned int materialListSize = mtl.MaterialListSize;

                        for (unsigned int j = 0; j < materialListSize; j++)
                        {
                            MTLMaterial& material = mtl.MaterialList[j];
                            bool isSameName = strcmp(material.Name, usedMaterialName) == 0;

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
                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        elemtent = &ElementList[elementIndex++];
                        newMeshKey = true;
                    }

                    strcpy(elemtent->Name, currentLineBuffer + 2);

                    break;
                }

                case OBJLineCommand::VertexParameter:
                case OBJLineCommand::VertexNormal:
                case OBJLineCommand::VertexGeometric:
                {
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


                    sscanf(currentLineBuffer, "%s %f %f %f", dummyBuffer, &currentVectorValue->X, &currentVectorValue->Y, &currentVectorValue->Z);
                }
                break;

                case OBJLineCommand::VertexTexture:
                {
                    Vector2<float>& point = elemtent->TextureCoordinateList[currentTextureElement++];

                    sscanf(currentLineBuffer, "%s %f %f", dummyBuffer, &point.X, &point.Y);

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

                    Vector3<unsigned int>& vectorA = elemtent->FaceElementList[currentFaceElement++];
                    Vector3<unsigned int>& vectorB = elemtent->FaceElementList[currentFaceElement++];
                    Vector3<unsigned int>& vectorC = elemtent->FaceElementList[currentFaceElement++];

                    // sscanf(currentLineBuffer, "%s %s %s %s", dummyBuffer, cacheA, cacheB, cacheC);
                    StringParse
                    (
                        currentLineBuffer, 
                        "§uuuuuuuuu",
                        &vectorA.X, &vectorA.Y, &vectorA.Z,
                        &vectorB.X, &vectorB.Y, &vectorB.Z,
                        &vectorC.X, &vectorC.Y, &vectorC.Z
                    );

                    usedFacesBefore = true;

                    break;
                }

                case OBJLineCommand::Invalid:
                case OBJLineCommand::None:
                case OBJLineCommand::Comment:
                default:
                    break;
            }

            if (newMeshKey)
            {
                newMeshKey = false;

                currentPositionElement = 0;
                currentTextureElement = 0;
                currentNormalElement = 0;
                currentParameterElement = 0;
                currentFaceElement = 0;
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
            vertex.ColorID = -1;
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
    delete[] MaterialList;
    delete[] ElementList;

    VertexStructureSize = -1;
    MaterialListSize = 0;
    MaterialList = 0;
    ElementListSize = 0;
    ElementList = 0;
}

void BF::OBJ::PrintData()
{
    printf(" +-------+-------+-------+-------+-------+-------\n");
    printf(" | Object: %s\n", &Name[0]);
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