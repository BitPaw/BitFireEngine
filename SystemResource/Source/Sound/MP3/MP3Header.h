#pragma once

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

		unsigned char BitRate;
		unsigned char Frequency;
		bool PaddingBit;
		bool PrivateBit; // Unused
		MP3ChannelMode ChannelMode;
		bool AudioModeIntensity;
		bool AudioModeMS;

		bool Copyrighted;
		bool CopyOfOriginal;
		MP3Emphasis Emphasis;

		MP3Header();

		void ExtractRawHeader(const char rawHeader[4]);
	};
}
