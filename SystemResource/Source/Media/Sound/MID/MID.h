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

		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}