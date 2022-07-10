#include "MP3Header.h"

BF::MP3Header::MP3Header()
{
	MPEGVersion = MP3MPEGVersion::Reserved;
	Layer = MP3Layer::Reserved;
	CRCErrorProtection = false;
	BitRate = 0;
	SampleRate = 0;
	UsePadding = false;
	IsPrivate = false; 
	ChannelMode = MP3ChannelMode::Stereo;
	AudioModeIntensity = false;
	AudioModeMS = false;
	Copyrighted = false;
	CopyOfOriginal = false;
	Emphasis = MP3Emphasis::None;
}

size_t BF::MP3Header::Parse(const unsigned char* data, const size_t dataSize)
{		
	// Parse First Byte__
	{
		const unsigned short byteA = data[0];
		const unsigned short byteB = data[1];
		const unsigned short signature = (byteA << 8) + byteB;
		const unsigned int filterMask = 0b1111111111100000;
		const bool validSignature = (signature & filterMask) == filterMask;

		if(!validSignature)
		{
			return 0;
		}
	}

	// Parse secound Byte__
	{
		const unsigned char byteB = data[1];

		const unsigned char mpegAudioVersionID = (byteB & 0b00011000) >> 3;
		const unsigned char layerID = (byteB & 0b00000110) >> 1;

		CRCErrorProtection = (byteB & 0b00000001);

		switch(mpegAudioVersionID)
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

		switch(layerID)
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
	}

	// Parse third Byte__
	{
		const unsigned char byteC = data[2];
		const bool isMPEGVersion1 = MPEGVersion == MP3MPEGVersion::MPEGVersion1;
		const bool isMPEGVersion2 = MPEGVersion == MP3MPEGVersion::MPEGVersion2;
		const bool isMPEGVersion25 = MPEGVersion == MP3MPEGVersion::MPEGVersion25;

		// Bit lookup
		{
			const unsigned char bitRateTag = (byteC & 0b11110000) >> 4;

			const unsigned char bad = 0x00;
			const unsigned short bitRateKBpsLookup[16][5]
			{
				{bad, 	bad, 	bad ,	bad ,	bad},
				{  32, 	32, 	32 ,	32 ,	8},
				{  64, 	48, 	40 ,	48 ,	16},
				{  96, 	56, 	48 ,	56 ,	24},
				{ 128, 	64, 	56 ,	64 ,	32},
				{ 160, 	80, 	64 ,	80 ,	48},
				{ 192, 	96, 	80 ,	96 ,	48},
				{ 224, 	112, 	96 ,	112 ,	56},
				{ 256, 	128, 	112 ,	128 ,	64 },
				{ 288, 	160, 	128 ,	144 ,	80 },
				{ 320, 	192, 	160 ,	160 ,	96 },
				{ 352, 	224, 	192 ,	176 ,	112 },
				{ 384, 	256, 	224 ,	192 ,	128 },
				{ 416, 	320, 	256 ,	224 ,	144 },
				{ 448, 	384, 	320 ,	256 ,	160 },
				{ bad, 	bad, 	bad ,	bad ,	bad }
			};

			const bool isLayer1 = Layer == MP3Layer::LayerI;
			const bool isLayer2 = Layer == MP3Layer::LayerII;
			const bool isLayer3 = Layer == MP3Layer::LayerIII;			

			unsigned char yPos = bitRateTag;
			unsigned char xPos =
				0 * (isMPEGVersion1 && isLayer1) +
				1 * (isMPEGVersion1 && isLayer2) +
				2 * (isMPEGVersion1 && isLayer3) +
				3 * (isMPEGVersion2 && isLayer1) +
				4 * ((isMPEGVersion2 || isMPEGVersion25) && (isLayer2 || isLayer3));

			const unsigned short bitRateKBps = bitRateKBpsLookup[yPos][xPos];

			BitRate = (unsigned int)bitRateKBps * 1000;
		}

		//For Layer II there are some combinations of bitrate and mode which are not allowed.

		{
			const unsigned char sampleRateID = (byteC & 0b00001100) >> 2;

			const unsigned short reserverdValue = -1;
			const unsigned short sampleRateLookup[4][3]
			{
				{	44100, 22050, 11025 },
				{	48000, 24000, 12000 },
				{	32000, 16000, 8000 },
				{	reserverdValue,	reserverdValue,	reserverdValue }
			};

			unsigned char yPos = sampleRateID;
			unsigned char xPos =
				0 * isMPEGVersion1 +
				1 * isMPEGVersion2 + 
				2 * isMPEGVersion25;


			const unsigned short sampleRateKBps = sampleRateLookup[yPos][xPos];

			SampleRate = sampleRateKBps;
		}

		UsePadding = (byteC & 0b00000010) >> 1;
		IsPrivate = (byteC & 0b00000001);
	}

	// Parse forth Byte__
	{
		const unsigned char byteD = data[3];

		const unsigned char channalMode	= (byteD & 0b11000000) >> 6;
		AudioModeIntensity				= (byteD & 0b00100000) >> 5;
		AudioModeMS						= (byteD & 0b00010000) >> 4;
		Copyrighted						= (byteD & 0b00001000) >> 3;
		CopyOfOriginal					= (byteD & 0b00000100) >> 2;
		const unsigned char emphasis	= (byteD & 0b00000011);

		switch(channalMode)
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

		switch(emphasis)
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

	const float bitratePerSample = BitRate / ((float)SampleRate + UsePadding);
		 
	switch(Layer)
	{
		case MP3Layer::LayerI:
		{
			FrameLength = ((12 * bitratePerSample) * 4) - 4;
			break;
		}
		case MP3Layer::LayerII:
		case MP3Layer::LayerIII:
		{
			FrameLength = (144 * bitratePerSample) -4 + UsePadding;
			break;
		}
		case MP3Layer::Reserved:
		default:
		{
			FrameLength = 0;
			break;
		}		
	}

	return 4u;
}