#include "MP3.h"

#include "MP3Header.h"
#include "MPEGAudioTag.h"

#include "../../File/File.h"
#include "../../Container/ByteStreamHusk.h"

BF::FileActionResult BF::MP3::Load(const char* filePath)
{
	File file(filePath);
	MP3Header mp3Header;
	MPEGAudioTag mpegAudioTag;

	file.ReadFromDisk();
	ByteStreamHusk byteStreamHusk(file.Data, file.DataSize);

	char rawHeader[4];

	byteStreamHusk.CopyBytesAndMove(rawHeader, 4);

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




	bool validInfoHeader = byteStreamHusk.CompareBytesAndMove((void*)"TAG", 3u);

	byteStreamHusk.CopyBytesAndMove((unsigned char*)&mpegAudioTag, 124u);
	
	unsigned char gere = byteStreamHusk.ExtractByteAndMove();

	mpegAudioTag.Genre = MPEGGenreConvert(gere);


	return FileActionResult::Successful;
}

BF::FileActionResult BF::MP3::Save(const char* filePath)
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