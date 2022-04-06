#include "WAV.h"
#include "../../File/FileStream.h"
#include <cstring>

#include <File/Cluster4Byte.h>

BF::WAV::WAV()
{
	SoundDataSize = 0;
	SoundData = nullptr;
}

BF::WAV::~WAV()
{
	free(SoundData);
}

BF::FileActionResult BF::WAV::Load(const wchar_t* filePath)
{
	FileStream file;
	Endian endian;

	// Load file
	{
		const FileActionResult FileActionResult = file.ReadFromDisk(filePath);
		const bool successful = FileActionResult == FileActionResult::Successful;

		if (!successful)
		{
			return FileActionResult;
		}
	}

	file.Read(RIFFChunk.ChunkID.Data, 4u);

	switch (RIFFChunk.ChunkID.Value) // Detect Endiantype
	{
		case MakeInt('R', 'I', 'F', 'X'):
			endian = Endian::Big;
			break;

		case MakeInt('R', 'I', 'F', 'F'):
			endian = Endian::Little;
			break;

		default:
			return FileActionResult::FormatNotSupported;
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
	{
		const unsigned int value = MakeInt('L', 'I', 'S', 'T');
		const bool isRIFFListChunk = file.ReadAndCompare(value);

		if (isRIFFListChunk)
		{
			file.DataCursorPosition += 30u;
		}
	}
	//---------------------------------------
	{
		const unsigned int value = MakeInt('d', 'a', 't', 'a');
		const bool validDataChunk = file.ReadAndCompare(value);	

		if (!validDataChunk)
		{
			return FileActionResult::FormatNotAsExpected;
		}
	}
	

	file.Read(SoundDataSize, endian);

	SoundData = (unsigned char*)malloc(SoundDataSize * sizeof(char));

	file.Read(SoundData, SoundDataSize);	

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WAV::Save(const wchar_t* filePath)
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