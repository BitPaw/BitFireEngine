#pragma once

#include <chrono>

#include <OS/OSVersion.h>

#if defined(OSUnix)
#define TimeSpanType std::chrono::_V2::system_clock::time_point  
#elif defined(OSWindows)
#define TimeSpanType std::chrono::steady_clock::time_point
#endif 

namespace BF
{
	class StopWatch
	{
		private:
		TimeSpanType _lastTimeStamp;

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
}