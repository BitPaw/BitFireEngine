#ifndef PXLAMEINCLUDE
#define PXLAMEINCLUDE

#include <OS/Error/PXActionResult.h>
#include <Format/Type.h>
#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum LAMESourceFrequency_
	{
		LAMESourceFrequencyInvalid,
		LAMESourceFrequencykHz32OrLess,
		LAMESourceFrequencykHz44x1,
		LAMESourceFrequencykHz48,
		LAMESourceFrequencykHz48Over,
	}
	LAMESourceFrequency;

	typedef struct LAME_
	{
		PXInt8U MajorVersion;
		PXInt8U MinorVersion;
		PXInt8U ReleaseVersion;
		unsigned char Revision; // At this time these 4 bits are set to 0.
		unsigned char VBRType;
		unsigned char LowpassFrequency;
		unsigned int Peak_signal;           // 9.23 fixed point
		unsigned short Radio_replay_pad;
		unsigned short Radio_replay_set_name;
		unsigned short Radio_replay_originator_code;
		unsigned short Radio_replay_gain;
		unsigned short Audiophile_replay_gain;
		unsigned char Flag_ath_type;
		unsigned char Flag_expn_psy_tune;
		unsigned char Flag_safe_joint;
		unsigned char Flag_no_gap_more;
		unsigned char Flag_no_gap_previous;
		unsigned char Average_bit_rate;
		unsigned char Delay_padding_delay_high;
		unsigned char Delay_padding_delay_low;
		unsigned char Delay_padding_padding_high;
		unsigned char Delay_padding_padding_low;
		unsigned char noise_shaping;
		unsigned char stereo_mode;
		unsigned char non_optimal;
		LAMESourceFrequency SourceFrequency;
		unsigned char Unused;                // set to 0
		unsigned short Preset;
		unsigned int MusicLength;
	}
	LAME;

	PXPublic PXActionResult LAMEParse(LAME* const lame, PXDataStream* const dataStream);

#ifdef __cplusplus
}
#endif

#endif




