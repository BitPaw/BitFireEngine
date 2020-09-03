#pragma once

#include <chrono>

class StopWatch
{
private: 
	std::chrono::steady_clock::time_point _lastTimeStamp;

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