#pragma once

#include "OBJ.h"
#include "OBJElement.h"
#include "OBJLineCommand.h"

#include "MTL/MTL.h"
#include "MTL/MTLLoader.h"

#include "../../../Utility/List.hpp"

#include "../../../Mathematic/Geometry/Point.hpp"
#include "../../../Mathematic/Geometry/Position.hpp"

#include "../../../IO/Log/Log.h"
#include "../../../Mathematic/Geometry/Position.hpp"
#include "../../../IO/File/TextFile.h"
#include "../../../IO/File/FileLoader.h"
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
     
        public:
        static OBJ* LoadFromFile(ASCIIString filePath);
        static void SaveToFile(ASCIIString filePath, OBJ& waveFont);
        static void PrintObjectDataToConsole(OBJ& waveFont);
    };
}