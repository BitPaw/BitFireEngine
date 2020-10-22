#pragma once

#include <string>

#include "OBJ.h"
#include "OBJElement.h"
#include "OBJLineCommand.h"

#include "../../../IO/Message/MessageSystem.h"
#include "../../../Mathematic/Geometry/Position.h"
#include "../../../IO/TrippelIndex.h"
#include "../../../IO/File/TextFile.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Utility/StringSplitter.h"
#include "../../../Time/StopWatch.h"

namespace BF
{
    class OBJLoader
    {
    private:
        static const char _characterComment = '#';
        static const char _characterObjectName = 'o';
        static const char _characterSmoothShading = 's';
        static const char _characterFace = 'f';
        static const char _characterNone = ' ';
        static const char _characterVertex = 'v';
        static const char _characterVertexTexture = 't';
        static const char _characterVertexNormal = 'n';
        static const char _characterParameter = 'p';

        static Position ParsePositionLine(std::string& line);
        static Point ParsePointLine(std::string& line);
        static List<IndexPosition> ParseFaceLine(std::string& line);

    public:
        static OBJ* LoadFromFile(std::string filePath);
        static void SaveToFile(std::string filePath, OBJ& waveFont);
        static void PrintObjectDataToConsole(OBJ& waveFont);
    };
}