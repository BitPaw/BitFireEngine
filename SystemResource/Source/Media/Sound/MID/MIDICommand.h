#pragma once

namespace BF
{
	enum class MIDICommand
	{
		Unkown,

		NoteON, // 0x8?
		NoteOFF, // 0x9?
		PolyphonicKeyAfterTouch, // 0xA?
		ControlChange, // 0xB?
		ProgrammChange, // 0xC?
		ChannelAfterTouch, // 0xD?
		PitchBendChange, // 0xE?
		NoteEvent // 0xFF
	};
}