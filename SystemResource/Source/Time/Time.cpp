#include "Time.h"

#include <OS/OSDefine.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <Windows.h>
#endif

BF::Time::Time()
{
	Year = -1;
	Month = TimeMonth::Invalid;
	DayOfWeek = TimeDayOfWeek::Invalid;;
	Day = -1;
	Hour = -1;
	Minute = -1;
	Second = -1;
	Milliseconds = -1;
}

void BF::Time::Now(Time& time)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	SYSTEMTIME systemTime{0};

	//GetSystemTime(&st);
	GetLocalTime(&systemTime);

	time.Year = systemTime.wYear;

	switch(systemTime.wMonth)
	{
		case 1u: time.Month = TimeMonth::January; break;
		case 2u: time.Month = TimeMonth::February; break;
		case 3u: time.Month = TimeMonth::March; break;
		case 4u: time.Month = TimeMonth::April; break;
		case 5u: time.Month = TimeMonth::March; break;
		case 6u: time.Month = TimeMonth::June; break;
		case 7u: time.Month = TimeMonth::July; break;
		case 8u: time.Month = TimeMonth::August; break;
		case 9u: time.Month = TimeMonth::September; break;
		case 10u: time.Month = TimeMonth::October; break;
		case 11u: time.Month = TimeMonth::November; break;
		case 12u: time.Month = TimeMonth::December; break;
		default: time.Month = TimeMonth::Invalid; break;
	}

	switch(systemTime.wDayOfWeek)
	{
		case 1u: time.DayOfWeek = TimeDayOfWeek::Monday; break;
		case 2u: time.DayOfWeek = TimeDayOfWeek::Tuesday; break;
		case 3u: time.DayOfWeek = TimeDayOfWeek::Wednesday; break;
		case 4u: time.DayOfWeek = TimeDayOfWeek::Thursday; break;
		case 5u: time.DayOfWeek = TimeDayOfWeek::Friday; break;
		case 6u: time.DayOfWeek = TimeDayOfWeek::Saturday; break;
		case 0u: time.DayOfWeek = TimeDayOfWeek::Sunday; break;
		default: time.DayOfWeek = TimeDayOfWeek::Invalid; break;
	}

	time.Day = systemTime.wDay;
	time.Hour = systemTime.wHour;
	time.Minute = systemTime.wMinute;
	time.Second = systemTime.wSecond;
	time.Milliseconds = systemTime.wMilliseconds;
#endif
}

size_t BF::Time::MillisecondsDelta(const Time& timeA, const Time& timeB)
{
	//Year = -1;
//Month = Month::Invalid;
//DayOfWeek = DayOfWeek::Invalid;;

	const size_t dayDelta = (timeB.Day - timeA.Day);
	const size_t hourDelta = (timeB.Hour - timeA.Hour) * (dayDelta * 24);
	const size_t minuteDelta = (timeB.Minute - timeA.Minute) * (hourDelta * 60);
	const size_t secondsDelta = (timeB.Second - timeA.Second) + (minuteDelta * 60);
	const size_t millisecondsDelta = (timeB.Milliseconds - timeA.Milliseconds) + (secondsDelta * 1000);

	return millisecondsDelta;
}
