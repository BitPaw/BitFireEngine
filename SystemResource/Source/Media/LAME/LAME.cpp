#include "LAME.h"

#include <File/ByteStream.h>
#include <Text/Text.h>

size_t BF::LAME::Parse(const unsigned char* data, const size_t dataSize)
{
	ByteStream dataStream(data, dataSize);

	// Check signature (4 Bytes)
	{
		const char signature[] = { 'L', 'A', 'M', 'E' };
		const size_t signatueSize = sizeof(signature);
		const bool isValid = dataStream.ReadAndCompare(signature, signatueSize);

		if(!isValid)
		{
			return 0;
		}
	}

	// Fetch version (5 Bytes)
	{
		char majorVersionText;
		char minorVersionText[2];
		char releaseVersionText = 0;

		dataStream.Read(&majorVersionText, 1); // 1 character
		const char isDot = dataStream.ReadAndCompare('.');
		dataStream.Read(minorVersionText, 2u); // 2 character
		dataStream.Read(releaseVersionText); // letter

		int a = 0;
		int b = 0;

		Text::ToInt(&majorVersionText, 1u, a);
		Text::ToInt(minorVersionText, 2u, b);

		MajorVersion = a;
		MinorVersion = b;
		ReleaseVersion = releaseVersionText;
	}

	dataStream.Read(Revision);
	dataStream.Read(VBRType);
	dataStream.Read(LowpassFrequency);
	dataStream.Read(Peak_signal, Endian::Big);
	dataStream.Read(Radio_replay_pad, Endian::Big);
	dataStream.Read(Radio_replay_set_name, Endian::Big);
	dataStream.Read(Radio_replay_originator_code, Endian::Big);
	dataStream.Read(Radio_replay_gain, Endian::Big);
	dataStream.Read(Audiophile_replay_gain, Endian::Big);
	dataStream.Read(Flag_ath_type);
	dataStream.Read(Flag_expn_psy_tune);
	dataStream.Read(Flag_safe_joint);
	dataStream.Read(Flag_no_gap_more);
	dataStream.Read(Flag_no_gap_previous);
	dataStream.Read(Average_bit_rate);
	dataStream.Read(Delay_padding_delay_high);
	dataStream.Read(Delay_padding_delay_low);
	dataStream.Read(Delay_padding_padding_high);
	dataStream.Read(Delay_padding_padding_low);
	dataStream.Read(noise_shaping);
	dataStream.Read(stereo_mode);
	dataStream.Read(non_optimal);

	// Parse: source frequency
	{
		unsigned char sourcefrequencyID = 0;

		dataStream.Read(sourcefrequencyID);

		switch(sourcefrequencyID)
		{
			case 0b00:
				SourceFrequency = LAMESourceFrequency::kHz32OrLess;
				break;

			case 0b01:
				SourceFrequency = LAMESourceFrequency::kHz44x1;
				break;

			case 0b10:
				SourceFrequency = LAMESourceFrequency::kHz48;
				break;

			case 0b11:
				SourceFrequency = LAMESourceFrequency::kHz48Over;
				break;
			
			default:
				SourceFrequency = LAMESourceFrequency::Invalid;
				break;
		}
	}

	dataStream.Read(Unused);
	dataStream.Read(Preset, Endian::Big);
	dataStream.Read(MusicLength, Endian::Big);


	return dataStream.DataCursorPosition;
}