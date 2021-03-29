#pragma once

#include "Sound.h"
#include "ISound.h"
#include "SoundFormat.h"

#include "MID/MID.h"
#include "MP3/MP3.h"
#include "OGG/OGG.h"
#include "WAV/WAV.h"

#include "../../Utility/ASCIIString.h"

namespace BF
{
	class SoundLoader
	{
		public:
		Sound* LoadFromFile(AsciiString& filePath);
	};
}