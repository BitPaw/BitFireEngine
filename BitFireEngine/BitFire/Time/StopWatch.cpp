#include "StopWatch.h"

StopWatch::StopWatch() : StopWatch(0)
{

}

StopWatch::StopWatch(const unsigned int amountOfTimeStamps)
{
	TimeStampListSizeCurrent = 0;
	TimeStampListSizeMaximal = amountOfTimeStamps;

	if (amountOfTimeStamps == 0)
	{
		TimeStampList = nullptr;
	}
	else
	{	
		TimeStampList = new double[amountOfTimeStamps];
	}
}

StopWatch::~StopWatch()
{
	delete[] TimeStampList;
}

double StopWatch::CalulateDeltaTimeTime()
{
	const std::chrono::steady_clock::time_point current = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsed = current - _lastTimeStamp;

	return elapsed.count();
}

void StopWatch::Start()
{
	_lastTimeStamp = std::chrono::high_resolution_clock::now();
}

double StopWatch::Stop()
{
	Duration = CalulateDeltaTimeTime();

	return Duration;
}

double StopWatch::TimeStamp()
{
	return 0;
}

double StopWatch::Reset()
{
	double value = CalulateDeltaTimeTime();

	_lastTimeStamp = std::chrono::high_resolution_clock::now();

	return value;
}