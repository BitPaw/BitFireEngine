#include "MID.h"

#include "MIDICommand.h"

#include <File/File.h>
#include <Hardware/Memory/Memory.h>

#define MIDITrackHeaderID {'M','T','h','d'}
#define MIDITrackChunkID  {'M','T','r','k'}

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
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryProtectionMode::ReadOnly);
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

BF::FileActionResult BF::MID::Load(const wchar_t* filePath)
{	
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryProtectionMode::ReadOnly);
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

BF::FileActionResult BF::MID::Load(const unsigned char* fileData, const size_t fileDataSize)
{
	ByteStream dataStream(fileData, fileDataSize);

	// Pasre Chunk header
	{
		unsigned int chunkLength = 0;

		{			
			const unsigned char headerSignature[] = MIDITrackHeaderID;
			const size_t headerSignatureSize = sizeof(headerSignature);
			const bool isValid = dataStream.ReadAndCompare(headerSignature, headerSignatureSize);		

			if(!isValid)
			{
				return FileActionResult::InvalidHeaderSignature;
			}
		}

		dataStream.Read(chunkLength, Endian::Big);
		dataStream.Read(Format, Endian::Big);
		dataStream.Read(TrackListSize, Endian::Big);
		dataStream.Read(MusicSpeed, Endian::Big);
	}

	if(TrackListSize == 0)
	{
		return FileActionResult::Successful;
	}

	TrackList = new MIDITrack[TrackListSize];

	// Parse Track Header
	for(size_t i = 0; i < TrackListSize; ++i)
	{
		MIDITrack& track = TrackList[i];
		unsigned int chunkLength = 0;

		{
			const unsigned char headerSignature[] = MIDITrackChunkID;
			const size_t headerSignatureSize = sizeof(headerSignature);
			const bool isValid = dataStream.ReadAndCompare(headerSignature, headerSignatureSize);

			if(!isValid)
			{
				return FileActionResult::InvalidHeaderSignature;
			}
		}

		dataStream.Read(chunkLength, Endian::Big);

		track.ID = i;
		track.EventData = Memory::Allocate<Byte__>(chunkLength);
		track.EventDataSize = chunkLength;

		dataStream.Read(track.EventData, chunkLength);
	}

	return FileActionResult::Successful;
}

BF::FileActionResult BF::MID::Save(const wchar_t* filePath)
{	
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
	file.WriteToDisk(6u, Endian::Big);
	file.WriteToDisk(Format, Endian::Big);
	file.WriteToDisk(TrackListSize, Endian::Big);
	file.WriteToDisk(MusicSpeed, Endian::Big);

	for (size_t i = 0; i < TrackListSize; i++)
	{
		const char midiTrackTag[] = MIDITrackChunkID;

		MIDITrack& track = TrackList[i];

		file.WriteToDisk(midiTrackTag, 4u);
		file.WriteToDisk(track.EventDataSize, Endian::Big);
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