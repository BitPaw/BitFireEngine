#include "MIDITrack.h"

#include <Hardware/Memory/Memory.h>

BF::MIDITrack::MIDITrack()
{
	ID = -1;
	EventData = nullptr;
	EventDataSize = 0;
}

BF::MIDITrack::~MIDITrack()
{
	MemoryRelease(EventData, EventDataSize);
}