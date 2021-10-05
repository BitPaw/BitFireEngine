#include "AudioSource.h"
#include <cassert>

BF::AudioSource::AudioSource()
{
	ID = 0;
	Pitch = 0.4;
	Volume = 0.02;
	Position[0] = 0;
	Position[1] = 0;
	Position[2] = 0;
	Velocity[0] = 0;
	Velocity[1] = 0;
	Velocity[2] = 0;
	Looping = true;
}

void BF::AudioSource::PitchIncrease(float amount)
{
	assert(amount > 0.0f);

	Pitch += amount;

	if (Pitch > PitchMaximum)
	{
		Pitch = PitchMaximum;
	}
}

void BF::AudioSource::PitchReduce(float amount)
{
	assert(amount > 0.0f);

	Pitch -= amount;

	if (Pitch < PitchMinimum)
	{
		Pitch = PitchMinimum;
	}
}
