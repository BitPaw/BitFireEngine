#include "MP3Header.h"

BF::MP3Header::MP3Header()
{
	MPEGVersion = MP3MPEGVersion::Reserved;
	Layer = MP3Layer::Reserved;
	CRCErrorProtection = false;
	BitRate = 0;
	Frequency = 0;
	PaddingBit = false;
	PrivateBit = false; 
	ChannelMode = MP3ChannelMode::Stereo;
	AudioModeIntensity = false;
	AudioModeMS = false;
	Copyrighted = false;
	CopyOfOriginal = false;
	Emphasis = MP3Emphasis::None;
}

void BF::MP3Header::ExtractRawHeader(const char rawHeader[4])
{
	bool validSyncWordPart1 = rawHeader[0] == '\xFF';
	bool validSyncWordPart2 = (rawHeader[1] & 0b11100000) == 0b11100000;
	bool validHeader = validSyncWordPart1 && validSyncWordPart2;
	unsigned char mpegAudioVersionID = (rawHeader[1] & 0b00011000) >> 3;
	unsigned char layerID = (rawHeader[1] & 0b00000110) >> 1;

	if (!validHeader)
	{
		return;
	}

	CRCErrorProtection = (rawHeader[1] & 0b00000001);

	BitRate = (rawHeader[2] & 0b11110000) >> 4;
	Frequency = (rawHeader[2] & 0b00001100) >> 2;
	PaddingBit = (rawHeader[2] & 0b00000010) >> 1;
	PrivateBit = (rawHeader[2] & 0b00000001);

	unsigned char channalMode = (rawHeader[3] & 0b11000000) >> 6;
	AudioModeIntensity = (rawHeader[3] & 0b00100000) >> 5;
	AudioModeMS = (rawHeader[3] & 0b00010000) >> 4;

	Copyrighted = (rawHeader[3] & 0b00000100) >> 3;
	CopyOfOriginal = (rawHeader[3] & 0b00000100) >> 2;
	unsigned char emphasis = (rawHeader[3] & 0b00000011);

	switch (mpegAudioVersionID)
	{
		default:
		case 0b00: 
			MPEGVersion = MP3MPEGVersion::MPEGVersion25;
			break;

		case 0b01:
			MPEGVersion = MP3MPEGVersion::Reserved;
			break;

		case 0b10:
			MPEGVersion = MP3MPEGVersion::MPEGVersion2;
			break;

		case 0b11:
			MPEGVersion = MP3MPEGVersion::MPEGVersion1;
			break;
	}

	switch (layerID)
	{
		default:
		case 0b00: 
			Layer = MP3Layer::Reserved;
			break;

		case 0b01:
			Layer = MP3Layer::LayerIII;
			break;

		case 0b10:
			Layer = MP3Layer::LayerII;
			break;

		case 0b11:
			Layer = MP3Layer::LayerI;
			break;	
	}

	switch (channalMode)
	{
		default:
		case 0b00:
			ChannelMode = MP3ChannelMode::Stereo;
			break;

		case 0b01:
			ChannelMode = MP3ChannelMode::JointStereo;
			break;

		case 0b10:
			ChannelMode = MP3ChannelMode::DualChannel;
			break;

		case 0b11:
			ChannelMode = MP3ChannelMode::SingleChannel;
			break;
	}
	
	switch (emphasis)
	{
		default:
		case 0b00:
			Emphasis = MP3Emphasis::None;
			break;

		case 0b01:
			Emphasis = MP3Emphasis::ms5015;
			break;

		case 0b10:
			Emphasis = MP3Emphasis::Reserved;
			break;

		case 0b11:
			Emphasis = MP3Emphasis::CCITJ17;
			break;
	}
}