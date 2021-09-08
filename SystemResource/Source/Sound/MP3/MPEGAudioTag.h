#pragma once

#include "MPEGGenre.hpp"

namespace BF
{
	struct MPEGAudioTag
	{
		// char[3] == TAG
		char Title[30];
		char Artist[30];
		char Album[30];
		char Year[4];
		char Comment[30];
		MPEGGenre Genre;
	};
}