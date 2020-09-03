#include "WaveFrontLoader.h"

Position WaveFrontLoader::ParsePositionLine(std::string line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);
    float z = std::stof(ss.Lines[3]);

    Position position(x, y, z);

    return position;
}

Point WaveFrontLoader::ParsePointLine(std::string line)
{
    StringSplitter ss = StringSplitter::Split(line, ' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);

    Point point(x, y);

    return point;
}

std::vector<IndexPosition> WaveFrontLoader::ParseFaceLine(std::string line)
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
    }

    return indexPositions;
}

WaveFront WaveFrontLoader::LoadFromFile(std::string filePath)
{
    WaveFront waveFront;
    TextFile textFIle = FileLoader::ReadTextFile(filePath);
    textFIle.SplitContentIntoLines();
    std::vector<WaveFrontLineCommand> commandList;
  
    // Loose Parese
    {
        unsigned int vertexPositionCounter = 0;
        unsigned int vertexTextureCounter = 0;
        unsigned int vertexNormalCounter = 0;
        unsigned int vertexParameterCounter = 0;
        unsigned int faceCounter = 0;

        const char characterComment = '#';
        const char characterObjectName = 'o';
        const char characterSmoothShading = 's';
        const char characterFace = 'f';
        const char characterNone = ' ';
        const char characterVertex = 'v';
        const char characterVertexTexture = 't';
        const char characterVertexNormal = 'n';
        const char characterParameter = 'p';

        for (unsigned int i = 0; i < textFIle.AmountOfLines; i++)
        {
            WaveFrontLineCommand currentCommand;
            std::string line = textFIle.Lines.at(i);
            char functionChar = line.length() <= 0 ? characterNone : line.at(0);

            // Parse Command
            switch (functionChar)
            {
            case characterComment:
                currentCommand = WaveFrontLineCommand::Comment;
                break;

            case characterObjectName:
                currentCommand = WaveFrontLineCommand::ObjectName;
                break;

            case characterSmoothShading:
                currentCommand = WaveFrontLineCommand::SmoothShading;
                break;

            case characterFace:
                currentCommand = WaveFrontLineCommand::Face;
                faceCounter++;
                break;

            case characterVertex:
                functionChar = line.at(1);

                switch (functionChar)
                {
                case characterNone:
                    currentCommand = WaveFrontLineCommand::VertexGeometric;
                    vertexPositionCounter++;
                    break;

                case characterVertexTexture:
                    currentCommand = WaveFrontLineCommand::VertexTexture;
                    vertexTextureCounter++;
                    break;

                case characterVertexNormal:
                    currentCommand = WaveFrontLineCommand::VertexNormal;
                    vertexNormalCounter++;
                    break;

                case characterParameter:
                    currentCommand = WaveFrontLineCommand::VertexParameter;
                    vertexParameterCounter++;
                    break;

                default:
                    currentCommand = WaveFrontLineCommand::Invalid;
                    break;
                }

                break;

            default:
                currentCommand = WaveFrontLineCommand::None;
                break;
            }

            // SaveCommand
            commandList.push_back(currentCommand);
        }

        // Create Space
        waveFront.VectorPositions.reserve(vertexPositionCounter);
        waveFront.VectorNormalPositions.reserve(vertexNormalCounter);
        waveFront.TextureCoordinates.reserve(vertexTextureCounter);
        waveFront.VectorParameter.reserve(vertexParameterCounter);
        waveFront.FaceElements.reserve(faceCounter);
    }

    // Fill Data
    for (unsigned int i = 0; i < textFIle.AmountOfLines; i++)
    {
        std::string line = textFIle.Lines.at(i);
        WaveFrontLineCommand command = commandList.at(i);

        switch (command)
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

    return waveFront;
}

void WaveFrontLoader::SaveToFile(std::string filePath, WaveFront& waveFont)
{

}

void WaveFrontLoader::PrintObjectDataToConsole(WaveFront& waveFont)
{
    printf("[Analysis: complete!]\n");
    printf(" V  : %u\n", waveFont.VectorPositions.size());
    printf(" VN : %u\n", waveFont.VectorNormalPositions.size());
    printf(" VT : %u\n", waveFont.TextureCoordinates.size());
    printf(" VP : %u\n", waveFont.VectorParameter.size());
    printf(" F  : %u\n", waveFont.FaceElements.size());
    printf("[===================]\n");
}