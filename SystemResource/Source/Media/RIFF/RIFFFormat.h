#pragma once

namespace BF
{
	enum class RIFFFormat
	{
		Invalid,

		WaveformAudio, // WAVE
		MultimediaMovieFile, // RMMP
		MIDI, // RMID
		DeviceIndependentBitmap, // RDIB
		Palette,  // PAL
		AudioVideoInterleave, // AVI 
		
		//DLS,
	};
}