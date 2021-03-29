#include "OBJ.h"
#include "../../File/File.h"
#include "OBJLineCommand.h"

BF::OBJ::OBJ()
{
	Name.Copy("[N/A]");
	VertexStructureSize = -1;
}

void BF::OBJ::Load(AsciiString& filePath)
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
    unsigned int numberOfLines;
    List<AsciiString> lineList;
    List<OBJLineCommand> commandList;
    File file(filePath);

    file.ReadAsLines(lineList);

    numberOfLines = lineList.Size();

    commandList.ReSize(numberOfLines);

    Name.Copy(file.Path);

    // Translate to enum commands
    {
        bool usedFacesBefore = false;
        bool newMeshKey = false;
        bool checkedRenderType = false;
        unsigned int elementListSize = 1; // We will have at least one mesh.

        for (unsigned int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
        {
            OBJLineCommand* currentCommand = &commandList[lineIndex];
            AsciiString& line = lineList[lineIndex];
            unsigned char functionChar = line.GetFirstNonEmpty();

            switch (functionChar)
            {
                case 'm':
                    *currentCommand = OBJLineCommand::MaterialLibraryInclude;
                    break;

                case 'u':
                    *currentCommand = OBJLineCommand::MaterialLibraryUse;

                    if (usedFacesBefore)
                    {
                        newMeshKey = true;
                        usedFacesBefore = false;
                    }

                    break;

                case _characterComment:
                    *currentCommand = OBJLineCommand::Comment;
                    break;

                case _characterObjectName:
                    *currentCommand = OBJLineCommand::ObjectName;
                    newMeshKey = true;
                    break;

                case _characterSmoothShading:
                    *currentCommand = OBJLineCommand::SmoothShading;
                    break;

                case _characterFace:
                    *currentCommand = OBJLineCommand::FaceElement;
                    usedFacesBefore = true;

                    if (!checkedRenderType)
                    {
                        VertexStructureSize = line.Count('/') / 2;

                        checkedRenderType = true;
                    }

                    break;

                case _characterVertex:
                {
                    functionChar = (line)[1]; //  Potential error

                    switch (functionChar)
                    {
                        case _characterNone:
                            *currentCommand = OBJLineCommand::VertexGeometric;
                            break;

                        case _characterVertexTexture:
                            *currentCommand = OBJLineCommand::VertexTexture;
                            break;

                        case _characterVertexNormal:
                            *currentCommand = OBJLineCommand::VertexNormal;
                            break;

                        case _characterParameter:
                            *currentCommand = OBJLineCommand::VertexParameter;
                            break;

                        default:
                            *currentCommand = OBJLineCommand::Invalid;
                            break;
                    }

                    break;
                }

                case _characterNone:
                    *currentCommand = OBJLineCommand::None;
                    break;

                default:
                    *currentCommand = OBJLineCommand::Invalid;
                    break;
            }

            if (newMeshKey)
            {
                newMeshKey = false;
                elementListSize++;
            }
        }

        ElementList.ReSize(elementListSize-1);
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
                    faceElementListSize++;

                    usedFacesBefore = true;
                    break;
            }

            if (newMeshKey && (elementIndex <= ElementList.Size()))
            {
                newMeshKey = false;

                faceElementListSize *= VertexStructureSize;

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

            faceElementListSize *= VertexStructureSize;

            elemtent->VertexPositionList.ReSize(vertexPositionListSize);
            elemtent->TextureCoordinateList.ReSize(textureCoordinateListSize);
            elemtent->VertexNormalPositionList.ReSize(vertexNormalPositionListSize);
            elemtent->VertexParameterList.ReSize(vertexParameterListSize);
            elemtent->FaceElementList.ReSize(faceElementListSize);

            Materials.ReSize(materialsCounter);
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
        OBJElement* elemtent = &ElementList[elementIndex++];
        //List<Position<unsigned int>> indexPositionCache(waveFront->VertexStructureSize); // 36 Byte alloc
        unsigned int faceStructureSize = VertexStructureSize;


        printf("Structursize <%u>\n", faceStructureSize);
        List<AsciiString> faceTextCache(faceStructureSize);
        List<AsciiString> dupTextCache(2);
        List<AsciiString> trippelTextCache(3); // X, Y [28 Byte alloc]
        List<AsciiString> quadTextCache(4); // v X, Y, Z [36 Byte alloc]
        Position<float>* currentVectorValue;

        // Parse
        for (unsigned int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
        {
            AsciiString* line = &lineList[lineIndex];
            OBJLineCommand command = commandList[lineIndex];

            switch (command)
            {
                case OBJLineCommand::MaterialLibraryInclude:
                {

                    line->Splitt(' ', trippelTextCache);

                    AsciiString& mtlfilePath = trippelTextCache[1]; //[20 Byte]
                    AsciiString materialFileFolder;
                    int position = filePath.FindLast('/');
                    bool hasSlash = position != -1;
                    bool doesFileExist = false;

                    if (hasSlash)
                    {
                        filePath.Cut(0, position + 1, materialFileFolder);
                        materialFileFolder.AttachToBack(mtlfilePath);
                    }
                    else
                    {
                        materialFileFolder.Copy(mtlfilePath);
                    }

                    //doesFileExist = FileLoader::DoesFileExist(materialFileFolder);

                    if (doesFileExist)
                    {
                       // MTL* materialFile = MTLLoader::LoadFromFile(materialFileFolder);

                        //waveFront->Materials[materialIndex++] = *materialFile;
                    }
                    else
                    {
                        printf("[Warning] Material (.mtl) file is missing at path <%s>\n", &materialFileFolder[0]);
                    }


                    //delete materialFile;

                }
                break;

                case OBJLineCommand::MaterialLibraryUse:
                {

                    line->Splitt(' ', dupTextCache);
                    AsciiString& materialName = line[1];
                    unsigned int materialID = -1;

                    for (unsigned int i = 0; i < Materials.Size(); i++)
                    {
                        MTL* mtl = &Materials[i];

                        for (unsigned int j = 0; j < mtl->MaterialList.Size(); j++)
                        {
                            Material* material = &mtl->MaterialList[j];

                            if (material->Name.Compare(materialName))
                            {
                                materialID = j;
                                j = -1;
                                i = -1;

                                //printf("%s == %s >> %i\n", material->Name.c_str(), materialName.c_str(), materialID);
                                //break;
                            }
                        }
                    }

                    elemtent->MaterialID = materialID;

                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        newMeshKey = true;
                    }

                    break;
                }


                case OBJLineCommand::ObjectName:
                    line->Cut(2, elemtent->Name);

                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        newMeshKey = true;
                    }
                    break;


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

                    line->Splitt(' ', quadTextCache);

                    currentVectorValue->Set
                    (
                        quadTextCache[1].ToFloat(), // X
                        quadTextCache[2].ToFloat(), // Y
                        quadTextCache[3].ToFloat() // Z
                    );
                }
                break;

                case OBJLineCommand::VertexTexture:
                {
                    Point<float>& point = elemtent->TextureCoordinateList[currentTextureElement++];

                    line->Splitt(' ', trippelTextCache);

                    point.Set
                    (
                        trippelTextCache[1].ToFloat(),
                        trippelTextCache[2].ToFloat()
                    );
                }
                break;


                case OBJLineCommand::SmoothShading:
                    break;

                case OBJLineCommand::FaceElement:
                    line->Splitt(' ', faceTextCache);

                    for (unsigned int i = 1; i <= faceStructureSize; i++)
                    {
                        faceTextCache[i].Splitt('/', trippelTextCache);
                        // Possiple error if char is '/'

                        elemtent->FaceElementList[currentFaceElement++].Set
                        (
                            trippelTextCache[0].ToInt(),
                            trippelTextCache[1].ToInt(),
                            trippelTextCache[2].ToInt()
                        );
                    }

                    usedFacesBefore = true;

                    break;

                case OBJLineCommand::Invalid:
                case OBJLineCommand::None:
                case OBJLineCommand::Comment:
                default:
                    break;
            }

            if (newMeshKey) // && elementIndex < waveFront->ElementList.Size.Value
            {
                newMeshKey = false;

                elemtent = &ElementList[elementIndex++];

                currentPositionElement = 0;
                currentTextureElement = 0;
                currentNormalElement = 0;
                currentParameterElement = 0;
                currentFaceElement = 0;
            }
        }
    }

    PrintData();
}

void BF::OBJ::Save(AsciiString& filePath)
{
}

void BF::OBJ::Convert(Model& model)
{
    bool usedNormals = false;
    unsigned int vertexListSize = VertexStructureSize;

    if ((vertexListSize % 3) == 0)
    {
        model.RenderInformation.RenderType = RenderMode::Triangle;
    }

    if ((vertexListSize % 4) == 0)
    {
        model.RenderInformation.RenderType = RenderMode::Square;
    }

    model.MeshList.ReSize(ElementList.Size());

    //unsigned int offset = 0;
    unsigned int size = model.MeshList.Size();
    unsigned int materialSize = Materials.Size();

    if (materialSize > 0)
    {
        unsigned int materialSize = Materials[0].MaterialList.Size();
        unsigned int colorIndex = 0;

        model.ColorList.ReSize(materialSize);

        for (unsigned int i = 0; i < Materials.Size(); i++)
        {
            MTL* mtl = &Materials[i];

            for (unsigned int j = 0; j < materialSize; j++)
            {
                Material* material = &mtl->MaterialList[j];

                float r = material->Diffuse.X;
                float g = material->Diffuse.Y;
                float b = material->Diffuse.Z;

                model.ColorList[colorIndex++].SetColor(r, g, b);
            }
        }
    }

    for (unsigned int elementIndex = 0; elementIndex < size; elementIndex++)
    {
        OBJElement* element = &ElementList[elementIndex]; // Get current source Mesh
        Mesh* mesh = &model.MeshList[elementIndex]; // Get current target Mesh
        unsigned int vertexListSize = element->VertexPositionList.Size();
        unsigned int faceElementListSize = element->FaceElementList.Size();
        unsigned int normalListSize = element->VertexNormalPositionList.Size();
        unsigned int textureCoordinateListSize = element->TextureCoordinateList.Size();

        mesh->Name = element->Name;

        // Color

        // Vertex Data
        mesh->VertexList.ReSize(vertexListSize);
        for (unsigned int i = 0; i < vertexListSize; i++)
        {
            Vertex* vertex = &mesh->VertexList[i];
            vertex->ColorID = element->MaterialID;
            vertex->CurrentPosition = element->VertexPositionList[i];

            //printf("V: <%f|%f|%f> C:%u\n", vertex->CurrentPosition.X, vertex->CurrentPosition.Y, vertex->CurrentPosition.Z, vertex->ColorID);
        }

        mesh->TexturePointList.ReSize(textureCoordinateListSize);
        for (unsigned int i = 0; i < textureCoordinateListSize; i++)
        {
            mesh->TexturePointList[i] = element->TextureCoordinateList[i];
            // printf("T: <%f|%f>\n", mesh->TexturePointList[i].X, mesh->TexturePointList[i].Y);
        }

        if (normalListSize > 0)
        {
            usedNormals = true;
            mesh->NormalPointList.ReSize(normalListSize);
            for (unsigned int i = 0; i < normalListSize; i++)
            {
                mesh->NormalPointList[i] = element->VertexNormalPositionList[i];
                //printf("N: <%f|%f|%f>\n", mesh->NormalPointList[i].X, mesh->NormalPointList[i].Y, mesh->NormalPointList[i].Z);
            }
        }

        // Index Data
        mesh->IndexList.ReSize(faceElementListSize);
        for (unsigned int i = 0; i < faceElementListSize; i++)
        {
            Position<unsigned int>* indexPosition = &element->FaceElementList[i];
            MeshIndexData* meshData = &mesh->IndexList[i];
            meshData->VertexPositionID = indexPosition->X - 1;
            meshData->TexturePointID = indexPosition->Y - 1;
            meshData->NormalVectorID = indexPosition->Z - 1;

            //printf("F: <%5u|%5u|%5u>\n", meshData->VertexPositionID, meshData->TexturePointID, meshData->NormalVectorID);
        }
    }

    if (!usedNormals)
    {
        model.CalculateNormalVectors();
    }

    model.UpdateGlobalMesh();
}

void BF::OBJ::PrintData()
{
    printf(" +-------+-------+-------+-------+-------+-------\n");
    printf(" | Object: %s\n", &Name[0]);
    printf(" +-------+-------+-------+-------+-------+-------\n");
    printf(" | %5s | %5s | %5s | %5s | %5s | %s\n", "Vert", "Norm", "Text", "Para", "Face", "Name");
    printf(" +-------+-------+-------+-------+-------+-------\n");

    for (unsigned int i = 0; i < ElementList.Size(); i++)
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

    for (unsigned int i = 0; i < Materials.Size(); i++)
    {
        MTL* mtl = &Materials[i];

        for (unsigned int j = 0; j < mtl->MaterialList.Size(); j++)
        {
            Material* material = &mtl->MaterialList[j];

            printf(" Material: %s\n", &material->Name[0]);
            printf(" - Ambient  [%4.4f|%4.4f|%4.4f]\n", material->Ambient.X, material->Ambient.Y, material->Ambient.Z);
            printf(" - Diffuse  [%4.4f|%4.4f|%4.4f]\n", material->Diffuse.X, material->Ambient.Y, material->Ambient.Z);
            printf(" - Specular [%4.4f|%4.4f|%4.4f]\n", material->Specular.X, material->Ambient.Y, material->Ambient.Z);
        }

        printf(" +-------+-------+-------+-------+-------+-------\n");
    }
}