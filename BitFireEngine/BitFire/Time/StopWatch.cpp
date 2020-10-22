#include "StopWatch.h"

BF::StopWatch::StopWatch() : StopWatch(0)
{

}

BF::StopWatch::StopWatch(const unsigned int amountOfTimeStamps)
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

BF::StopWatch::~StopWatch()
{
	delete[] TimeStampList;
}

double BF::StopWatch::CalulateDeltaTimeTime()
{
	const TimeSpampType current = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsed = current - _lastTimeStamp;

	return elapsed.count();
}

void BF::StopWatch::Start()
{
	_lastTimeStamp = std::chrono::high_resolution_clock::now();
}

double BF::StopWatch::Stop()
{
	Duration = CalulateDeltaTimeTime();

	return Duration;
}

double BF::StopWatch::TimeStamp()
{
	return 0;
}

double BF::StopWatch::Reset()
{
	double value = CalulateDeltaTimeTime();

	_lastTimeStamp = std::chrono::high_resolution_clock::now();

	return value;
}