#pragma once

#include <stddef.h>

#include "MP3Layer.hpp"
#include "MP3MPEGVersion.hpp"
#include "MP3ChannelMode.hpp"
#include "MP3Emphasis.hpp"

namespace BF
{
	struct MP3Header
	{
		public:
		MP3MPEGVersion MPEGVersion;
		MP3Layer Layer;
		bool CRCErrorProtection;

		unsigned int BitRate;
		unsigned short SampleRate;
		bool UsePadding;
		bool IsPrivate; // Unused
		MP3ChannelMode ChannelMode;
		bool AudioModeIntensity;
		bool AudioModeMS;

		bool Copyrighted;
		bool CopyOfOriginal;
		MP3Emphasis Emphasis;

		unsigned int FrameLength;

		MP3Header();

		size_t Parse(const unsigned char* data, const size_t dataSize);
	};
}
