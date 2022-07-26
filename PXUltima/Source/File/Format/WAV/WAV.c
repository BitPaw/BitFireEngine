#include "WAV.h"

#include <File/Format/RIFF/RIFF.h>
#include <File/ParsingStream.h>
#include <Memory/Memory.h>
#include <File/Endian.h>
#include <Container/ClusterInt.h>

#define WAVListMarker MakeInt('L', 'I', 'S', 'T')

ActionResult WAVParse(WAV* wav, const void* data, const size_t dataSize, size_t* dataRead)
{
	ParsingStream parsingStream;
	Endian endian = EndianInvalid;

	MemorySet(wav, sizeof(WAV), 0);
	*dataRead = 0;

	ParsingStreamConstruct(&parsingStream, data, dataSize);

	// RIFF
	{
		RIFF riff;
		const unsigned char* riffHeaderStart = ParsingStreamCursorPosition(&parsingStream);
		const size_t maximalSize = ParsingStreamRemainingSize(&parsingStream);
		size_t parsedBytes = 0;

		const ActionResult actionResult = RIFFParse(&riff, riffHeaderStart, maximalSize, &parsedBytes);

		if(!riff.Valid)
		{
			return ResultInvalidHeaderSignature;
		}

		ParsingStreamCursorAdvance(&parsingStream, parsedBytes);

		endian = riff.EndianFormat;
	}
	//-------------------------------------------------------------------------

	//---<FMT Chunk>-----------------------------------------------------------
	{
		const unsigned char* fmtHeaderStart = ParsingStreamCursorPosition(&parsingStream);
		const size_t maximalSize = ParsingStreamRemainingSize(&parsingStream);
		size_t parsedBytes = 0;
	
		const ActionResult actionResult = FMTParse(&wav->Format, fmtHeaderStart, maximalSize, &parsedBytes, endian);
		const unsigned char sucessful = actionResult == ResultSuccessful;

		if(!sucessful)
		{
			return ResultFormatNotAsExpected;
		}

		ParsingStreamCursorAdvance(&parsingStream, parsedBytes);
	}
	//---------------------------------------

	//---------------------------------------	
	{
		const unsigned int value = WAVListMarker;
		const unsigned char isRIFFListChunk = ParsingStreamReadAndCompare(&parsingStream, &value, sizeof(unsigned int));

		if(isRIFFListChunk)
		{
			ParsingStreamCursorAdvance(&parsingStream, 30u);
		}
	}
	//---------------------------------------
	{
		const unsigned int value = MakeInt('d', 'a', 't', 'a');
		const unsigned char validDataChunk = ParsingStreamReadAndCompare(&parsingStream, &value, sizeof(unsigned int));

		if(!validDataChunk)
		{
			return ResultFormatNotAsExpected;
		}
	}

	ParsingStreamReadIU(&parsingStream, wav->SoundDataSize, endian);

	wav->SoundData = MemoryAllocate(sizeof(unsigned char) * wav->SoundDataSize);

	ParsingStreamReadD(&parsingStream, wav->SoundData, wav->SoundDataSize);

	return ResultSuccessful;
}

/*

ActionResult BF::WAV::Save(const wchar_t* filePath)
{
	// Note: The sample data must end on an even byte boundary. Whatever that means.
	File fileStream;

	const Endian endian = EndianLittle;
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

	return ResultSuccessful;
}

ActionResult BF::WAV::ConvertTo(Sound& sound)
{
	sound.NumerOfChannels = Format.NumerOfChannels;
	sound.SampleRate = Format.SampleRate;
	sound.BitsPerSample = Format.BitsPerSample;
	sound.DataSize = SoundDataSize;
	sound.Data = Memory::Allocate<unsigned char>(SoundDataSize);

	MemoryCopy(SoundData, SoundDataSize, sound.Data, sound.DataSize);

	return ResultSuccessful;
}

*/