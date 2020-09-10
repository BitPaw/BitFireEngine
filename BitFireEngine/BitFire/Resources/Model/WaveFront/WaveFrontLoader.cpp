#include "WaveFrontLoader.h"
#include "../../../IO/Message/MessagerSystem.h"

Position BF::WaveFrontLoader::ParsePositionLine(std::string& line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);
    float z = std::stof(ss.Lines[3]);

    Position position(x, y, z);

    delete[] ss.Lines;

    return position;
}

Point BF::WaveFrontLoader::ParsePointLine(std::string& line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);

    Point point(x, y);

    delete[] ss.Lines;

    return point;
}

std::vector<IndexPosition> BF::WaveFrontLoader::ParseFaceLine(std::string& line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');
    std::vector<IndexPosition> indexPositions;

    indexPositions.reserve(3);

    std::string xValue, yValue, zValue;

    for (size_t i = 1; i < 4; i++)
    {
        StringSplitter aa = StringSplitter::Split(ss.Lines[i], '/');

        unsigned int x = -1;
        unsigned int y = -1;
        unsigned int z = -1;

        // Possiple error if char is '/'
        xValue = aa.Lines[0];
        yValue = aa.Lines[1];
      

        x = std::stoi(xValue);
        y = std::stoi(yValue);

        if (aa.NumberOfLines >= 3)
        {
            zValue = aa.Lines[2];
            z = std::stoi(zValue);
        }  

        IndexPosition indexPosition(x, y, z);

        indexPositions.push_back(indexPosition);

        delete[] aa.Lines;
    }

    delete[] ss.Lines;

    return indexPositions;
}

BF::WaveFront BF::WaveFrontLoader::LoadFromFile(std::string filePath)
{
    StopWatch stopWatch;
    WaveFront waveFront = WaveFront();

    stopWatch.Start();

    TextFile textFIle = FileLoader::ReadTextFile(filePath, true);
        
    printf("  Loading File   : %lf\n", stopWatch.Reset());
    
    unsigned int numberOfLines = textFIle.Lines.Size.Value;
    bool isFirstVertex = true;

    waveFront.Name = textFIle.FileName;
       

    printf("  Splitting File : %lf\n", stopWatch.Reset());
    

    List<WaveFrontLineCommand> commandList(numberOfLines);
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

                    waveFront.ElementList.Size.Value++;

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

    waveFront.ElementList.ReSize();

    printf("  command lookup: %lf\n", stopWatch.Reset());


    // II
    {       
    unsigned int elementIndex = 0;     
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
                // Register Memory
                elemtent->FaceElementList.Size.Value *= 3;

                elemtent->VertexPositionList.ReSize();
                elemtent->TextureCoordinateList.ReSize();
                elemtent->VertexNormalPositionList.ReSize();
                elemtent->VertexParameterList.ReSize();
                elemtent->FaceElementList.ReSize();
            }

            elemtent = &waveFront.ElementList[elementIndex++];

        case WaveFrontLineCommand::VertexGeometric:
            elemtent->VertexPositionList.Size.Value++;
            break;

        case WaveFrontLineCommand::VertexTexture:
            elemtent->TextureCoordinateList.Size.Value++;
            break;

        case WaveFrontLineCommand::VertexNormal:
            elemtent->VertexNormalPositionList.Size.Value++;
            break;

        case WaveFrontLineCommand::VertexParameter:
            elemtent->VertexParameterList.Size.Value++;
            break;

        case WaveFrontLineCommand::SmoothShading:
            break;

        case WaveFrontLineCommand::FaceElement:
            elemtent->FaceElementList.Size.Value++;
            break;
        }       
    }


    // Register Memory
    elemtent->FaceElementList.Size.Value *= 3;

    elemtent->VertexPositionList.ReSize();
    elemtent->TextureCoordinateList.ReSize();
    elemtent->VertexNormalPositionList.ReSize();
    elemtent->VertexParameterList.ReSize();
    elemtent->FaceElementList.ReSize();

    }

    printf("  Raw Parse     : %lf\n", stopWatch.Reset());

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
                elemtent->Name = (*line).substr(2);

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


    printf("  Exact Parse   : %lf\n", stopWatch.Reset());

    PrintObjectDataToConsole(waveFront);

    return waveFront;
}

void BF::WaveFrontLoader::SaveToFile(std::string filePath, WaveFront& waveFont)
{

}

void BF::WaveFrontLoader::PrintObjectDataToConsole(WaveFront& waveFont)
{
    printf("\n[=====================]\n");
    printf("  [Object: %s]\n", waveFont.Name.c_str());

    for (unsigned int i = 0; i < waveFont.ElementList.Size.Value; i++)
    {
        WaveFrontElement* waveFrontElement = &waveFont.ElementList[i];

        unsigned int sizePos = waveFrontElement->VertexPositionList.Size.Value;
        unsigned int sizeNormal = waveFrontElement->VertexNormalPositionList.Size.Value;
        unsigned int sizeText = waveFrontElement->TextureCoordinateList.Size.Value;
        unsigned int sizePara = waveFrontElement->VertexParameterList.Size.Value;
        unsigned int sizeFace = waveFrontElement->FaceElementList.Size.Value;

        if (i+1 >= waveFont.ElementList.Size.Value)
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