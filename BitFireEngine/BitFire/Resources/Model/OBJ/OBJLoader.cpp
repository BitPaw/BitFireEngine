#include "OBJLoader.h"
#include "MTL/MTL.h"
#include "MTL/MTLLoader.h"

BF::Position BF::OBJLoader::ParsePositionLine(std::string& line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);
    float z = std::stof(ss.Lines[3]);

    Position position(x, y, z);

    ss.Lines.DeleteAll();

    return position;
}

BF::Point BF::OBJLoader::ParsePointLine(std::string& line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);

    Point point(x, y);

    ss.Lines.DeleteAll();

    return point;
}

BF::List<BF::IndexPosition> BF::OBJLoader::ParseFaceLine(std::string& line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');
    List<IndexPosition> indexPositions;
    unsigned int dynamicIndex = 0;

    indexPositions.ReSize(3);

    for (unsigned int i = 1; i < 4; i++)
    {
        StringSplitter aa = StringSplitter::Split(ss.Lines[i], '/');
        std::string xValue, yValue, zValue;

        unsigned int x = -1;
        unsigned int y = -1;
        unsigned int z = -1;

        // Possiple error if char is '/'
        xValue = aa.Lines[0];
        yValue = aa.Lines[1];

        x = std::stoi(xValue);
        y = std::stoi(yValue);

        if (aa.Lines.Size.Value >= 3)
        {
            zValue = aa.Lines[2];
            z = std::stoi(zValue);
        }

        indexPositions[dynamicIndex++] = IndexPosition(x, y, z);

        aa.Lines.DeleteAll();
    }

    ss.Lines.DeleteAll();

    return indexPositions;
}

BF::OBJ* BF::OBJLoader::LoadFromFile(std::string filePath)
{
    StopWatch stopWatch;
    OBJ* waveFront = new OBJ();
    List<OBJLineCommand> commandList;

    stopWatch.Start();

    TextFile textFIle = FileLoader::ReadTextFile(filePath, true);
    unsigned int numberOfLines = textFIle.Lines.Size.Value;
    bool isFirstVertex = true;

    waveFront->Name = textFIle.FileName;

    printf("  Loading File : %lf\n", stopWatch.Reset());   

   commandList.ReSize(numberOfLines);

   // Translate to enum commands
   {
       bool usedFacesBefore = false;
       bool newMeshKey = false;

       waveFront->ElementList.Size.Value = 1; // We will have at least one mesh.

       for (unsigned int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
       {
           OBJLineCommand* currentCommand = &commandList[lineIndex];
           std::string* line = &textFIle.Lines[lineIndex];
           unsigned int functionChar = (*line).length() <= 0 ? _characterNone : (*line)[0];

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
                   break;

               case _characterVertex:
               {
                   functionChar = (*line)[1];

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
               waveFront->ElementList.Size.Value++;
           }
       }

       waveFront->ElementList.ReSize();
   }       

   printf("  Command lookup: %lf\n", stopWatch.Reset());

    // Space lookup
    {
       bool usedFacesBefore = false;
       bool newMeshKey = false;

        unsigned int elementIndex = 0;
        unsigned int materialsCounter = 0;

        OBJElement* elemtent = &waveFront->ElementList[elementIndex++];

        // How many data do i need?
        for (unsigned int i = 0; i < numberOfLines; i++)
        {
            switch (commandList[i])
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
                    elemtent->VertexPositionList.Size.Value++;
                    break;

                case OBJLineCommand::VertexTexture:
                    elemtent->TextureCoordinateList.Size.Value++;
                    break;

                case OBJLineCommand::VertexNormal:
                    elemtent->VertexNormalPositionList.Size.Value++;
                    break;

                case OBJLineCommand::VertexParameter:
                    elemtent->VertexParameterList.Size.Value++;
                    break;

                case OBJLineCommand::SmoothShading:
                    break;

                case OBJLineCommand::FaceElement:
                    elemtent->FaceElementList.Size.Value++;

                    usedFacesBefore = true;
                    break;
            }

            if (newMeshKey && (elementIndex <= waveFront->ElementList.Size.Value))
            {
                newMeshKey = false;

                elemtent->FaceElementList.Size.Value *= 3;

                elemtent->VertexPositionList.ReSize();
                elemtent->TextureCoordinateList.ReSize();
                elemtent->VertexNormalPositionList.ReSize();
                elemtent->VertexParameterList.ReSize();
                elemtent->FaceElementList.ReSize();


                elemtent = &waveFront->ElementList[elementIndex++];
            }
        }

        // Register Memory
        {
            elemtent->FaceElementList.Size.Value *= 3;

            elemtent->VertexPositionList.ReSize();
            elemtent->TextureCoordinateList.ReSize();
            elemtent->VertexNormalPositionList.ReSize();
            elemtent->VertexParameterList.ReSize();
            elemtent->FaceElementList.ReSize();

            waveFront->Materials.ReSize(materialsCounter);
        }    
    }

    printf("  Raw Parse     : %lf\n", stopWatch.Reset());

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
        OBJElement* elemtent = &waveFront->ElementList[elementIndex++];

        // Parse
        for (unsigned int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
        {
            std::string* line = &textFIle.Lines[lineIndex];

            switch (commandList[lineIndex])
            {
                case OBJLineCommand::Invalid:
                    break;

                case OBJLineCommand::None:
                    break;

                case OBJLineCommand::Comment:
                    break;

                case OBJLineCommand::MaterialLibraryInclude:
                {
                    try
                    {
                        StringSplitter ss = StringSplitter::Split(*line, ' ');
                        std::string mtlfilePath = ss.Lines[1];

                        // Merge File Path
                        {
                            int position = filePath.find_first_of("/");
                            bool hasSlash = position != -1;

                            if (hasSlash)
                            {
                                std::string rootFolder = filePath.substr(0, position);

                                mtlfilePath = rootFolder + "/" + mtlfilePath;
                            }
                        }

                        MTL* materialFile = MTLLoader::LoadFromFile(mtlfilePath);

                        waveFront->Materials[materialIndex++] = *materialFile;

                        //delete materialFile;
                    }
                    catch (const std::exception&)
                    {
                        MessageSystem::PushMessage(MessageType::Error, "Could not load File");
                    }    
                }
                break;

                case OBJLineCommand::MaterialLibraryUse:
                {
                    StringSplitter ss = StringSplitter::Split(*line, ' ');
                    std::string materialName = ss.Lines[1];
                    unsigned int materialID = -1;

                    for (unsigned int i = 0; i < waveFront->Materials.Size.Value; i++)
                    {
                        MTL* mtl = &waveFront->Materials[i];

                        for (unsigned int j = 0; j < mtl->MaterialList.Size.Value; j++)
                        {
                            Material* material = &mtl->MaterialList[j];

                            if (material->Name == materialName)
                            {
                                materialID = j;
                                j = 9999999;
                                i = 9999999;

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
                    elemtent->Name = (*line).substr(2);

                    if (usedFacesBefore)
                    {
                        usedFacesBefore = false;
                        newMeshKey = true;
                    }
                    break;

                case OBJLineCommand::VertexGeometric:
                    elemtent->VertexPositionList[currentPositionElement++] = ParsePositionLine(*line);
                    break;

                case OBJLineCommand::VertexTexture:
                    elemtent->TextureCoordinateList[currentTextureElement++] = ParsePointLine(*line);
                    break;

                case OBJLineCommand::VertexNormal:
                    elemtent->VertexNormalPositionList[currentNormalElement++] = ParsePositionLine(*line);
                    break;

                case OBJLineCommand::VertexParameter:
                    elemtent->VertexParameterList[currentParameterElement++] = ParsePositionLine(*line);
                    break;

                case OBJLineCommand::SmoothShading:
                    break;

                case OBJLineCommand::FaceElement:
                    List<IndexPosition> indexPosition = ParseFaceLine(*line);

                    for (unsigned int i = 0; i < indexPosition.Size.Value; i++)
                    {
                        elemtent->FaceElementList[currentFaceElement++] = indexPosition[i];
                    }

                    indexPosition.DeleteAll();

                    usedFacesBefore = true;

                    break;
            }

            if (newMeshKey) // && elementIndex < waveFront->ElementList.Size.Value
            {
                newMeshKey = false;

                elemtent = &waveFront->ElementList[elementIndex++];

                currentPositionElement = 0;
                currentTextureElement = 0;
                currentNormalElement = 0;
                currentParameterElement = 0;
                currentFaceElement = 0;
            }
        }
    }

    printf("  Exact Parse   : %lf\n", stopWatch.Reset());

    //PrintObjectDataToConsole(*waveFront);

    return waveFront;
}

void BF::OBJLoader::SaveToFile(std::string filePath, BF::OBJ& waveFont)
{

}

void BF::OBJLoader::PrintObjectDataToConsole(BF::OBJ& waveFont)
{
    printf("\n[=====================]\n");
    printf("  [Object: %s]\n", waveFont.Name.c_str());

    for (unsigned int i = 0; i < waveFont.ElementList.Size.Value; i++)
    {
        OBJElement* waveFrontElement = &waveFont.ElementList[i];

        unsigned int sizePos = waveFrontElement->VertexPositionList.Size.Value;
        unsigned int sizeNormal = waveFrontElement->VertexNormalPositionList.Size.Value;
        unsigned int sizeText = waveFrontElement->TextureCoordinateList.Size.Value;
        unsigned int sizePara = waveFrontElement->VertexParameterList.Size.Value;
        unsigned int sizeFace = waveFrontElement->FaceElementList.Size.Value;

        if (i + 1 >= waveFont.ElementList.Size.Value)
        {
            printf("  |-<Element %u : %4s>\n", i, waveFrontElement->Name.c_str());
            if (sizePos == 0)
            {
                printf("    |-<V   : %4s>\n", "---");
            }
            else
            {
                printf("    |-<V   : %4u>\n", sizePos);
            }

            if (sizeNormal == 0)
            {
                printf("    |-<VN  : %4s>\n", "---");
            }
            else
            {
                printf("    |-<VN  : %4u>\n", sizeNormal);
            }

            if (sizeText == 0)
            {
                printf("    |-<VT  : %4s>\n", "---");
            }
            else
            {
                printf("    |-<VT  : %4u>\n", sizeText);
            }

            if (sizePara == 0)
            {
                printf("    |-<VP  : %4s>\n", "---");
            }
            else
            {
                printf("    |-<VP : %4u>\n", sizePara);
            }

            if (sizeFace == 0)
            {
                printf("    |-<F   : %4s>\n", "---");
            }
            else
            {
                printf("    ^-<F   : %4u>\n", sizeFace);
            }

        }
        else
        {
            printf("  |-<Element %u : %4s>\n", i, waveFrontElement->Name.c_str());
            if (sizePos == 0)
            {
                printf("  | |-<V   : %4s>\n", "---");
            }
            else
            {
                printf("  | |-<V   : %4u>\n", sizePos);
            }

            if (sizeNormal == 0)
            {
                printf("  | |-< VN  : %4s>\n", "---");
            }
            else
            {
                printf("  | |-<VN  : %4u>\n", sizeNormal);
            }

            if (sizeText == 0)
            {
                printf("  | |-<VT  : %4s>\n", "---");
            }
            else
            {
                printf("  | |-<VT  : %4u>\n", sizeText);
            }

            if (sizePara == 0)
            {
                printf("  | |-<VP  : %4s>\n", "---");
            }
            else
            {
                printf("  | |-<VP : %4u>\n", sizePara);
            }

            if (sizeFace == 0)
            {
                printf("  | |-<F   : %4s>\n", "---");
            }
            else
            {
                printf("  | ^-<F   : %4u>\n", sizeFace);
            }
        }
    }

    printf("[---------------------]\n\n");

    for (unsigned int i = 0; i < waveFont.Materials.Size.Value; i++)
    {
        MTL* mtl = &waveFont.Materials[i];

        for (unsigned int j = 0; j < mtl->MaterialList.Size.Value; j++)
        {
            Material* material = &mtl->MaterialList[j];

            printf(" Material: %s\n", material->Name.c_str());
            printf(" - Ambient  [%4.4f|%4.4f|%4.4f]\n", material->Ambient.X, material->Ambient.Y, material->Ambient.Z);
            printf(" - Diffuse  [%4.4f|%4.4f|%4.4f]\n", material->Diffuse.X, material->Ambient.Y, material->Ambient.Z);
            printf(" - Specular [%4.4f|%4.4f|%4.4f]\n", material->Specular.X, material->Ambient.Y, material->Ambient.Z);
        }
    }

    printf("[=====================]\n\n");
}


















/*

WaveFront WaveFrontLoader::LoadFromFile(std::string filePath)
{
    WaveFront waveFront;
    TextFile textFIle = FileLoader::ReadTextFile(filePath);
    textFIle.SplitContentIntoLines();

    unsigned int numberOfLines = textFIle.AmountOfLines;

    WaveFrontLineCommand* commandList = new WaveFrontLineCommand[numberOfLines];

    // Loose Parese
    {
        unsigned int vertexPositionCounter = 0;
        unsigned int vertexTextureCounter = 0;
        unsigned int vertexNormalCounter = 0;
        unsigned int vertexParameterCounter = 0;
        unsigned int faceCounter = 0;
        WaveFrontLineCommand* currentCommand;
        std::string* line;
        char functionChar;

        for (unsigned int i = 0; i < numberOfLines; i++)
        {
            currentCommand = &commandList[i];
            line = &textFIle.Lines[i];

            functionChar = (*line)[0];

            //char functionChar = line.length() <= 0 ? _characterNone : line.at(0);

            // Parse Command
            switch (functionChar)
            {
            case _characterComment:
            {
                *currentCommand = WaveFrontLineCommand::Comment;
                break;
            }


            case _characterObjectName:
            {
                *currentCommand = WaveFrontLineCommand::ObjectName;
                break;
            }


            case _characterSmoothShading:
            {
                *currentCommand = WaveFrontLineCommand::SmoothShading;
                break;
            }


            case _characterFace:
            {
                *currentCommand = WaveFrontLineCommand::Face;
                faceCounter++;
                break;
            }

            case _characterVertex:
            {
                functionChar = (*line)[1];

                switch (functionChar)
                {
                case _characterNone:
                {
                    *currentCommand = WaveFrontLineCommand::VertexGeometric;
                    vertexPositionCounter++;
                    break;
                }


                case _characterVertexTexture:
                {
                    *currentCommand = WaveFrontLineCommand::VertexTexture;
                    vertexTextureCounter++;
                    break;
                }


                case _characterVertexNormal:
                {
                    *currentCommand = WaveFrontLineCommand::VertexNormal;
                    vertexNormalCounter++;
                    break;
                }

                case _characterParameter:
                {
                    *currentCommand = WaveFrontLineCommand::VertexParameter;
                    vertexParameterCounter++;
                    break;
                }

                default:
                {
                    *currentCommand = WaveFrontLineCommand::Invalid;
                    break;
                }
                }

                break;
            }

            default:
            {
                *currentCommand = WaveFrontLineCommand::None;
                break;
            }

            }
        }

        // Reserve
        waveFront.VectorPositions.reserve(vertexPositionCounter);
        waveFront.VectorNormalPositions.reserve(vertexNormalCounter);
        waveFront.TextureCoordinates.reserve(vertexTextureCounter);
        waveFront.VectorParameter.reserve(vertexParameterCounter);
        waveFront.FaceElements.reserve(faceCounter);
    }

    // Fill Data
    for (unsigned int i = 0; i < textFIle.AmountOfLines; i++)
    {
        std::string line = textFIle.Lines[i];

        switch (commandList[i])
        {

        case WaveFrontLineCommand::VertexGeometric:
        {
            waveFront.VectorPositions.push_back(ParsePositionLine(line));
            break;
        }

        case WaveFrontLineCommand::VertexTexture:
        {
            waveFront.TextureCoordinates.push_back(ParsePointLine(line));
            break;
        }

        case WaveFrontLineCommand::VertexNormal:
        {
            waveFront.VectorNormalPositions.push_back(ParsePositionLine(line));
            break;
        }

        case WaveFrontLineCommand::VertexParameter:
        {
            waveFront.VectorParameter.push_back(ParsePositionLine(line));
            break;
        }

        case WaveFrontLineCommand::Face:
        {
            std::vector<IndexPosition> indexPosition = ParseFaceLine(line);

            for (size_t i = 0; i < indexPosition.size(); i++)
            {
                waveFront.FaceElements.push_back(indexPosition.at(i));
            }

            break;
        }

        case WaveFrontLineCommand::ObjectName:
        {
            waveFront.Name = line.substr(2);
            break;
        }

        default:
        {
            // Do nothing
            break;
        }

        }
    }

    delete[] commandList;

    PrintObjectDataToConsole(waveFront);

    return waveFront;
}
*/