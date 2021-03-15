#pragma once

#include <functional>

#include "GameTickData.h"

#include "../Event/DataEvent.hpp"

namespace BF
{
    class GameTickEvent : public DataEvent<std::function<void(GameTickData)>, GameTickData>
    {       

    };
}