#include "GameTickData.h"
#include "../Mathematic/Math.h"

BF::GameTickData::GameTickData()
{
	for (unsigned int i = 0; i < _deltaTimeValues; i++)
	{
		DeltaTime[_deltaTimeIndex] = 0;
	}

	ActiveTime = 0;

	FramesPerSecound = 0;
	FramesRendered = 0; 
	LastTimeCheck = 0;
}

void BF::GameTickData::CalcualteFramesPerSecounds(double time)
{
	_deltaTimeIndex = (_deltaTimeIndex + 1) % _deltaTimeValues;

	DeltaTime[_deltaTimeIndex] = time;
}

float BF::GameTickData::GetSmoothDeltaTime()
{
	double value = 0;

	for (size_t i = 0; i < _deltaTimeValues; i++)
	{
		value += DeltaTime[i];
	}

	return value / _deltaTimeValues;
}
