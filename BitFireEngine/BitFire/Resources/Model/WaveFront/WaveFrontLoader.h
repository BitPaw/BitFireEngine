#pragma once

#include <string>
#include <vector>

#include "WaveFront.h"
#include "WaveFrontLineCommand.h"

#include "../../../Mathematic/Geometry/Position.h"
#include "../../../IO/TrippelIndex.h"
#include "../../../IO/File/TextFile.h"
#include "../../../IO/File/FileLoader.h"
#include "../../../Utility/StringSplitter.h"
#include "../../../Time/StopWatch.h"

namespace BF
{
    class WaveFrontLoader
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
        static std::vector<IndexPosition> ParseFaceLine(std::string& line);

    public:
        static WaveFront LoadFromFile(std::string filePath);
        static void SaveToFile(std::string filePath, WaveFront& waveFont);
        static void PrintObjectDataToConsole(WaveFront& waveFont);
    };
}