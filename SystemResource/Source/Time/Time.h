#pragma once

namespace BF
{
	enum class DayOfWeek
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

	enum class Month
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
		Month Month;
		DayOfWeek DayOfWeek;
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