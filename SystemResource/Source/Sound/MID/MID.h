#pragma once

#include "../Sound.h"
#include "MIDITrack.h"

namespace BF
{
	struct MID 
	{
		unsigned short Format;
		unsigned short MusicSpeed;
		unsigned int TrackListSize;
		MIDITrack* TrackList;

		public:
		void Load(const char* filePath);
		void Save(const char* filePath);
		void ConvertTo(Sound& sound);
		void ConvertFrom(Sound& sound);
	};
}