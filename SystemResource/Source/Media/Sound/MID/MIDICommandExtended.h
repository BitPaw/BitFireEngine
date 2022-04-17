#pragma once

namespace BF
{
	enum class MIDICommandExtended
	{
		Unkown,

		Copyright, // 0x01
		InstrumentName, // 0x03
		Tempo, // 0x51
		TimeSignature, // 0x58
		KeySignature // 0x59
	};
}