#pragma once

namespace BF
{
	struct AudioSource
	{
		public:
		unsigned int ID;
		float Pitch;
		float Volume;
		float Position[3];
		float Velocity[3];
		bool Looping;

		AudioSource();
	};
}