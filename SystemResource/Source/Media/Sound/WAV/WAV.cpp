#include "WAV.h"

#include <File/File.h>
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

BF::FileActionResult BF::WAV::Load(const char* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath);
		const bool sucessful = fileLoadingResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileLoadingResult;
		}
	}

	{
		const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

		return fileParsingResult;
	}
}

BF::FileActionResult BF::WAV::Load(const wchar_t* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath);
		const bool sucessful = fileLoadingResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileLoadingResult;
		}
	}

	{
		const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

		return fileParsingResult;
	}	
}

BF::FileActionResult BF::WAV::Load(const unsigned char* fileData, const size_t fileDataSize)
{
	ByteStream dataStream(fileData, fileDataSize);
	Endian endian = Endian::Invalid;

	// RIFF
	{
		RIFF riff;
		const unsigned char* riffHeaderStart = dataStream.CursorCurrentAdress();
		const size_t maximalSize = dataStream.ReadPossibleSize();
		const size_t parsedBytes = riff.Parse(riffHeaderStart, maximalSize);

		if(!riff.Valid)
		{
			return FileActionResult::FormatNotAsExpected;
		}

		dataStream.CursorAdvance(parsedBytes);

		endian = riff.EndianFormat;
	}
	//----------------

	//---<FMT Chunk>---------------------
	{
		ByteCluster fmtHeader;

		dataStream.Read(fmtHeader.Data, 4u);

		const unsigned int expectedValue = MakeInt('f', 'm', 't', ' ');
		const bool valid = expectedValue == fmtHeader.Value;

		if(!valid)
		{
			return FileActionResult::FormatNotSupported;
		}
	}

	dataStream.Read(Format.ChunkSize, endian);
	dataStream.Read(Format.AudioFormat, endian);
	dataStream.Read(Format.NumerOfChannels, endian);
	dataStream.Read(Format.SampleRate, endian);
	dataStream.Read(Format.ByteRate, endian);
	dataStream.Read(Format.BlockAllign, endian);
	dataStream.Read(Format.BitsPerSample, endian);
	//---------------------------------------

	//---------------------------------------	
	{
		const unsigned int value = MakeInt('L', 'I', 'S', 'T');
		const bool isRIFFListChunk = dataStream.ReadAndCompare(value);

		if(isRIFFListChunk)
		{
			dataStream.DataCursorPosition += 30u;
		}
	}
	//---------------------------------------
	{
		const unsigned int value = MakeInt('d', 'a', 't', 'a');
		const bool validDataChunk = dataStream.ReadAndCompare(value);

		if(!validDataChunk)
		{
			return FileActionResult::FormatNotAsExpected;
		}
	}

	dataStream.Read(SoundDataSize, endian);

	SoundData = Memory::Allocate<unsigned char>(SoundDataSize);

	dataStream.Read(SoundData, SoundDataSize);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WAV::Save(const wchar_t* filePath)
{
	// Note: The sample data must end on an even byte boundary. Whatever that means. 
	File fileStream;

	const Endian endian = Endian::Little;
	unsigned int riffSize = 0;

	fileStream.Write("RIFF", 4);
	fileStream.Write(riffSize, endian);
	fileStream.Write("WAVE", 4);

	fileStream.Write("fmt ", 4u);
	fileStream.Write(Format.ChunkSize, endian);
	fileStream.Write(Format.AudioFormat, endian);
	fileStream.Write(Format.NumerOfChannels, endian);
	fileStream.Write(Format.SampleRate, endian);
	fileStream.Write(Format.ByteRate, endian);
	fileStream.Write(Format.BlockAllign, endian);
	fileStream.Write(Format.BitsPerSample, endian);

	// LIST?

	fileStream.Write("data", 4);
	fileStream.Write(SoundDataSize, endian);
	fileStream.Write(SoundData, SoundDataSize);

	fileStream.WriteToDisk(filePath);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WAV::ConvertTo(Sound& sound)
{
	sound.NumerOfChannels = Format.NumerOfChannels;
	sound.SampleRate = Format.SampleRate;
	sound.BitsPerSample = Format.BitsPerSample;
	sound.DataSize = SoundDataSize;
	sound.Data = Memory::Allocate<unsigned char>(SoundDataSize);

	Memory::Copy(sound.Data, SoundData, SoundDataSize);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::WAV::ConvertFrom(Sound& sound)
{
	return FileActionResult::Successful;
}