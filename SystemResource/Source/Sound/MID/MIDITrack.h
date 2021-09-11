#pragma once

namespace BF
{
	struct MIDITrack
	{
		public:
		unsigned int ID;
		char* EventData;
		unsigned int EventDataSize;

		MIDITrack();
	};
}