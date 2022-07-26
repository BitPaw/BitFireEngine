#include "Time.h"

#include <OS/OSVersion.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <Windows.h>
#endif

TimeDayOfWeek ConvertToMonth(unsigned short monthID)
{
	switch(monthID)
	{
		case 1u: return MonthJanuary; 
		case 2u: return MonthFebruary; 
		case 3u: return MonthMarch; 
		case 4u: return MonthApril; 
		case 5u: return MonthMarch; 
		case 6u: return MonthJune; 
		case 7u: return MonthJuly; 
		case 8u: return MonthAugust; 
		case 9u: return MonthSeptember; 
		case 10u: return MonthOctober; 
		case 11u: return MonthNovember; 
		case 12u: return MonthDecember; 
		default: return MonthInvalid; 
	}
}

TimeMonth ConvertToDay(unsigned short dayID)
{
	switch(dayID)
	{
		case 1u: return DayMonday; 
		case 2u: return DayTuesday; 
		case 3u: return DayWednesday; 
		case 4u: return DayThursday; 
		case 5u: return DayFriday; 
		case 6u: return DaySaturday; 
		case 0u: return DaySunday; 
		default: return DayInvalid; 
	}
}

void TimeNow(Time* time)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	SYSTEMTIME systemTime;

	//GetSystemTime(&st);
	GetLocalTime(&systemTime);

	time->Year = systemTime.wYear;
	time->Month = systemTime.wMonth;
	time->DayOfWeek = systemTime.wDayOfWeek;
	time->Day = systemTime.wDay;
	time->Hour = systemTime.wHour;
	time->Minute = systemTime.wMinute;
	time->Second = systemTime.wSecond;
	time->Milliseconds = systemTime.wMilliseconds;
#endif
}

size_t TimeMillisecondsDelta(const Time* timeA, const Time* timeB)
{
	//Year = -1;
//Month = Month::Invalid;
//DayOfWeek = DayOfWeek::Invalid;;

	const size_t dayDelta = (timeB->Day - timeA->Day);
	const size_t hourDelta = (timeB->Hour - timeA->Hour) * (dayDelta * 24);
	const size_t minuteDelta = (timeB->Minute - timeA->Minute) * (hourDelta * 60);
	const size_t secondsDelta = (timeB->Second - timeA->Second) + (minuteDelta * 60);
	const size_t millisecondsDelta = (timeB->Milliseconds - timeA->Milliseconds) + (secondsDelta * 1000);

	return millisecondsDelta;
}