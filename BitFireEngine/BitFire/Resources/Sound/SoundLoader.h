#pragma once

#include <string>

#include "Sound.h"
#include "ISound.h"
#include "SoundFormat.h"

#include "MID/MIDLoader.h"
#include "MP3/MP3Loader.h"
#include "OGG/OGGLoader.h"
#include "WAV/WAVLoader.h"

#include "../../IO/File/TextFile.h"
#include "../../IO/Message/MessageSystem.h"

namespace BF
{
	class SoundLoader
	{
		public:
		ISound* LoadFromFile(std::string filePath);

		Sound* MIDToSound(MID* midi);
		Sound* MP3ToSound(MP3* mp3);
		Sound* OGGToSound(OGG* ogg);
		Sound* WAVToSound(WAV* wave);

		MID* SoundToMID(Sound* sound);
		MP3* SoundToMP3(Sound* sound);
		OGG* SoundToOGG(Sound* sound);
		WAV* SoundToWav(Sound* sound);
	};
}