#include "WAV.h"
#include "../../File/FileStream.h"
#include <cstring>

BF::WAV::WAV()
{
	SoundDataSize = 0;
	SoundData = nullptr;
}

BF::WAV::~WAV()
{
	free(SoundData);
}

BF::FileActionResult BF::WAV::Load(const char* filePath)
{
	FileStream file;
	FileActionResult FileActionResult = file.ReadFromDisk(filePath);
	Endian endian;

	if (FileActionResult != FileActionResult::Successful)
	{
		return FileActionResult;
	}

	file.Read(RIFFChunk.ChunkID, 4u);

	bool useBigEndian = memcmp("RIFX", RIFFChunk.ChunkID, 4u) == 0;
	bool useLittleEndian = memcmp("RIFF", RIFFChunk.ChunkID, 4u) == 0;
	bool isValidEndian = useLittleEndian != useBigEndian;

	if (!isValidEndian)
	{
		return FileActionResult::FormatNotSupported;
	}

	if (useLittleEndian)
	{
		endian = Endian::Little;
	}

	if (useBigEndian)
	{
		endian = Endian::Big;
	}

	file.Read(RIFFChunk.ChunkSize, endian);
	file.Read(RIFFChunk.Format, 4u);

	//---<FMT Chunk>---------------------
	file.Read(FMTChunk.ChunkID, 4u);
	file.Read(FMTChunk.ChunkSize, endian);
	file.Read(FMTChunk.AudioFormat, endian);
	file.Read(FMTChunk.NumerOfChannels, endian);
	file.Read(FMTChunk.SampleRate, endian);
	file.Read(FMTChunk.ByteRate, endian);
	file.Read(FMTChunk.BlockAllign, endian);
	file.Read(FMTChunk.BitsPerSample, endian);
	//---------------------------------------


	//---------------------------------------	
	char dataText[4];

	file.Read(dataText, 4u);

	bool isRIFFListChunk = memcmp("LIST", dataText, 4) == 0;

	if (isRIFFListChunk)
	{
		file.DataCursorPosition += 30u;
	}	
	//---------------------------------------
	char dataTagText[4];

	file.Read(dataTagText, 4u);

	bool validDataChunk = memcmp("data", dataTagText, 4u) == 0;

	if (!validDataChunk)
	{
		return FileActionResult::FormatNotAsExpected;
	}

	file.Read(SoundDataSize, endian);

	SoundData = (unsigned char*)malloc(SoundDataSize * sizeof(char));

	file.Read(SoundData, SoundDataSize);	

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WAV::Save(const char* filePath)
{
	// Note: The sample data must end on an even byte boundary. Whatever that means. 

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WAV::ConvertTo(Sound& sound)
{
	sound.NumerOfChannels = FMTChunk.NumerOfChannels;
	sound.SampleRate = FMTChunk.SampleRate;
	sound.BitsPerSample = FMTChunk.BitsPerSample;
	sound.DataSize = SoundDataSize;
	sound.Data = (unsigned char*)malloc(SoundDataSize);

	memcpy(sound.Data, SoundData, SoundDataSize);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WAV::ConvertFrom(Sound& sound)
{
	return FileActionResult::Successful;
}