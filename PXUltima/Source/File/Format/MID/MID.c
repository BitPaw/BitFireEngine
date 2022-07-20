#include "MID.h"

#include <File/ParsingStream.h>
#include <Memory/Memory.h>


#define MIDITrackHeaderID {'M','T','h','d'}
#define MIDITrackChunkID  {'M','T','r','k'}

/*
MIDICommand midiCommand;
unsigned int byteLength = -1;

switch (midiCommand)
{
	default:
	case MIDICommand::Unkown:
		byteLength = -1;
		break;

	case MIDICommand::ProgrammChange:
	case MIDICommand::ChannelAfterTouch:
		byteLength = 1;
		break;

	case MIDICommand::NoteOFF:
	case MIDICommand::NoteON:
	case MIDICommand::PolyphonicKeyAfterTouch:
	case MIDICommand::ControlChange:
	case MIDICommand::PitchBendChange:
	case MIDICommand::NoteEvent:
		byteLength = 2;
		break;
}*/

ActionResult MIDParse(MID* mid, const void* data, const size_t dataSize, size_t* dataRead)
{
	ParsingStream parsingStream;

	ParsingStreamConstruct(&parsingStream, data, dataSize);

	// Pasre Chunk header
	{
		unsigned int chunkLength = 0;

		{
			const unsigned char headerSignature[] = MIDITrackHeaderID;
			const size_t headerSignatureSize = sizeof(headerSignature);
			const unsigned char isValid = ParsingStreamReadAndCompare(&parsingStream, headerSignature, headerSignatureSize);

			if(!isValid)
			{
				return ResultInvalidHeaderSignature;
			}
		}

		ParsingStreamReadSU(&parsingStream, chunkLength, EndianBig);
		ParsingStreamReadSU(&parsingStream, &mid->Format, EndianBig);
		ParsingStreamReadSU(&parsingStream, &mid->TrackListSize, EndianBig);
		ParsingStreamReadSU(&parsingStream, &mid->MusicSpeed, EndianBig);
	}

	if(!mid->TrackListSize)
	{
		return ResultSuccessful;
	}

	mid->TrackList = MemoryAllocate(sizeof(MIDITrack) * mid->TrackListSize);

	// Parse Track Header
	for(size_t i = 0; i < mid->TrackListSize; ++i)
	{
		MIDITrack* track = &mid->TrackList[i];
		unsigned int chunkLength = 0;

		{
			const unsigned char headerSignature[] = MIDITrackChunkID;
			const size_t headerSignatureSize = sizeof(headerSignature);
			const unsigned char isValid = ParsingStreamReadAndCompare(&parsingStream, headerSignature, headerSignatureSize);

			if(!isValid)
			{
				return ResultInvalidHeaderSignature;
			}
		}

		ParsingStreamReadIU(&parsingStream, chunkLength, EndianBig);

		track->ID = i;
		track->EventData = MemoryAllocate(sizeof(unsigned char) * chunkLength);
		track->EventDataSize = chunkLength;

		ParsingStreamReadD(&parsingStream, track->EventData, chunkLength);
	}

	*dataRead = parsingStream.DataCursor;

	return ResultSuccessful;
}

ActionResult MIDSerialize(MID* mid, void* data, const size_t dataSize, size_t* dataWritten)
{
	/*
	File file;

	{
		const FileActionResult fileOpenResult = file.Open(filePath, FileOpenMode::Write);
		const bool sucessful = fileOpenResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileOpenResult;
		}
	}

	const char midiTagData[] = MIDITrackHeaderID;

	file.WriteToDisk(midiTagData, 4u); // "MThd"
	file.WriteToDisk(6u, EndianBig);
	file.WriteToDisk(Format, EndianBig);
	file.WriteToDisk(TrackListSize, EndianBig);
	file.WriteToDisk(MusicSpeed, EndianBig);

	for(size_t i = 0; i < TrackListSize; i++)
	{
		const char midiTrackTag[] = MIDITrackChunkID;

		MIDITrack& track = TrackList[i];

		file.WriteToDisk(midiTrackTag, 4u);
		file.WriteToDisk(track.EventDataSize, EndianBig);
		file.WriteToDisk(track.EventData, track.EventDataSize);
	}

	{
		const FileActionResult fileCloseResult = file.Close();
		const bool sucessful = fileCloseResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileCloseResult;
		}
	}

	return FileActionResult::Successful;*/

	return ResultSuccessful;
}