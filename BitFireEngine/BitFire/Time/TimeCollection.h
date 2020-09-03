#pragma once

#include <chrono>

class TimeCollection
{
private:
    static std::chrono::steady_clock::time_point _lastTimeStamp;

public:
	static double ActiveTime;
	static float DeltaTime;

    static void SetDeltaTimeStamp()
    {
        std::chrono::steady_clock::time_point currentTimeStamp = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currentTimeStamp - _lastTimeStamp;
       
        DeltaTime = elapsed.count();

        _lastTimeStamp = currentTimeStamp;
    }
};