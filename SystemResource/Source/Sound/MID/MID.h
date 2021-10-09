#pragma once

#include "MIDITrack.h"
#include "../ISoundFormat.hpp"

namespace BF
{
	struct MID : public ISoundFormat
	{
		public:
		unsigned short Format;
		unsigned short MusicSpeed;
		unsigned int TrackListSize;
		MIDITrack* TrackList;

		MID();
		~MID();

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}