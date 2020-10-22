#pragma once

#include "StopWatch.h"

namespace BF
{
    class TimeCollection
    {
    private:
        static StopWatch _stopWatch;

    public:
        static double ActiveTime;
        static float DeltaTime;

        static void SetDeltaTimeStamp()
        {
            DeltaTime = _stopWatch.Reset();
        }
    };
}