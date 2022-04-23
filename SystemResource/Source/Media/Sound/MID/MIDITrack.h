#pragma once

namespace BF
{
	struct MIDITrack
	{
		public:
		unsigned int ID;
		unsigned char* EventData;
		unsigned int EventDataSize;

		MIDITrack();
		~MIDITrack();
	};
}