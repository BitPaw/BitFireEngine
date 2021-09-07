#include "AudioSource.h"

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
