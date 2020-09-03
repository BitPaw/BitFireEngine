#include "WaveFrontLoader.h"

Position WaveFrontLoader::ParsePositionLine(std::string& line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);
    float z = std::stof(ss.Lines[3]);

    Position position(x, y, z);

    delete[] ss.Lines;

    return position;
}

Point WaveFrontLoader::ParsePointLine(std::string& line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);

    Point point(x, y);

    delete[] ss.Lines;

    return point;
}

std::vector<IndexPosition> WaveFrontLoader::ParseFaceLine(std::string& line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');
    std::vector<IndexPosition> indexPositions;

    indexPositions.reserve(3);

    std::string xValue, yValue, zValue;

    for (size_t i = 1; i < 4; i++)
    {
        StringSplitter aa = StringSplitter::Split(ss.Lines[i], '/');

        // Possiple error if char is '/'
        xValue = aa.Lines[0];
        yValue = aa.Lines[1];
        zValue = aa.Lines[2];

        unsigned int x = std::stoi(xValue);
        unsigned int y = std::stoi(yValue);
        unsigned int z = std::stoi(zValue);

        IndexPosition indexPosition(x, y, z);

        indexPositions.push_back(indexPosition);

        delete[] aa.Lines;
    }

    delete[] ss.Lines;

    return indexPositions;
}

WaveFront WaveFrontLoader::LoadFromFile(std::string filePath)
{
    WaveFront waveFront = WaveFront();
    TextFile textFIle = FileLoader::ReadTextFile(filePath);
    textFIle.SplitContentIntoLines();
    
    unsigned int numberOfLines = textFIle.AmountOfLines;
    bool isFirstVertex = true;

    WaveFrontLineCommand* commandList = new WaveFrontLineCommand[numberOfLines]{ WaveFrontLineCommand::Invalid };
    WaveFrontLineCommand* currentCommand;
    std::string* line;
    unsigned int functionChar;

    // Get commands & How many sub-objects do i have?
    for (unsigned int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
    {
        currentCommand = &commandList[lineIndex];
        line = &textFIle.Lines[lineIndex];
        //functionChar = (*line)[0];

        functionChar = (*line).length() <= 0 ? _characterNone : (*line)[0];

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
            isFirstVertex = true;

            *currentCommand = WaveFrontLineCommand::FaceElement;
            break;
        }

        case _characterVertex:
        {
            functionChar = (*line)[1];

            switch (functionChar)
            {
            case _characterNone:
            {
                if (isFirstVertex)
                {
                    isFirstVertex = false;

                    waveFront.ElementListSize++;

                    *currentCommand = WaveFrontLineCommand::VertexGeometricFirst;
                }
                else
                {
                    *currentCommand = WaveFrontLineCommand::VertexGeometric;
                }

                
                break;
            }


            case _characterVertexTexture:
            {
                *currentCommand = WaveFrontLineCommand::VertexTexture;
                break;
            }


            case _characterVertexNormal:
            {
                *currentCommand = WaveFrontLineCommand::VertexNormal;
                break;
            }

            case _characterParameter:
            {
                *currentCommand = WaveFrontLineCommand::VertexParameter;
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

    // II
    {

    unsigned int elementIndex = 0;    
    waveFront.ElementList = new WaveFrontElement[waveFront.ElementListSize];
    WaveFrontElement* elemtent = nullptr;

    // How many data do i need?
    for (unsigned int i = 0; i < numberOfLines; i++)
    {

        switch (commandList[i])
        {
        case WaveFrontLineCommand::Invalid:
            break;

        case WaveFrontLineCommand::None:
            break;

        case WaveFrontLineCommand::Comment:
            break;

        case WaveFrontLineCommand::MaterialLibraryInclude:
            break;

        case WaveFrontLineCommand::MaterialLibraryUse:
            break;

        case WaveFrontLineCommand::ObjectName:
            break;

        case  WaveFrontLineCommand::VertexGeometricFirst:

            if (elementIndex > 0)
            {
                elemtent->FaceElementListSize *= 3;
                elemtent->Allocate();
            }

            elemtent = &waveFront.ElementList[elementIndex++];

        case WaveFrontLineCommand::VertexGeometric:
            elemtent->VertexPositonListSize++;
            break;

        case WaveFrontLineCommand::VertexTexture:
            elemtent->TextureCoordinateListSize++;
            break;

        case WaveFrontLineCommand::VertexNormal:
            elemtent->VertexNormalPositionListSize++;
            break;

        case WaveFrontLineCommand::VertexParameter:
            elemtent->VertexParameterListSize++;
            break;

        case WaveFrontLineCommand::SmoothShading:
            break;

        case WaveFrontLineCommand::FaceElement:
            elemtent->FaceElementListSize++;
            break;
        }       
    }

    elemtent->FaceElementListSize *= 3;
    elemtent->Allocate();

    }

    // III
    {      
        unsigned int elementIndex = 0;
        unsigned int currentPositionElement = 0;
        unsigned int currentTextureElement = 0;
        unsigned int currentNormalElement = 0;
        unsigned int currentParameterElement = 0;
        unsigned int currentFaceElement = 0;
        WaveFrontElement* elemtent = &waveFront.ElementList[elementIndex];

        // Parse
        for (unsigned int lineIndex = 0; lineIndex < numberOfLines; lineIndex++)
        {
            line = &textFIle.Lines[lineIndex];

            switch (commandList[lineIndex])
            {
            case WaveFrontLineCommand::Invalid:
                break;

            case WaveFrontLineCommand::None:
                break;

            case WaveFrontLineCommand::Comment:
                break;

            case WaveFrontLineCommand::MaterialLibraryInclude:
                break;

            case WaveFrontLineCommand::MaterialLibraryUse:
                break;

            case WaveFrontLineCommand::ObjectName:
            {
                std::string name = (*line).substr(2);                             
                unsigned int lengh = name.length();

                elemtent->Name = new char[lengh + 1];

                for (unsigned int i = 0; i < lengh; i++)
                {
                    elemtent->Name[i] = name[i];
                }

                elemtent->Name[lengh] = '\0';

                break;
            }               

            case  WaveFrontLineCommand::VertexGeometricFirst:
                elemtent = &waveFront.ElementList[elementIndex++];

                currentPositionElement = 0;
                currentTextureElement = 0;
                currentNormalElement = 0;
                currentParameterElement = 0;
                currentFaceElement = 0;

                // No breake, jump below!

            case WaveFrontLineCommand::VertexGeometric:
                elemtent->VertexPositionList[currentPositionElement++] = ParsePositionLine(*line);
                break;

            case WaveFrontLineCommand::VertexTexture:
                elemtent->TextureCoordinateList[currentTextureElement++] = ParsePointLine(*line);
                break;

            case WaveFrontLineCommand::VertexNormal:
                elemtent->VertexNormalPositionList[currentNormalElement++] = ParsePositionLine(*line);
                break;

            case WaveFrontLineCommand::VertexParameter:
                elemtent->VertexParameterList[currentParameterElement++] = ParsePositionLine(*line);
                break;

            case WaveFrontLineCommand::SmoothShading:
                break;

            case WaveFrontLineCommand::FaceElement:
                std::vector<IndexPosition> indexPosition = ParseFaceLine(*line);

                for (unsigned int i = 0; i < indexPosition.size(); i++)
                {
                    elemtent->FaceElementList[currentFaceElement++] = indexPosition.at(i);
                }
                break;
            }
        }
    }

    delete[] commandList;

    PrintObjectDataToConsole(waveFront);

    return waveFront;
}

void WaveFrontLoader::SaveToFile(std::string filePath, WaveFront& waveFont)
{

}

void WaveFrontLoader::PrintObjectDataToConsole(WaveFront& waveFont)
{
    printf("\n[=====================]\n");
    printf("  [Object: %s]\n", waveFont.Name);

    for (unsigned int i = 0; i < waveFont.ElementListSize; i++)
    {
        WaveFrontElement* waveFrontElement = &waveFont.ElementList[i];

        unsigned int sizePos = waveFrontElement->VertexPositonListSize;
        unsigned int sizeNormal = waveFrontElement->VertexNormalPositionListSize;
        unsigned int sizeText = waveFrontElement->TextureCoordinateListSize;
        unsigned int sizePara = waveFrontElement->VertexParameterListSize;
        unsigned int sizeFace = waveFrontElement->FaceElementListSize;


        if (i+1 >= waveFont.ElementListSize)
        {
            printf("  |-<Element %u : %4s>\n", i, waveFrontElement->Name);
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
                printf("    |-< VN  : %4s>\n", "---");
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
            printf("  |-<Element %u : %4s>\n", i, waveFrontElement->Name);
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