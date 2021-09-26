#include "WAV.h"
#include "../../File/File.h"
#include "../../Container/ByteStreamHusk.h"
#include "RIFF.h"
#include "FMT.h"

BF::WAV::WAV()
{
	AudioFormat = 0;
	NumerOfChannels = 0;
	SampleRate = 0;
	ByteRate = 0;
	BlockAllign = 0;
	BitsPerSample = 0;

	SoundDataSize = 0;
	SoundData = nullptr;
}

BF::WAV::~WAV()
{
	free(SoundData);
}

void BF::WAV::Load(const char* filePath)
{
	File file(filePath);
	file.ReadFromDisk();
	ByteStreamHusk byteSteam(file.Data, file.DataSize);

	RIFF riffChunk;
	FMT fmtChunk;
	Endian endian;	

	byteSteam.CopyBytesAndMove(riffChunk.ChunkID, 4);

	bool useBigEndian = memcmp("RIFX", riffChunk.ChunkID, 4) == 0;
	bool useLittleEndian = memcmp("RIFF", riffChunk.ChunkID, 4) == 0;
	bool isValidEndian = useLittleEndian != useBigEndian;

	if (!isValidEndian)
	{
		return;
	}

	if (useLittleEndian)
	{
		endian = Endian::Little;
	}

	if (useBigEndian)
	{
		endian = Endian::Big;
	}

	riffChunk.ChunkSize = byteSteam.ExtractIntegerAndMove(endian);
	byteSteam.CopyBytesAndMove(riffChunk.Format, 4);

	byteSteam.CopyBytesAndMove(fmtChunk.ChunkID, 4);
	fmtChunk.ChunkSize = byteSteam.ExtractIntegerAndMove(endian);
	fmtChunk.AudioFormat = byteSteam.ExtractShortAndMove(endian);
	fmtChunk.NumerOfChannels = byteSteam.ExtractShortAndMove(endian);
	fmtChunk.SampleRate = byteSteam.ExtractIntegerAndMove(endian);
	fmtChunk.ByteRate = byteSteam.ExtractIntegerAndMove(endian);
	fmtChunk.BlockAllign = byteSteam.ExtractShortAndMove(endian);
	fmtChunk.BitsPerSample = byteSteam.ExtractShortAndMove(endian);

	char dataText[4];

	byteSteam.CopyBytesAndMove(dataText, 4);

	bool isRIFFListChunk = memcmp("LIST", dataText, 4) == 0;

	if (isRIFFListChunk)
	{
		byteSteam.CurrentPosition  += 30u;
	}

	byteSteam.CopyBytesAndMove(dataText, 4);
	unsigned int wavChunkSize = byteSteam.ExtractIntegerAndMove(endian);

	AudioFormat = fmtChunk.AudioFormat;
	NumerOfChannels = fmtChunk.NumerOfChannels;
	SampleRate = fmtChunk.SampleRate;
	ByteRate = fmtChunk.ByteRate;
	BlockAllign = fmtChunk.BlockAllign;
	BitsPerSample = fmtChunk.BitsPerSample;

	SoundDataSize = wavChunkSize + BlockAllign;
	SoundData = (unsigned char*)calloc(SoundDataSize, sizeof(char));
	
	byteSteam.CopyBytesAndMove(SoundData, wavChunkSize);
}

void BF::WAV::Save(const char* filePath)
{

}

void BF::WAV::ConvertTo(Sound& sound)
{
	sound.NumerOfChannels = NumerOfChannels;
	sound.SampleRate = SampleRate;
	sound.BitsPerSample = BitsPerSample;
	sound.DataSize = SoundDataSize;
	sound.Data = (unsigned char*)malloc(SoundDataSize);

	memcpy(sound.Data, SoundData, SoundDataSize);
}

void BF::WAV::ConvertFrom(Sound& sound)
{

}