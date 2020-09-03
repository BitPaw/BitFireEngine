#include "WaveFont.h"

Vertex WaveFont::ParseVertexLine(std::string line)
{
    SplittedString ss = SplittedString::Split(line,' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);
    float z = std::stof(ss.Lines[3]);

    Vertex vertex(x, y, z);

    return vertex;
}

Point WaveFont::ParsePointLine(std::string line)
{
    SplittedString ss = SplittedString::Split(line, ' ');

    float x = std::stof(ss.Lines[1]);
    float y = std::stof(ss.Lines[2]);

    Point point(x, y);

    return point;
}

void WaveFont::ParseIndicesAndMerge(std::string line, unsigned int* arrayIndex, unsigned int* index)
{
    SplittedString ss = SplittedString::Split(line, ' ');

    for (size_t i = 1; i < 4; i++)
    {
        SplittedString aa = SplittedString::Split(ss.Lines[i], '/');

        float x = std::stof(aa.Lines[0]);
        float y = std::stof(aa.Lines[1]);
        float z = std::stof(aa.Lines[2]);

        arrayIndex[(*index)++] = x;
        arrayIndex[(*index)++] = y;
        arrayIndex[(*index)++] = z;
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
    Vertex* vertexList;

    unsigned int vertexTexture = 0;
    Point* textureCoordinates;

    unsigned int vertexNormal = 0;
    Vertex* vertexNormalList;

    unsigned int* indiceList;
    unsigned int indiceCounter = 0;

    unsigned int startIndice = 0;

    // Loose Parese
    for (unsigned int i = 0; i < numberOfLines; i++)
    {
        enum LineCommand currentCommand;
        char functionChar = lines[i].at(0);

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
            indiceCounter++;
            break;

        default:
            // Do nothing
            break;
        }

        // SaveCommand
        commandList[i] = currentCommand;
    }

    // Create Space
    vertexList = new Vertex[vertexCounter];
    textureCoordinates = new Point[vertexTexture];
    vertexNormalList = new Vertex[vertexNormal];
    indiceList = new unsigned int[indiceCounter * 3 * 3];

    // Reset
    vertexCounter = 0;
    vertexTexture = 0;
    vertexNormal = 0;
    indiceCounter = 0;

    std::string name = "[N/A]";

    // Fill Data
    for (unsigned int i = 0; i < numberOfLines; i++)
    {
        switch (commandList[i])
        {
        case VertexGeometric:
            vertexList[vertexCounter++] = ParseVertexLine(lines[i]);
            break;

        case VertexTexture:
            textureCoordinates[vertexTexture++] = ParsePointLine(lines[i]);
            break;

        case VertexNormal:
            vertexNormalList[vertexNormal++] = ParseVertexLine(lines[i]);
            break;

        case VertexParameter:
            // To do
            break;

        case Face:
            ParseIndicesAndMerge(lines[i], indiceList, &indiceCounter);
            break;

        case ObjectName:
            break;

        default:
            // Do nothing
            break;
        }
    }

    const char* objname = name.c_str();
    Mesh* mesh = new Mesh(vertexList, vertexCounter, indiceList, indiceCounter);

   renderObject = new RenderObject(objname, mesh);

    //renderObject = nullptr;
    
    return renderObject;
}
