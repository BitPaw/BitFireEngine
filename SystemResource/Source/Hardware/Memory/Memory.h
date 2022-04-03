#pragma once

#include <cstddef>

#include "MemoryUsage.h"

namespace BF
{
    class Memory
    {
        public:
        static bool Scan(MemoryUsage& memoryUsage);
    };
}