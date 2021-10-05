#pragma once

#define PitchMaximum 2.9
#define PitchMinimum 0.2

namespace BF
{
	struct AudioSource
	{
		public:
		unsigned int ID;		
		float Pitch; // [0.5 - 2.0]
		float Volume;
		float Position[3];
		float Velocity[3];
		bool Looping;

		AudioSource();

		void PitchIncrease(float amount);
		void PitchReduce(float amount);
	};
}