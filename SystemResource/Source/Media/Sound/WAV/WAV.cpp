#include "WAV.h"

#include <File/FileStream.h>
#include <Media/RIFF/RIFF.h>
#include <Hardware/Memory/Memory.h>

BF::WAV::WAV()
{
	SoundDataSize = 0;
	SoundData = nullptr;
}

BF::WAV::~WAV()
{
	Memory::Release(SoundData, SoundDataSize);
}

BF::FileActionResult BF::WAV::Load(const wchar_t* filePath)
{
	FileStream file;
	Endian endian = Endian::Invalid;

	// Load file
	{
		const FileActionResult FileActionResult = file.ReadFromDisk(filePath);
		const bool successful = FileActionResult == FileActionResult::Successful;

		if (!successful)
		{
			return FileActionResult;
		}
	}

	// RIFF
	{
		RIFF riff;

		riff.Parse(file);

		if(!riff.Valid)
		{
			return FileActionResult::FormatNotAsExpected;
		}

		endian = riff.EndianFormat;
	}	
	//----------------

	//---<FMT Chunk>---------------------
	{
		ByteCluster fmtHeader;

		file.Read(fmtHeader.Data, 4u);

		const unsigned int expectedValue = MakeInt('f', 'm', 't', ' ');
		const bool valid = expectedValue == fmtHeader.Value;

		if(!valid)
		{
			return FileActionResult::FormatNotSupported;
		}
	}
	
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

	SoundData = Memory::Allocate<unsigned char>(SoundDataSize);

	file.Read(SoundData, SoundDataSize);	

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WAV::Save(const wchar_t* filePath)
{
	// Note: The sample data must end on an even byte boundary. Whatever that means. 
	FileStream fileStream;

	const Endian endian = Endian::Little;
	unsigned int riffSize = 0;

	fileStream.Write("RIFF", 4);
	fileStream.Write(riffSize, endian);
	fileStream.Write("WAVE", 4);

	fileStream.Write("fmt ", 4u);
	fileStream.Write(FMTChunk.ChunkSize, endian);
	fileStream.Write(FMTChunk.AudioFormat, endian);
	fileStream.Write(FMTChunk.NumerOfChannels, endian);
	fileStream.Write(FMTChunk.SampleRate, endian);
	fileStream.Write(FMTChunk.ByteRate, endian);
	fileStream.Write(FMTChunk.BlockAllign, endian);
	fileStream.Write(FMTChunk.BitsPerSample, endian);

	// LIST?

	fileStream.Write("data", 4);
	fileStream.Write(SoundDataSize, endian);
	fileStream.Write(SoundData, SoundDataSize);

	fileStream.WriteToDisk(filePath);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WAV::ConvertTo(Sound& sound)
{
	sound.NumerOfChannels = FMTChunk.NumerOfChannels;
	sound.SampleRate = FMTChunk.SampleRate;
	sound.BitsPerSample = FMTChunk.BitsPerSample;
	sound.DataSize = SoundDataSize;
	sound.Data = Memory::Allocate<unsigned char>(SoundDataSize);

	Memory::Copy(sound.Data, SoundData, SoundDataSize);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WAV::ConvertFrom(Sound& sound)
{
	return FileActionResult::Successful;
}