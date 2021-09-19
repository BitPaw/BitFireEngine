#include "MID.h"
#include "../../File/File.h"
#include "../../Container/ByteStreamHusk.h"
#include "MIDICommand.h"

void BF::MID::Load(const char* filePath)
{
	const char midiTrackEndIndicator[5] = "\x00\xFF\x2F\x00";

	File file(filePath);
	file.ReadFromDisk();
	ByteStreamHusk byteStreamHusk(file.Data, file.DataSize);

	// Pasre Chunk header
	{
		bool validHeaderTag = byteStreamHusk.CompareBytesAndMove((void*)"MThd", 4u);
		unsigned int chunkLength = byteStreamHusk.ExtractIntegerAndMove(Endian::Big);
		Format = byteStreamHusk.ExtractShortAndMove(Endian::Big);
		TrackListSize = byteStreamHusk.ExtractShortAndMove(Endian::Big);
		MusicSpeed = byteStreamHusk.ExtractShortAndMove(Endian::Big);
	}	

	TrackList = new MIDITrack[TrackListSize];

	// Parse Track Header
	for (unsigned int i = 0; i < TrackListSize; i++)
	{
		bool validTrackHeaderTag = byteStreamHusk.CompareBytesAndMove((void*)"MTrk", 4u);
		unsigned int chunkLength = byteStreamHusk.ExtractIntegerAndMove(Endian::Big);
		MIDITrack& track = TrackList[i];

		track.EventData = (char*)malloc(chunkLength);
		track.EventDataSize = chunkLength;

		byteStreamHusk.CopyBytesAndMove(track.EventData, chunkLength);
	}
}

void BF::MID::Save(const char* filePath)
{
	unsigned int fileSize = 14u;

	for (unsigned int i = 0; i < TrackListSize; i++)
	{
		MIDITrack& track = TrackList[i];

		fileSize += 8u + track.EventDataSize;
	}

	char* data = (char*)malloc(fileSize);
	ByteStreamHusk byteStreamHusk((unsigned char*)data, fileSize);

	byteStreamHusk.InsertArrayAndMove((void*)"MThd", 4u);
	byteStreamHusk.InsertIngegerAndMove(Endian::Big, 6u);
	byteStreamHusk.InsertShortAndMove(Endian::Big, Format);
	byteStreamHusk.InsertShortAndMove(Endian::Big, TrackListSize);
	byteStreamHusk.InsertShortAndMove(Endian::Big, MusicSpeed);

	for (unsigned int  i = 0; i < TrackListSize; i++)
	{
		MIDITrack& track = TrackList[i];

		byteStreamHusk.InsertArrayAndMove((void*)"MTrk", 4u);
		byteStreamHusk.InsertIngegerAndMove(Endian::Big, track.EventDataSize);
		byteStreamHusk.InsertArrayAndMove(track.EventData, track.EventDataSize);
	}	

	File::WriteToDisk(filePath, data, fileSize);

	free(data);
}

void BF::MID::ConvertTo(Sound& sound)
{

}

void BF::MID::ConvertFrom(Sound& sound)
{
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