#include "LAME.h"

#include <File/ParsingStream.h>
#include <Text/Text.h>

ActionResult LAMEParse(LAME* lame, const void* data, const size_t dataSize, size_t* dataRead)
{
	ParsingStream parsingStream;

	ParsingStreamConstruct(&parsingStream, data, dataSize);

	// Check signature (4 Bytes)
	{
		const char signature[] = { 'L', 'A', 'M', 'E' };
		const size_t signatueSize = sizeof(signature);
		const unsigned char isValid = ParsingStreamReadAndCompare(&parsingStream, signature, signatueSize);

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

		ParsingStreamReadC(&parsingStream, &majorVersionText); // 1 character
		const char isDot = ParsingStreamReadAndCompare(&parsingStream, '.', sizeof(unsigned char));
		ParsingStreamReadD(&parsingStream, minorVersionText, 2u); // 2 character
		ParsingStreamReadC(&parsingStream, releaseVersionText); // letter

		int a = 0;
		int b = 0;

		TextToIntA(&majorVersionText, 1u, &a);
		TextToIntA(minorVersionText, 2u, &b);

		lame->MajorVersion = a;
		lame->MinorVersion = b;
		lame->ReleaseVersion = releaseVersionText;
	}

	ParsingStreamReadCU(&parsingStream, &lame->Revision);
	ParsingStreamReadCU(&parsingStream, &lame->VBRType);
	ParsingStreamReadCU(&parsingStream, &lame->LowpassFrequency);
	ParsingStreamReadIU(&parsingStream, &lame->Peak_signal, EndianBig);
	ParsingStreamReadSU(&parsingStream, &lame->Radio_replay_pad, EndianBig);
	ParsingStreamReadSU(&parsingStream, &lame->Radio_replay_set_name, EndianBig);
	ParsingStreamReadSU(&parsingStream, &lame->Radio_replay_originator_code, EndianBig);
	ParsingStreamReadSU(&parsingStream, &lame->Radio_replay_gain, EndianBig);
	ParsingStreamReadSU(&parsingStream, &lame->Audiophile_replay_gain, EndianBig);
	ParsingStreamReadCU(&parsingStream, &lame->Flag_ath_type);
	ParsingStreamReadCU(&parsingStream, &lame->Flag_expn_psy_tune);
	ParsingStreamReadCU(&parsingStream, &lame->Flag_safe_joint);
	ParsingStreamReadCU(&parsingStream, &lame->Flag_no_gap_more);
	ParsingStreamReadCU(&parsingStream, &lame->Flag_no_gap_previous);
	ParsingStreamReadCU(&parsingStream, &lame->Average_bit_rate);
	ParsingStreamReadCU(&parsingStream, &lame->Delay_padding_delay_high);
	ParsingStreamReadCU(&parsingStream, &lame->Delay_padding_delay_low);
	ParsingStreamReadCU(&parsingStream, &lame->Delay_padding_padding_high);
	ParsingStreamReadCU(&parsingStream, &lame->Delay_padding_padding_low);
	ParsingStreamReadCU(&parsingStream, &lame->noise_shaping);
	ParsingStreamReadCU(&parsingStream, &lame->stereo_mode);
	ParsingStreamReadCU(&parsingStream, &lame->non_optimal);

	// Parse: source frequency
	{
		unsigned char sourcefrequencyID = 0;

		ParsingStreamReadCU(&parsingStream, &sourcefrequencyID);

		switch(sourcefrequencyID)
		{
			case 0b00:
				lame->SourceFrequency = LAMESourceFrequencykHz32OrLess;
				break;

			case 0b01:
				lame->SourceFrequency = LAMESourceFrequencykHz44x1;
				break;

			case 0b10:
				lame->SourceFrequency = LAMESourceFrequencykHz48;
				break;

			case 0b11:
				lame->SourceFrequency = LAMESourceFrequencykHz48Over;
				break;

			default:
				lame->SourceFrequency = LAMESourceFrequencyInvalid;
				break;
		}
	}

	ParsingStreamReadCU(&parsingStream, &lame->Unused);
	ParsingStreamReadSU(&parsingStream, &lame->Preset, EndianBig);
	ParsingStreamReadIU(&parsingStream, &lame->MusicLength, EndianBig);

	*dataRead = parsingStream.DataCursor;

    return ResultSuccessful;
}
