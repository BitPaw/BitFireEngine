#ifndef TimeInclude
#define TimeInclude

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif	

	typedef enum TimeDayOfWeek_
	{
		DayInvalid,
		DayMonday,
		DayTuesday,
		DayWednesday,
		DayThursday,
		DayFriday,
		DaySaturday,
		DaySunday
	}
	TimeDayOfWeek;

	typedef enum TimeMonth_
	{
		MonthInvalid,
		MonthJanuary,
		MonthFebruary,
		MonthMarch,
		MonthApril,
		MonthMay,
		MonthJune,
		MonthJuly,
		MonthAugust,
		MonthSeptember,
		MonthOctober,
		MonthNovember,
		MonthDecember
	}
	TimeMonth;


	typedef struct Time_
	{
		unsigned short Year;
		unsigned short Month;
		unsigned char DayOfWeek;
		unsigned char Day;
		unsigned short Hour;
		unsigned short Minute;
		unsigned short Second;
		unsigned short Milliseconds;
	}
	Time;

	extern TimeDayOfWeek ConvertToMonth(unsigned short monthID);
	extern TimeMonth ConvertToDay(unsigned short dayID);

	extern void TimeNow(Time* time);
	extern size_t TimeMillisecondsDelta(const Time* timeA, const Time* timeB);

#ifdef __cplusplus
}
#endif

#endif