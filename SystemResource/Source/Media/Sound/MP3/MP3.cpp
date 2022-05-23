#include "MP3.h"

#include "MP3Header.h"
#include "MPEGAudioTag.h"

#include <File/File.h>

#include <cstddef>
#include <cstring>

BF::FileActionResult BF::MP3::Load(const wchar_t* filePath)
{
	File file;

	{
		const FileActionResult loadingResult = file.ReadFromDisk(filePath);

		if(loadingResult != FileActionResult::Successful)
		{
			return loadingResult;
		}
	}	

	MP3Header mp3Header;
	MPEGAudioTag mpegAudioTag;

	char rawHeader[4];

	file.Read(rawHeader, 4);

	mp3Header.ExtractRawHeader(rawHeader);


	unsigned int frameLengthInBytes;

	switch (mp3Header.Layer)
	{
		case MP3Layer::LayerI:
			//frameLengthInBytes = (12 * mp3Header.BitRate / mp3Header.SampleRate + mp3Header.Padding) * 4;
			break;

		case MP3Layer::LayerII:
		case MP3Layer::LayerIII:
			//frameLengthInBytes = 144 * mp3Header.BitRate / mp3Header.SampleRate + mp3Header.Padding;
			break;

		default:
			// Error
			break;
	}


	char tagBuffer[3];
	unsigned char gere;
	bool validInfoHeader = false;

	file.Read(tagBuffer, 3);

	validInfoHeader = memcmp(tagBuffer, "TAG", 3) == 0;

	file.Read(&mpegAudioTag, 124u);
	file.Read(gere);	

	mpegAudioTag.Genre = MPEGGenreConvert(gere);

	
	return FileActionResult::Successful;
}

BF::FileActionResult BF::MP3::Save(const wchar_t* filePath)
{
	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::MP3::ConvertTo(Sound& sound)
{
	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::MP3::ConvertFrom(Sound& sound)
{
	return BF::FileActionResult::Successful;
}