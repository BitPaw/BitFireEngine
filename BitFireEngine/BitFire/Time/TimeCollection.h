#pragma once

#include <chrono>

#include "StopWatch.h"

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