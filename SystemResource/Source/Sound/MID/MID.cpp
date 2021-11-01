#include "MID.h"

#include "MIDICommand.h"

#include "../../File/File.h"
#include "../../File/FileStream.h"

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

BF::FileActionResult BF::MID::Load(const char* filePath)
{
	
	const char midiTrackEndIndicator[5] = "\x00\xFF\x2F\x00";

	FileStream file;
	FileActionResult loadingResult = file.ReadFromDisk(filePath);

	if (loadingResult != FileActionResult::Successful)
	{
		return loadingResult;
	}

	// Pasre Chunk header
	{
		unsigned int chunkLength = 0;
		bool validHeaderTag = file.ReadAndCompare("MThd", 4u);	
		
		file.Read(chunkLength, Endian::Big);
		file.Read(Format, Endian::Big);
		file.Read(TrackListSize, Endian::Big);
		file.Read(MusicSpeed, Endian::Big);	
	}	

	TrackList = new MIDITrack[TrackListSize];

	// Parse Track Header
	for (unsigned int i = 0; i < TrackListSize; i++)
	{
		bool validTrackHeaderTag = file.ReadAndCompare("MTrk", 4u);
		unsigned int chunkLength = 0;
		MIDITrack& track = TrackList[i];

		file.Read(chunkLength, Endian::Big);

		track.EventData = (char*)malloc(chunkLength);
		track.EventDataSize = chunkLength;

		file.Read(track.EventData, chunkLength);
	}
		
	return FileActionResult::Successful;
}

BF::FileActionResult BF::MID::Save(const char* filePath)
{	
	unsigned int fileSize = 14u;

	for (unsigned int i = 0; i < TrackListSize; i++)
	{
		MIDITrack& track = TrackList[i];

		fileSize += 8u + track.EventDataSize;
	}

	FileStream file(fileSize);

	file.Write("MThd", 4u);
	file.Write((unsigned int)6u, Endian::Big);
	file.Write(Format, Endian::Big);
	file.Write(TrackListSize, Endian::Big);
	file.Write(MusicSpeed, Endian::Big);

	for (unsigned int  i = 0; i < TrackListSize; i++)
	{
		MIDITrack& track = TrackList[i];

		file.Write("MTrk", 4u);
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