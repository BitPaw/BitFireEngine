#pragma once

namespace BF
{
	struct AudioSource
	{
		public:
		unsigned int ID;
		// [0.5 - 2.0]
		float Pitch;
		float Volume;
		float Position[3];
		float Velocity[3];
		bool Looping;

		AudioSource();
	};
}