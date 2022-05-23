#include "MID.h"

#include "MIDICommand.h"

#include <File/File.h>
#include <Hardware/Memory/Memory.h>

#define MIDITrackHeaderID MakeInt('M','T','h','d')
#define MIDITrackChunkID  MakeInt('M','T','r','k')

BF::MID::MID()
{
	Format = 0;
	MusicSpeed = 0;
	TrackListSize = 0;
	TrackList = 0;
}

BF::MID::~MID()
{
	delete[] TrackList;
}

BF::FileActionResult BF::MID::Load(const wchar_t* filePath)
{	
	const char midiTrackEndIndicator[5] = "\x00\xFF\x2F\x00";

	File file;

	{
		const FileActionResult loadingResult = file.MapToVirtualMemory(filePath);
		const bool successful = loadingResult == FileActionResult::Successful;

		if(!successful)
		{
			return loadingResult;
		}
	}

	// Pasre Chunk header
	{		
		unsigned int chunkLength = 0;
		
		{
			ByteCluster headerSignature;

			file.Read(headerSignature.Data, 4u);

			const bool isValid = headerSignature.Value = MIDITrackHeaderID;

			if(!isValid)
			{
				return FileActionResult::InvalidHeaderSignature;
			}
		}
	
		
		file.Read(chunkLength, Endian::Big);
		file.Read(Format, Endian::Big);
		file.Read(TrackListSize, Endian::Big);
		file.Read(MusicSpeed, Endian::Big);	
	}	

	if(TrackListSize == 0)
	{
		return FileActionResult::Successful;
	}

	TrackList = new MIDITrack[TrackListSize];

	// Parse Track Header
	for (size_t i = 0; i < TrackListSize; i++)
	{
		MIDITrack& track = TrackList[i];
		unsigned int chunkLength = 0;

		{
			ByteCluster headerSignature;

			file.Read(headerSignature.Data, 4u);

			const bool isValid = headerSignature.Value = MIDITrackChunkID;

			if(!isValid)
			{
				return FileActionResult::InvalidHeaderSignature;
			}
		}		

		file.Read(chunkLength, Endian::Big);

		track.ID = i;
		track.EventData = Memory::Allocate<Byte>(chunkLength);
		track.EventDataSize = chunkLength;

		file.Read(track.EventData, chunkLength);
	}
		
	return FileActionResult::Successful;
}

BF::FileActionResult BF::MID::Save(const wchar_t* filePath)
{	
	size_t fileSize = 14u;

	for (unsigned int i = 0; i < TrackListSize; i++)
	{
		MIDITrack& track = TrackList[i];

		fileSize += 8u + track.EventDataSize;
	}

	File file;// (fileSize);
	const ByteCluster midiTagData(MIDITrackHeaderID);

	file.Write(midiTagData.Data, 4u); // "MThd"
	file.Write(6u, Endian::Big);
	file.Write(Format, Endian::Big);
	file.Write(TrackListSize, Endian::Big);
	file.Write(MusicSpeed, Endian::Big);

	for (size_t i = 0; i < TrackListSize; i++)
	{
		const ByteCluster midiTrackTag(MIDITrackChunkID);

		MIDITrack& track = TrackList[i];

		file.Write(midiTrackTag.Data, 4u);
		file.Write(track.EventDataSize, Endian::Big);
		file.Write(track.EventData, track.EventDataSize);
	}	

	file.WriteToDisk(filePath);

	return FileActionResult::Successful;
}

BF::FileActionResult BF::MID::ConvertTo(Sound& sound)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::MID::ConvertFrom(Sound& sound)
{
	return FileActionResult::Successful;
}


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