#pragma once

#include <chrono>

#if defined(_WIN32)
#define TimeSpampType std::chrono::steady_clock::time_point
#endif

#if defined(__linux__)
#define TimeSpampType std::chrono::_V2::system_clock::time_point  
#endif

class StopWatch
{
private: 
	TimeSpampType _lastTimeStamp = std::chrono::high_resolution_clock::now();;

	double Duration;
	
	unsigned int TimeStampListSizeCurrent;
	unsigned int TimeStampListSizeMaximal;
	double* TimeStampList;

	double CalulateDeltaTimeTime();

public:
	StopWatch();
	StopWatch(const unsigned int amountOfTimeStamps);

	~StopWatch();

	void Start();
	double Stop();
	double TimeStamp();
	double Reset();
};