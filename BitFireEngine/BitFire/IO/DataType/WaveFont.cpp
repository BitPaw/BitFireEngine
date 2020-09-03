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

void WaveFont::ParseIndicesAndMerge(std::string line, TrippelIndex* indexList, unsigned int* index)
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
                
        TrippelIndex* indexObject = &indexList[(*index)++];

        indexObject->A = x;
        indexObject->B = y;
        indexObject->C = z;
    }
}

RenderObject* WaveFont::LoadFromFile(std::string filePath)
{
    enum class LineCommand
    {
        None,
        Invalid,
        Comment,
        ObjectName,
        VertexGeometric,
        VertexTexture,
        VertexNormal,
        VertexParameter,
        SmoothShading,
        Face,
    };

    RenderObject* renderObject;
    unsigned int numberOfLines = 0;
    std::string* lines = FileLoader::ReadFileByLines(filePath, &numberOfLines);   
    LineCommand* commandList = new LineCommand[numberOfLines];

    unsigned int vertexCounter = 0;
    Position* positionList;

    unsigned int vertexTexture = 0;
    Point* textureCoordinates;

    unsigned int vertexNormal = 0;
    Position* vertexNormalList;

    unsigned int faceCounter = 0;
    TrippelIndex* indexList;   

    unsigned int indiceListLengh;
    unsigned int* indiceList;

    unsigned int startIndice = 0;


    const char characterComment = '#';
    const char characterObjectName = 'o';
    const char characterSmoothShading = 's';
    const char characterFace = 'f';

    const char characterNone = ' ';
    const char characterVertex = 'v';
    const char characterVertexTexture = 't';
    const char characterVertexNormal = 'n';
    const char characterParameter = 'p';

    // Loose Parese
    for (unsigned int i = 0; i < numberOfLines; i++)
    {
        enum LineCommand currentCommand;
        std::string line = lines[i];
        char functionChar = line.length() <= 0 ? characterNone : line.at(0);

        // Parse Command
        switch (functionChar)
        {
        case characterComment:
            currentCommand = LineCommand::Comment;
            break;

        case characterObjectName:
            currentCommand = LineCommand::ObjectName;
            break;

        case characterSmoothShading:
            currentCommand = LineCommand::SmoothShading;
            break;

        case characterFace:
            currentCommand = LineCommand::Face;
            faceCounter++;
            break;

        case characterVertex:
            functionChar = lines[i].at(1);

            switch (functionChar)
            {
            case characterNone:
                currentCommand = LineCommand::VertexGeometric;
                vertexCounter++;
                break;

            case characterVertexTexture:
                currentCommand = LineCommand::VertexTexture;
                vertexTexture++;
                break;

            case characterVertexNormal:
                currentCommand = LineCommand::VertexNormal;
                vertexNormal++;
                break;

            case characterParameter:
                currentCommand = LineCommand::VertexParameter;
                //VertexParameter++;
                break;

            default:
                currentCommand = LineCommand::Invalid;
                break;
            }

            break;

        default:
            currentCommand = LineCommand::None;
            break;
        }

        // SaveCommand
        commandList[i] = currentCommand;
    }

    printf("[Analysis: complete!]\n");
    printf(" V  : %u\n", vertexCounter);
    printf(" VT : %u\n", vertexTexture);
    printf(" VN : %u\n", vertexNormal);
    printf(" F  : %u\n", faceCounter);
    printf("[===================]\n");

    // Create Space
    indiceListLengh = faceCounter * 3;

    positionList = new Position[vertexCounter];
    textureCoordinates = new Point[vertexTexture];
    vertexNormalList = new Position[vertexNormal];
    indiceList = new unsigned int[indiceListLengh];
    indexList = new TrippelIndex[indiceListLengh];

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
        case LineCommand::VertexGeometric:
            positionList[vertexCounter++] = ParsePositionLine(lines[i]);
            break;

        case LineCommand::VertexTexture:
            textureCoordinates[vertexTexture++] = ParsePointLine(lines[i]);
            break;

        case LineCommand::VertexNormal:
            vertexNormalList[vertexNormal++] = ParsePositionLine(lines[i]);
            break;

        case LineCommand::VertexParameter:
            // To do
            break;

        case LineCommand::Face:
            ParseIndicesAndMerge(lines[i], indexList, &faceCounter);
            break;

        case LineCommand::ObjectName:
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
        indiceList[i] = (indexList[i].A) -1;

        //printf("ID %u : %u\n",i,  indiceList[i]);
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
            vertex->NormalizedPosition = &vertexNormalList[(indexList[i].C - 1)];
            vertex->TexturePoint = &textureCoordinates[(indexList[i].B - 1)];
        }
    }
   
    Mesh* mesh = new Mesh(vertexes, vertexCounter, indiceList, faceCounter, 3);

    renderObject = new RenderObject(objname, mesh);

    //renderObject = nullptr;
    
    return renderObject;
}
