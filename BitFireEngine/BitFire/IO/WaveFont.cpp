#include "WaveFont.h"

Position WaveFont::ParsePositionLine(std::string line)
{
    SplittedString ss = SplittedString::Split(line,' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);
    float z = std::stof(ss.Lines[3]);

    Position position(x, y, z);

    return position;
}

Point WaveFont::ParsePointLine(std::string line)
{
    SplittedString ss = SplittedString::Split(line, ' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);

    Point point(x, y);

    return point;
}

void WaveFont::ParseIndicesAndMerge(std::string line, Position* list, unsigned int* index)
{
    SplittedString ss = SplittedString::Split(line, ' ');

    std::string xValue, yValue, zValue;

    for (size_t i = 1; i < 4; i++)
    {
        SplittedString aa = SplittedString::Split(ss.Lines[i], '/');

        // Possiple error if char is /

        xValue = aa.Lines[0];
        yValue = aa.Lines[1];
        zValue = aa.Lines[2];

        float x = std::stof(xValue);
        float y = std::stof(yValue);
        float z = std::stof(zValue);
                
        Position* position = &list[(*index)++];

        position->X = x;
        position->Y = y;
        position->Z = z;
    }
}

RenderObject* WaveFont::LoadFromFile(std::string filePath)
{

    enum LineCommand
    {
        Invalid,
        Comment,
        ObjectName,
        VertexGeometric,
        VertexTexture,
        VertexNormal,
        VertexParameter,
        StartIndice,
        Face,
    };


    unsigned int numberOfLines = 0;
    std::string* lines = FileLoader::ReadFileByLines(filePath, &numberOfLines);

    RenderObject* renderObject;
    enum LineCommand* commandList = new LineCommand[numberOfLines];

    unsigned int vertexCounter = 0;
    Position* positionList;

    unsigned int vertexTexture = 0;
    Point* textureCoordinates;

    unsigned int vertexNormal = 0;
    Position* vertexNormalList;

    unsigned int faceCounter = 0;
    Position* indexList;   


    unsigned int indiceListLengh;
    unsigned int* indiceList;


    unsigned int startIndice = 0;

    // Loose Parese
    for (unsigned int i = 0; i < numberOfLines; i++)
    {
        enum LineCommand currentCommand;
        std::string line = lines[i];
        char functionChar = line.length() <= 0 ? ' ' : line.at(0);

        // Parse Command
        switch (functionChar)
        {
        case '#':
            currentCommand = Comment;
            break;

        case 'o':
            currentCommand = ObjectName;
            break;

        case 's':
            currentCommand = StartIndice;
            break;

        case 'f':
            currentCommand = Face;
            break;

        case 'v':
            functionChar = lines[i].at(1);

            switch (functionChar)
            {
            case ' ':
                currentCommand = VertexGeometric;
                break;

            case 't':
                currentCommand = VertexTexture;
                break;

            case 'n':
                currentCommand = VertexNormal;
                break;

            case 'p':
                currentCommand = VertexParameter;
                break;

            default:
                currentCommand = Invalid;
                break;
            }

            break;

        default:
            currentCommand = Invalid;
            break;
        }

        // Count Command
        switch (currentCommand)
        {
        case VertexGeometric:
            vertexCounter++;
            break;

        case VertexTexture:
            vertexTexture++;
            break;

        case VertexNormal:
            vertexNormal++;
            break;

        case VertexParameter:
            //VertexParameter++;
            break;

        case Face:
            faceCounter++;
            break;

        default:
            // Do nothing
            break;
        }

        // SaveCommand
        commandList[i] = currentCommand;
    }

    // Create Space
    indiceListLengh = faceCounter * 3;

    positionList = new Position[vertexCounter];
    textureCoordinates = new Point[vertexTexture];
    vertexNormalList = new Position[vertexNormal];
    indiceList = new unsigned int[indiceListLengh];
    indexList = new Position[indiceListLengh];

    Vertex* vertexes = new Vertex[vertexCounter];

    // Reset
    vertexCounter = 0;
    vertexTexture = 0;
    vertexNormal = 0;
    faceCounter = 0;

    std::string name = "[N/A]";

    // Fill Data
    for (unsigned int i = 0; i < numberOfLines; i++)
    {
        switch (commandList[i])
        {
        case VertexGeometric:
            positionList[vertexCounter++] = ParsePositionLine(lines[i]);
            break;

        case VertexTexture:
            textureCoordinates[vertexTexture++] = ParsePointLine(lines[i]);
            break;

        case VertexNormal:      
            vertexNormalList[vertexNormal++] = ParsePositionLine(lines[i]);
            break;

        case VertexParameter:
            // To do
            break;

        case Face:
            ParseIndicesAndMerge(lines[i], indexList, &faceCounter);
            break;

        case ObjectName:
            name = lines[i].substr(2);
            break;

        default:
            // Do nothing
            break;
        }
    }

 
    const char* objname = name.c_str();

    for (size_t i = 0; i < indiceListLengh; i++)
    {
        indiceList[i] = indexList[i].X;
    }



    // Set Data
    {
        Vertex* vertex;
        Position* indexPosition;
        unsigned int positionID;
        unsigned int normalID;
        unsigned int colorID;

        for (size_t i = 0; i < vertexCounter; i++)
        {
            vertex = &vertexes[i];
            //indexPosition = &indexList[i];
            //positionID = indexPosition->X;
            //normalID = indexPosition->Y;
            //colorID = indexPosition->Z;

            //indiceList[i] = positionList[positionID].X;

            vertex->CurrentPosition = &positionList[i];
            vertex->NormalizedPosition = &vertexNormalList[i];
            vertex->Color = &textureCoordinates[i];
        }
    }
   
    Mesh* mesh = new Mesh(vertexes, vertexCounter, indiceList, faceCounter, 3);

    renderObject = new RenderObject(objname, mesh);

    //renderObject = nullptr;
    
    return renderObject;
}
