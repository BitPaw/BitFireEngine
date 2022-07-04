#pragma once

#include <stddef.h>

namespace BF
{
	enum class TimeDayOfWeek
	{
		Invalid,

		Monday,
		Tuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday,
		Sunday
	};

	enum class TimeMonth
	{
		Invalid,

		January,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December
	};

	struct Time
	{
		unsigned short Year;
		TimeMonth Month;
		TimeDayOfWeek DayOfWeek;
		unsigned short Day;
		unsigned short Hour;
		unsigned short Minute;
		unsigned short Second;
		unsigned short Milliseconds;

		Time();

		static void Now(Time& time);
		static size_t MillisecondsDelta(const Time& timeA, const Time& timeB);
	};
}
